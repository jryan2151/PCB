// Example output: 134912,15,24011.66,5.580,150,744,
//(Time,Sensor#,Impedence,Gain,Tap,?)



/* Copyright (c) 2015-2019, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

 _______________________________________________________________________________
 *************************** NOTES ON USING THIS CODE **************************
 *******************************************************************************
 _______________________________________________________________________________

 The sampling duration in the CC2640R2_LAUNCHXL.c file (line 131) is a limiting
 factor for the MUXFREQ settings. The maximums are listed below:

 MUXFREQ max | samplingDuration
 650         | 341_US
 800         | 170_US
 _______________________________________________________________________________

 These values must be changed otherwise there will be a bottleneck of information
 over the UART to USB connection that will limit the dataspeed

 Notes on MUXFREQ setting:
 Nominal    | Actual
 200        | 201.6
 400        | 403.3
 650        | 656.0
 _______________________________________________________________________________

 When changing the number of channels you want to measure you much change the
 variable "channels" on line 96 length of the lastAmp array on line 97 to the
 same number.


 */
//#include <unistd.h> ???
//#include <stdbool.h> ???
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

/* Driver Header files */
#include <ti/drivers/GPIO.h>
#include <ti/drivers/PIN.h>
#include <ti/drivers/UART.h>
#include <ti/drivers/ADC.h> //http://dev.ti.com/tirex/content/simplelink_cc13x0_sdk_1_00_00_13/docs/tidrivers/doxygen/html/_a_d_c_8h.html
#include <ti/drivers/timer/GPTimerCC26XX.h>
#include <ti/drivers/I2C.h>
#include <ti/drivers/i2c/I2CCC26XX.h> //http://software-dl.ti.com/dsps/dsps_public_sw/sdo_sb/targetcontent/tirtos/2_20_00_06/exports/tirtos_full_2_20_00_06/products/tidrivers_full_2_20_00_08/docs/doxygen/html/_i2_c_c_c26_x_x_8h.html
#include <ti/drivers/Power.h>
#include <ti/drivers/power/PowerCC26XX.h>
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <xdc/runtime/Types.h>
#include <xdc/runtime/Timestamp.h>
#include <ti/drivers/SD.h>
#include <xdc/runtime/System.h>
#include <ti/sysbios/hal/Hwi.h>

// ADDED BY GABE //
//#include <ti/drivers/sleep_GS.c>


/* Board Header file */
#include "Board.h"
#include "DiskAccess.h"
#include "Storage.h"
#include "Serializer.h"
#include "sensors.h"

/////////////////////////// pin configuration ///////////////////////
/* Pin driver handles */
static PIN_Handle muxPinHandle;

/* Global memory storage for a PIN_Config table */
static PIN_State muxPinState;

/* Global Variables */
uint8_t muxidx = 0;
uint8_t muxmod = 0;
uint8_t status = 3;
float avg = 0;
uint16_t adcValue = 0;
float gain = 0;
float impedance = 0; // ???
char* uartBuf;
int clockticks = 0;
uint_fast16_t uartTxBufferOffset = 0; // ???

int stutter = 0; //checks to make sure we dont stutter more than 3 times

uint8_t DEVICENUM = 1;
const int channels = 16; //change to const in channels = 16; ???
//int lastAmp[1] = {500}; //initialize to the value you want to start the signal2 at (must be as long as channel)
static int MUXFREQ = 800;  //600 (maybe not good for bluetooth so probably don't change ??? //Switching frequency (this equals the number of channels to read each second). Must be less than half of DAC frequency (~line 320).

static int inc = 0;
static int checker; //this is to fix the end line


// CAP'N'S LOG: ADDED BY GABE
static float PERIOD_OF_TIME = 1.3087;
float milliseconds = 0;
uint8_t sensorValues[channels] = {125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125}; //initial tap value for each sensor
int taps[8] = {1,24,32,45,60,125,200,250}; // The discrete tap values that we want to use, the 1 and 155 on the ends are for error handling and should never actually be used
int currentTap[channels] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}; //stores the tap value for each sensor so we can have the right tap for each read.
float lowCuts[8] = {0,1400,1400,1400,1200,1400,0,0}; // the gain value at which we will switch to the next tap value because the gain is getting too low
float highCuts[8] = {0,4000,2400,2400,2300,2300,2300,0}; // the gain value at which we will switch to the previous tap value because the gain is getting too high
// END OF CAP'N'S LOG


// ??? uint8_t sensorValues[channels] = {100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100}; //initial tap value for each sensor
int lastAmp[channels] = {500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500}; //initialize to the value you want to start the signal at (must be as long as channel)
#define ADC_SAMPLE_COUNT    (1) //Number of samples to read each time we call the callback function (how many samples per row on output)
#define ADCMULTIPLE         (1) //How many times to call the ADC within one mux switch (total samples per switch will equal ADCMULTIPLE*ADC_SAMPLE_COUNT)
#define ADChiLimit          3000 //raw value that will be the threshold
#define ADCloLimit          200 // ??? 200 //raw value that will be the threshold
#define minVOLT             (80) //

 /* Starting sector to write/read to */
#define STARTINGSECTOR 0

#define BYTESPERKILOBYTE 1024

PIN_Config muxPinTable[] = {
    IOID_28 | PIN_GPIO_OUTPUT_EN | PIN_GPIO_HIGH | PIN_PUSHPULL | PIN_DRVSTR_MAX, //EN
    IOID_22 | PIN_GPIO_OUTPUT_EN | PIN_GPIO_HIGH | PIN_PUSHPULL | PIN_DRVSTR_MAX, //A3
    IOID_23 | PIN_GPIO_OUTPUT_EN | PIN_GPIO_HIGH | PIN_PUSHPULL | PIN_DRVSTR_MAX, //A2
    IOID_12 | PIN_GPIO_OUTPUT_EN | PIN_GPIO_HIGH | PIN_PUSHPULL | PIN_DRVSTR_MAX, //A1
    IOID_15 | PIN_GPIO_OUTPUT_EN | PIN_GPIO_HIGH | PIN_PUSHPULL | PIN_DRVSTR_MAX, //A0
    PIN_TERMINATE
};

/////////////////////////// mux task configuration ///////////////////////
/* Task data */
GPTimerCC26XX_Handle hMUXTimer;
void MUXtimerCallback(GPTimerCC26XX_Handle handle, GPTimerCC26XX_IntMask interruptMask) {
    // We determine this whole function is unnecessary

    muxmod = muxidx % channels; //get remainder of muxidx for switch // ??? Commented out in Joseph's code
    switch(muxidx) // ??? Switched to muxidx from muxmod

    {
        case 0: //2
            PIN_setOutputValue(muxPinHandle, IOID_28, 0); //E
            PIN_setOutputValue(muxPinHandle, IOID_22, 0); //S3
            PIN_setOutputValue(muxPinHandle, IOID_23, 0); //S2
            PIN_setOutputValue(muxPinHandle, IOID_12, 0); //S1
            PIN_setOutputValue(muxPinHandle, IOID_15, 0); //S0
            break;
        case 1: //4
            PIN_setOutputValue(muxPinHandle, IOID_28, 0); //E
            PIN_setOutputValue(muxPinHandle, IOID_22, 0);
            PIN_setOutputValue(muxPinHandle, IOID_23, 0);
            PIN_setOutputValue(muxPinHandle, IOID_12, 0);
            PIN_setOutputValue(muxPinHandle, IOID_15, 1);
            break;
        case 2: //6
            PIN_setOutputValue(muxPinHandle, IOID_28, 0); //E
            PIN_setOutputValue(muxPinHandle, IOID_22, 0);
            PIN_setOutputValue(muxPinHandle, IOID_23, 0);
            PIN_setOutputValue(muxPinHandle, IOID_12, 1);
            PIN_setOutputValue(muxPinHandle, IOID_15, 0);
            break;
        case 3: //8
            PIN_setOutputValue(muxPinHandle, IOID_28, 0); //E
            PIN_setOutputValue(muxPinHandle, IOID_22, 0);
            PIN_setOutputValue(muxPinHandle, IOID_23, 0);
            PIN_setOutputValue(muxPinHandle, IOID_12, 1);
            PIN_setOutputValue(muxPinHandle, IOID_15, 1);
            break;
        case 4: //10
            PIN_setOutputValue(muxPinHandle, IOID_28, 0); //E
            PIN_setOutputValue(muxPinHandle, IOID_22, 0);
            PIN_setOutputValue(muxPinHandle, IOID_23, 1);
            PIN_setOutputValue(muxPinHandle, IOID_12, 0);
            PIN_setOutputValue(muxPinHandle, IOID_15, 0);
            break;
        case 5: //12
            PIN_setOutputValue(muxPinHandle, IOID_28, 0); //E
            PIN_setOutputValue(muxPinHandle, IOID_22, 0);
            PIN_setOutputValue(muxPinHandle, IOID_23, 1);
            PIN_setOutputValue(muxPinHandle, IOID_12, 0);
            PIN_setOutputValue(muxPinHandle, IOID_15, 1);
            break;
        case 6: //14
            PIN_setOutputValue(muxPinHandle, IOID_28, 0); //E
            PIN_setOutputValue(muxPinHandle, IOID_22, 0);
            PIN_setOutputValue(muxPinHandle, IOID_23, 1);
            PIN_setOutputValue(muxPinHandle, IOID_12, 1);
            PIN_setOutputValue(muxPinHandle, IOID_15, 0);
            break;
        case 7: //16
            PIN_setOutputValue(muxPinHandle, IOID_28, 0); //E
            PIN_setOutputValue(muxPinHandle, IOID_22, 0);
            PIN_setOutputValue(muxPinHandle, IOID_23, 1);
            PIN_setOutputValue(muxPinHandle, IOID_12, 1);
            PIN_setOutputValue(muxPinHandle, IOID_15, 1);
            break;
        case 15: //15
            PIN_setOutputValue(muxPinHandle, IOID_28, 0); //E
            PIN_setOutputValue(muxPinHandle, IOID_22, 1);
            PIN_setOutputValue(muxPinHandle, IOID_23, 0);
            PIN_setOutputValue(muxPinHandle, IOID_12, 0);
            PIN_setOutputValue(muxPinHandle, IOID_15, 0);
            break;
        case 14: //13
            PIN_setOutputValue(muxPinHandle, IOID_28, 0); //E
            PIN_setOutputValue(muxPinHandle, IOID_22, 1);
            PIN_setOutputValue(muxPinHandle, IOID_23, 0);
            PIN_setOutputValue(muxPinHandle, IOID_12, 0);
            PIN_setOutputValue(muxPinHandle, IOID_15, 1);
            break;
        case 13: //11
            PIN_setOutputValue(muxPinHandle, IOID_28, 0); //E
            PIN_setOutputValue(muxPinHandle, IOID_22, 1);
            PIN_setOutputValue(muxPinHandle, IOID_23, 0);
            PIN_setOutputValue(muxPinHandle, IOID_12, 1);
            PIN_setOutputValue(muxPinHandle, IOID_15, 0);
            break;
        case 12: //9
            PIN_setOutputValue(muxPinHandle, IOID_28, 0); //E
            PIN_setOutputValue(muxPinHandle, IOID_22, 1);
            PIN_setOutputValue(muxPinHandle, IOID_23, 0);
            PIN_setOutputValue(muxPinHandle, IOID_12, 1);
            PIN_setOutputValue(muxPinHandle, IOID_15, 1);
            break;
        case 11: //7
            PIN_setOutputValue(muxPinHandle, IOID_28, 0); //E
            PIN_setOutputValue(muxPinHandle, IOID_22, 1);
            PIN_setOutputValue(muxPinHandle, IOID_23, 1);
            PIN_setOutputValue(muxPinHandle, IOID_12, 0);
            PIN_setOutputValue(muxPinHandle, IOID_15, 0);
            break;
        case 10: //5
            PIN_setOutputValue(muxPinHandle, IOID_28, 0); //E
            PIN_setOutputValue(muxPinHandle, IOID_22, 1);
            PIN_setOutputValue(muxPinHandle, IOID_23, 1);
            PIN_setOutputValue(muxPinHandle, IOID_12, 0);
            PIN_setOutputValue(muxPinHandle, IOID_15, 1);
            break;
        case 9: //3
            PIN_setOutputValue(muxPinHandle, IOID_28, 0); //E
            PIN_setOutputValue(muxPinHandle, IOID_22, 1);
            PIN_setOutputValue(muxPinHandle, IOID_23, 1);
            PIN_setOutputValue(muxPinHandle, IOID_12, 1);
            PIN_setOutputValue(muxPinHandle, IOID_15, 0);
            break;
        case 8: //1
            PIN_setOutputValue(muxPinHandle, IOID_28, 0); //E
            PIN_setOutputValue(muxPinHandle, IOID_22, 1);
            PIN_setOutputValue(muxPinHandle, IOID_23, 1);
            PIN_setOutputValue(muxPinHandle, IOID_12, 1);
            PIN_setOutputValue(muxPinHandle, IOID_15, 1);
            break;
    }

    muxidx += 1; // increment counter

    if(muxidx == channels){
        muxidx = 0; //reset counter back to zero, if it equals the number of channels
    }
}

///////////////////////////////////// I2C preamble //////////////////////////
uint8_t rxBuffer1[0];            // Receive buffer
uint8_t txBuffer1[2];            // Transmit buffer
uint8_t rxBuffer2[0];            // Receive buffer
uint8_t txBuffer2[2];            // Transmit buffer
uint8_t rxBuffer3[1];          // Receive buffer
uint8_t txBuffer3[2];          // Transmit buffer
bool transferDone = false;
bool openDone = true;
uint8_t counterDAC = 0;
uint8_t counterDATA = 0;

Semaphore_Handle bacpac_channel_mutex;
Semaphore_Handle bacpac_channel_mailbox;
char streaming_buffer[96];

//Used to store the signal2 amplitude (max is 4095)
struct {
    uint16_t ampAC : 12;
    uint16_t ampDC : 12;
} Signal; //&&& signal2->Signal

// Function Declarations
static void i2cWriteCallback(I2C_Handle handle, I2C_Transaction *transac, bool result);
void DACtimerCallback(GPTimerCC26XX_Handle handle, GPTimerCC26XX_IntMask interruptMask);


/* Driver handles */
GPTimerCC26XX_Handle hDACTimer;
I2C_Handle I2Chandle;
I2C_Params I2Cparams;
I2C_Transaction i2cTrans1;
I2C_Transaction i2cTrans2;
I2C_Transaction i2cTrans3;

///////////////////////////////////// ADC/ Display Preamble /////////////////////////////////
/* ADC Global Variables */
uint16_t trigger = 0;
int_fast16_t res; // ??? in Joseph's code this is commented out
ADC_Handle adc;
ADC_Params params;

#define UARTBUFFERSIZE   64
//double adcValue[ADC_SAMPLE_COUNT];
int modBuffer[ADC_SAMPLE_COUNT];
char uartTxBuffer[UARTBUFFERSIZE]; // ??? ...SIZE] = {0};

UART_Handle uart;

// Callback function to use the UART in callback mode. It does nothing.
void uartCallback(UART_Handle handle, void *buf, size_t count) { return; }

/*
 *  ======== mainThread ========
 */
//void *mainThread(void *arg0) // ??? OLD NAME (DONT REPLACE)
//static void mainThread(UArg a0, UArg a1)
void Sensors_init() {
    uartBuf = (char*) malloc(256 * sizeof(char));
    // Initialize Variables
    Signal.ampAC = lastAmp[0]; //&&& signal2.->Signal.

    // Call Driver Init Functions
    I2C_init();
    ADC_init();
    GPIO_init();
    da_initialize();


    ////////////////////////////////////////////// GPIO /////////////////////////////////////////
    /* Configure the LED pins */
    GPIO_setConfig(Board_GPIO_LED0, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    /* Turn on user LED */
    GPIO_write(Board_GPIO_LED0, Board_GPIO_LED_OFF);

    /* Configure the LED pins */
    GPIO_setConfig(Board_GPIO_LED1, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    /* Turn on user LED */
    GPIO_write(Board_GPIO_LED1, Board_GPIO_LED_OFF);

    /* Configure the LED pins */
    GPIO_setConfig(Board_DIO0, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    /* Turn on user LED */
    GPIO_write(Board_DIO0, 0);

    ////////////////////////////////////////////// I2C //////////////////////////////////////////

    // Configure I2C parameters.
    I2C_Params_init(&I2Cparams);
    I2Cparams.bitRate = I2C_400kHz;
    I2Cparams.transferMode = I2C_MODE_CALLBACK;
    I2Cparams.transferCallbackFxn = i2cWriteCallback;

    // Initialize master I2C transaction structure
    i2cTrans1.writeBuf     = txBuffer1; //Square signal2
    i2cTrans1.writeCount   = 2;
    i2cTrans1.readBuf      = NULL;
    i2cTrans1.readCount    = 0;
    i2cTrans1.slaveAddress = 0x4C; //hex converter: https://www.cs.princeton.edu/courses/archive/fall07/cos109/bc.html

    // Initialize master I2C transaction structure
    i2cTrans2.writeBuf     = txBuffer2; //DC signal2
    i2cTrans2.writeCount   = 2;
    i2cTrans2.readBuf      = NULL;
    i2cTrans2.readCount    = 0;
    i2cTrans2.slaveAddress = 0x4D; //hex converter: https://www.cs.princeton.edu/courses/archive/fall07/cos109/bc.html

    // Initialize master I2C transaction structure
        i2cTrans3.writeBuf     = txBuffer3; //DC Signal
        i2cTrans3.writeCount   = 2;
        i2cTrans3.readBuf      = NULL;
        i2cTrans3.readCount    = 0;
        i2cTrans3.slaveAddress = 0x2C; //hex converter: https://www.cs.princeton.edu/courses/archive/fall07/cos109/bc.html
    // ??? (WHOLE THING for i2cTrans3)

    ////////////////////////////////////////////// GPTimer for DAC //////////////////////////////////////////
    GPTimerCC26XX_Params paramsDAC;
    GPTimerCC26XX_Params_init(&paramsDAC);
    paramsDAC.width          = GPT_CONFIG_32BIT;
    paramsDAC.mode           = GPT_MODE_PERIODIC_UP;
    paramsDAC.debugStallMode = GPTimerCC26XX_DEBUG_STALL_OFF;
    hDACTimer = GPTimerCC26XX_open(CC2640R2_LAUNCHXL_GPTIMER0A, &paramsDAC); //Need timer 0A for ADCbuf
    if(hDACTimer == NULL) {
        while(1);
    }

    Types_FreqHz  freq;
    BIOS_getCpuFreq(&freq); //48MHz
    GPTimerCC26XX_Value loadValDAC = 48000000/(MUXFREQ*4);
    loadValDAC = loadValDAC - 1;


    GPTimerCC26XX_setLoadValue(hDACTimer, loadValDAC);
    GPTimerCC26XX_registerInterrupt(hDACTimer, DACtimerCallback, GPT_INT_TIMEOUT);

    // Open I2C
    I2Chandle = I2C_open(Board_I2C0, &I2Cparams);

    if (I2Chandle == NULL) {
        // Error opening I2C
        openDone = false;
        while (1);
    }
    /*
    signal2.ampAC = lastAmp[muxmod];
    signal2.ampDC = signal2.ampAC/2;
    txBuffer1[0] = signal2.ampAC >> 8; //hi byte
    txBuffer1[1] = signal2.ampAC; //lower 2 bytes
    txBuffer2[0] = signal2.ampDC >> 8; //hi byte
    txBuffer2[1] = signal2.ampDC; //lower 2 bytes
    I2C_transfer(I2Chandle, &i2cTrans1);
    I2C_transfer(I2Chandle, &i2cTrans2);
    */ // ??? Commented out of Joseph's code

////////////////////////////////////////////////////////////////// MUX //////////////////////////////////////////////////////////
    muxPinHandle = PIN_open(&muxPinState, muxPinTable);
    if(!muxPinHandle) {
        /* Error initializing mux output pins */
        while(1);
    }
    PIN_setOutputValue(muxPinHandle, IOID_21, 0); // ??? IOID_21



    GPTimerCC26XX_Params paramsMUX;
    GPTimerCC26XX_Params_init(&paramsMUX);
    paramsMUX.width = GPT_CONFIG_32BIT;
    paramsMUX.mode = GPT_MODE_PERIODIC_UP;
    paramsMUX.debugStallMode = GPTimerCC26XX_DEBUG_STALL_OFF;
    hMUXTimer = GPTimerCC26XX_open(CC2640R2_LAUNCHXL_GPTIMER1A, &paramsMUX); //Need timer 0A for ADCbuf

    if(hMUXTimer == NULL) {
        Task_exit();
    }

    GPTimerCC26XX_Value loadValMUX = 48000000 / MUXFREQ;
    loadValMUX = loadValMUX - 1;
    GPTimerCC26XX_setLoadValue(hMUXTimer, loadValMUX);
    GPTimerCC26XX_registerInterrupt(hMUXTimer, MUXtimerCallback, GPT_INT_TIMEOUT);

////////////////////////////////////////////////////////////////// ADC/ UART //////////////////////////////////////////////////////////
    /* Create a UART with data processing off. */
    UART_Params uartParams;
    UART_init();
    UART_Params_init(&uartParams);
    uartParams.writeDataMode = UART_DATA_BINARY;
    uartParams.writeMode = UART_MODE_CALLBACK;
    uartParams.writeCallback = uartCallback;
    uartParams.baudRate = 460800; // 115200; // 460800
    uart = UART_open(Board_UART0, &uartParams);


    ADC_Params_init(&params);
    adc = ADC_open(0, &params);// ADC0 uses IDIO_25 (change in cc26xx.c file in ADC section by commenting things out)
    if (adc == NULL) {
        // Error initializing ADC channel 0
        while(1);
    }

    // Turn on gain to high once
    Signal.ampAC = lastAmp[muxmod]; //Signal goes high, i.e. positive
    Signal.ampDC = Signal.ampAC/2;
    txBuffer1[0] = Signal.ampAC >> 8; //hi byte
    txBuffer1[1] = Signal.ampAC; //lower 2 bytes
    txBuffer2[0] = Signal.ampDC >> 8; //hi byte
    txBuffer2[1] = Signal.ampDC; //lower 2 bytes
    I2C_transfer(I2Chandle, &i2cTrans1);
    I2C_transfer(I2Chandle, &i2cTrans2);

    // set the mux to 0
    PIN_setOutputValue(muxPinHandle, IOID_21, 0); //E
    PIN_setOutputValue(muxPinHandle, IOID_22, 0); //S3
    PIN_setOutputValue(muxPinHandle, IOID_23, 0); //S2
    PIN_setOutputValue(muxPinHandle, IOID_12, 0); //S1
    PIN_setOutputValue(muxPinHandle, IOID_15, 0); //S0

    //DA_get_status(da_load(), "Loading Disk");
}

/////////////////////////////////////////// I2C Functions /////////////////////////////////////////////////
static void i2cWriteCallback(I2C_Handle handle, I2C_Transaction *transac, bool result){
    // Set length bytes
    if (result) {
        transferDone = true;
    }
    else {
        // Transaction failed, act accordingly...
        transferDone = false;
    }
};


void ReplaceTheMess_GS(uint8_t muxidx_GS){
    switch(muxidx_GS) {
        case 10: //sensor 0 array pin 10
            PIN_setOutputValue(muxPinHandle, IOID_21, 0); //E
            PIN_setOutputValue(muxPinHandle, IOID_22, 0); //S3
            PIN_setOutputValue(muxPinHandle, IOID_23, 0); //S2
            PIN_setOutputValue(muxPinHandle, IOID_12, 0); //S1
            PIN_setOutputValue(muxPinHandle, IOID_15, 0); //S0
            break;
        case 13: // sensor 1 array pin 13
            PIN_setOutputValue(muxPinHandle, IOID_21, 0); //E
            PIN_setOutputValue(muxPinHandle, IOID_22, 0);
            PIN_setOutputValue(muxPinHandle, IOID_23, 0);
            PIN_setOutputValue(muxPinHandle, IOID_12, 0);
            PIN_setOutputValue(muxPinHandle, IOID_15, 1);
            break;
        case 11: // sensor 2 array pin 11
            PIN_setOutputValue(muxPinHandle, IOID_21, 0); //E
            PIN_setOutputValue(muxPinHandle, IOID_22, 0);
            PIN_setOutputValue(muxPinHandle, IOID_23, 0);
            PIN_setOutputValue(muxPinHandle, IOID_12, 1);
            PIN_setOutputValue(muxPinHandle, IOID_15, 0);
            break;
        case 8: // sensor 3 array pin 8
            PIN_setOutputValue(muxPinHandle, IOID_21, 0); //E
            PIN_setOutputValue(muxPinHandle, IOID_22, 0);
            PIN_setOutputValue(muxPinHandle, IOID_23, 0);
            PIN_setOutputValue(muxPinHandle, IOID_12, 1);
            PIN_setOutputValue(muxPinHandle, IOID_15, 1);
            break;
        case 14: //sensor 4 array pin 14
            PIN_setOutputValue(muxPinHandle, IOID_21, 0); //E
            PIN_setOutputValue(muxPinHandle, IOID_22, 0);
            PIN_setOutputValue(muxPinHandle, IOID_23, 1);
            PIN_setOutputValue(muxPinHandle, IOID_12, 0);
            PIN_setOutputValue(muxPinHandle, IOID_15, 0);
            break;
        case 12: //sensor 5 array pin 12
            PIN_setOutputValue(muxPinHandle, IOID_21, 0); //E
            PIN_setOutputValue(muxPinHandle, IOID_22, 0);
            PIN_setOutputValue(muxPinHandle, IOID_23, 1);
            PIN_setOutputValue(muxPinHandle, IOID_12, 0);
            PIN_setOutputValue(muxPinHandle, IOID_15, 1);
            break;
        case 15: //sensor 6 array pin 15
            PIN_setOutputValue(muxPinHandle, IOID_21, 0); //E
            PIN_setOutputValue(muxPinHandle, IOID_22, 0);
            PIN_setOutputValue(muxPinHandle, IOID_23, 1);
            PIN_setOutputValue(muxPinHandle, IOID_12, 1);
            PIN_setOutputValue(muxPinHandle, IOID_15, 0);
            break;
        case 7: // sensor 7 array pin 7
            PIN_setOutputValue(muxPinHandle, IOID_21, 0); //E
            PIN_setOutputValue(muxPinHandle, IOID_22, 0);
            PIN_setOutputValue(muxPinHandle, IOID_23, 1);
            PIN_setOutputValue(muxPinHandle, IOID_12, 1);
            PIN_setOutputValue(muxPinHandle, IOID_15, 1);
            break;
        case 4: // sensor 8 array pin 4
            PIN_setOutputValue(muxPinHandle, IOID_21, 0); //E
            PIN_setOutputValue(muxPinHandle, IOID_22, 1);
            PIN_setOutputValue(muxPinHandle, IOID_23, 0);
            PIN_setOutputValue(muxPinHandle, IOID_12, 0);
            PIN_setOutputValue(muxPinHandle, IOID_15, 0);
            break;
        case 6: //sensor 9 array pin 6
            PIN_setOutputValue(muxPinHandle, IOID_21, 0); //E
            PIN_setOutputValue(muxPinHandle, IOID_22, 1);
            PIN_setOutputValue(muxPinHandle, IOID_23, 0);
            PIN_setOutputValue(muxPinHandle, IOID_12, 0);
            PIN_setOutputValue(muxPinHandle, IOID_15, 1);
            break;
        case 0: // sensor 10 array pin 0
            PIN_setOutputValue(muxPinHandle, IOID_21, 0); //E
            PIN_setOutputValue(muxPinHandle, IOID_22, 1);
            PIN_setOutputValue(muxPinHandle, IOID_23, 0);
            PIN_setOutputValue(muxPinHandle, IOID_12, 1);
            PIN_setOutputValue(muxPinHandle, IOID_15, 0);
            break;
        case 5: // sensor 11 array pin 5
            PIN_setOutputValue(muxPinHandle, IOID_21, 0); //E
            PIN_setOutputValue(muxPinHandle, IOID_22, 1);
            PIN_setOutputValue(muxPinHandle, IOID_23, 0);
            PIN_setOutputValue(muxPinHandle, IOID_12, 1);
            PIN_setOutputValue(muxPinHandle, IOID_15, 1);
            break;
        case 2: // sensor 12 array pin 2
            PIN_setOutputValue(muxPinHandle, IOID_21, 0); //E
            PIN_setOutputValue(muxPinHandle, IOID_22, 1);
            PIN_setOutputValue(muxPinHandle, IOID_23, 1);
            PIN_setOutputValue(muxPinHandle, IOID_12, 0);
            PIN_setOutputValue(muxPinHandle, IOID_15, 0);
            break;
        case 3: // sensor 13 array pin 3
            PIN_setOutputValue(muxPinHandle, IOID_21, 0); //E
            PIN_setOutputValue(muxPinHandle, IOID_22, 1);
            PIN_setOutputValue(muxPinHandle, IOID_23, 1);
            PIN_setOutputValue(muxPinHandle, IOID_12, 0);
            PIN_setOutputValue(muxPinHandle, IOID_15, 1);
            break;
        case 1: // sensor 14 array pin 1
            PIN_setOutputValue(muxPinHandle, IOID_21, 0); //E
            PIN_setOutputValue(muxPinHandle, IOID_22, 1);
            PIN_setOutputValue(muxPinHandle, IOID_23, 1);
            PIN_setOutputValue(muxPinHandle, IOID_12, 1);
            PIN_setOutputValue(muxPinHandle, IOID_15, 0);
            break;
        case 9: // sensor 15 array pin 9
            PIN_setOutputValue(muxPinHandle, IOID_21, 0); //E
            PIN_setOutputValue(muxPinHandle, IOID_22, 1);
            PIN_setOutputValue(muxPinHandle, IOID_23, 1);
            PIN_setOutputValue(muxPinHandle, IOID_12, 1);
            PIN_setOutputValue(muxPinHandle, IOID_15, 1);
            break;
    }
}

void DACtimerCallback(GPTimerCC26XX_Handle handle, GPTimerCC26XX_IntMask interruptMask) {

    if(counterDAC == 0){
        counterDAC++; //increments counter to 1
    }
    else if (counterDAC == 1){
        Signal.ampAC = lastAmp[muxmod]/2; //Signal goes high, i.e. positive
        txBuffer1[0] = Signal.ampAC >> 8; //hi byte
        txBuffer1[1] = Signal.ampAC; //lower 2 bytes
        I2C_transfer(I2Chandle, &i2cTrans1);
        counterDAC++;
    }
    else if (counterDAC == 2){
        muxmod = muxidx % channels; //get remainder of muxidx for switch
        // this code moved lower to account for stutter code
        // muxidx += 1; increment counter note: this happens after we have already set pot and sensor in case 2
//        if(muxidx == channels){
//            muxidx = 0; // reset counter back to zero, if it equals the number of channels
//        }
        // storage_buffer_length = 0;
        streaming_buffer_length = 0;

        float amp; uint8_t ampFactor = 3;

        if (uartTxBufferOffset < UARTBUFFERSIZE) {
            amp = ADC_convertRawToMicroVolts(adc,lastAmp[muxmod])/ampFactor;
        }

        ////////// ADC Read ///////////
        int res1; uint32_t adcVal;
        res1 = ADC_convert(adc, &adcValue);
        if (res1 == ADC_STATUS_SUCCESS) {
            adcVal = ADC_convertRawToMicroVolts(adc,adcValue);
        }


        txBuffer1[0] = 0; //hi byte
        txBuffer1[1] = 0; //lower 2 bytes
        //txBuffer2[0] = Signal.ampDC >> 8; //hi byte
        //txBuffer2[1] = Signal.ampDC; //lower 2 bytes
        I2C_transfer(I2Chandle, &i2cTrans1);
        //I2C_transfer(I2Chandle, &i2cTrans2);

        //////////ADC Stutter ////////// -- JR
//          we removed the stutter because it is untested
//        if ( (adcValue < 2950) || (stutter > 3) ) { //Run normal process if adc Value is below the upper fence, or if we have already stuttered 3 times
            muxidx += 1; // increment counter note: this happens after we have already set pot and sensor in case 2
            if(muxidx == channels){
                muxidx = 0; // reset counter back to zero, if it equals the number of channels
                }

        // gain = (float)adcVal/amp;

            if (adcValue < 400){
                impedance = 49999.99;
            }

                    else if (sensorValues[muxmod] == 24){
                        impedance = fabs((-226.6 * adcValue + 644686)/(adcValue + -414.9));
                    }
                    else if (sensorValues[muxmod] == 32){
                        impedance = fabs((-186.3 * adcValue + 699935)/(adcValue + -480.1));
                    }
                    else if (sensorValues[muxmod] == 45){
                        impedance = fabs((-175.6 * adcValue + 919799)/(adcValue + -485.5));
                    }
                    else if (sensorValues[muxmod] == 60){
                        impedance = fabs((-31.3 * adcValue + 928390)/(adcValue + -508.0));
                    }
                    else if (sensorValues[muxmod] == 125){
                        impedance = fabs((-482.8 * adcValue + 2892453)/(adcValue + -447.2));
                    }
                    else if (sensorValues[muxmod] == 200){
                        impedance = fabs((-592.0 * adcValue + 4185201)/(adcValue + -472.1));
                    }
            if (impedance > 49999.99){
                impedance = 49999.99;
            }


            if (serializer_isFull()) serializer_setTimestamp((uint32_t)milliseconds);
            serializer_addImpedance(impedance);
            if (serializer_isFull() && Semaphore_pend(bacpac_channel_mutex, 0)) {
                streaming_buffer_length += serializer_serialize(streaming_buffer);
                serializer_serializeReadable(uartBuf);
                print(uartBuf);
                Semaphore_post(bacpac_channel_mailbox);
            }

            GPIO_write(Board_GPIO_LED1, Board_GPIO_LED_OFF);

        ////////// Changes tap value if necessary //////////
            if (gain < lowCuts[currentTap[muxmod]])
            {
                currentTap[muxmod]++;
                sensorValues[muxmod] = taps[currentTap[muxmod]];
            }
            else if (gain > highCuts[currentTap[muxmod]])
            {
                currentTap[muxmod]--;
                sensorValues[muxmod] = taps[currentTap[muxmod]];
            }
            if (currentTap[muxmod] > 6)
            {
                currentTap[muxmod] = 6;
                sensorValues[muxmod] = taps[currentTap[muxmod]];
            }
            else if (currentTap[muxmod] < 1)
            {
                currentTap[muxmod] = 1;
                sensorValues[muxmod] = taps[currentTap[muxmod]];
            }
//          removed because untested
//            stutter = 0; //The ADC value is below 2950, so no stuttering occured
//        }
//
//        else {  //Stutter the code and move down in the tap if the ADC value is too high
//                    currentTap[muxmod]--;
//                    stutter++;
//                }


        counterDATA += 1; //increment sample counter once finished
        counterDAC++; //increments counter to 2
    }
    else if (counterDAC == 3) {
        ReplaceTheMess_GS(muxidx);

        ////////// Set potentiometer value for next read //////////
        txBuffer3[0] = 0;
        txBuffer3[1] = sensorValues[muxidx];

        // this helps modify the buffer to output time stamp, tap value, impedences

        I2C_transfer(I2Chandle, &i2cTrans3);

        ////////// Updates milliseconds variable //////////
        milliseconds = milliseconds + PERIOD_OF_TIME;
        counterDAC = 0; // Reset counter to case 0
    }
}

void Sensors_start_timers() {
    milliseconds = 0;
    GPTimerCC26XX_start(hDACTimer);
}

void Sensors_stop_timers() {
    // GPTimerCC26XX_stop(hMUXTimer);
    serializer_clear();
    GPTimerCC26XX_stop(hDACTimer);
}

void DA_get_status(int status_code, char* message) {
    switch (status_code) {
        case DISK_NULL_HANDLE:
            System_sprintf(uartBuf, "%s: SD handle null\n\0", message);
            break;
        case DISK_FAILED_INIT:
            System_sprintf(uartBuf, "%s: Failed to initialize SD card\n\0", message);
            break;
        case DISK_FAILED_READ:
            System_sprintf(uartBuf, "%s: Sector reading error\n\0", message);
            break;
        case DISK_FAILED_WRITE:
            System_sprintf(uartBuf, "%s: Sector writing error\n\0", message);
            break;
        case DISK_SUCCESS:
            System_sprintf(uartBuf, "%s: Success\n\0", message);
            break;
        case DISK_LOCKED:
            System_sprintf(uartBuf, "%s: Disk locked\n\0", message);
            break;
        default:
            System_sprintf(uartBuf, "%s: Unknown status: %d\n\0", message, status_code);
   }
    UART_write(uart, uartBuf, strlen(uartBuf));
}

void print(char* str) {
    UART_write(uart, str, strlen(str));
}


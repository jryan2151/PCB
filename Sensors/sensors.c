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
char* myBuf;
int clockticks = 0;
uint_fast16_t uartTxBufferOffset = 0; // ???

uint8_t DEVICENUM = 1;
const int channels = 16; //change to const in channels = 16; ???
//int lastAmp[1] = {0}; //initialize to the value you want to start the signal2 at (must be as long as channel)
static int MUXFREQ = 200;  //600 (maybe not good for bluetooth so probably don't change ??? //Switching frequency (this equals the number of channels to read each second). Must be less than half of DAC frequency (~line 320).


// CAP'N'S LOG: ADDED BY GABE
static float PERIOD = 3.0592303;
float MILLISECONDS = 0;
uint8_t sensorValues[channels] = {100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100}; //initial tap value for each sensor
int taps[8] = {1,5,15,35,60,100,150,155}; // The discrete tap values that we want to use, the 1 and 155 on the ends are for error handling and should never actually be used
int currentTap[channels] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}; //stores the tap value for each sensor so we can have the right tap for each read.
float lowCuts[8] = {0,8,9,10.5,10.5,12,0,0}; // the gain value at which we will switch to the next tap value because the gain is getting too low
float highCuts[8] = {0,0,12.5,14.5,15,15,15,0}; // the gain value at which we will switch to the previous tap value because the gain is getting too high
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
    // muxmod = muxidx % channels; //get remainder of muxidx for switch // ??? Commented out in Joseph's code
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
    myBuf = (char*) malloc(64 * sizeof(char));
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

    // GABE DELETED SOMETHING FROM HERE

    Types_FreqHz  freq2;
    BIOS_getCpuFreq(&freq2);
    char buf[32];
    System_sprintf(buf, "%u\n", freq2.lo);
    print(buf);


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

void Sensors_write_test() {
    int t1 = Timestamp_get32();
    int res = da_write("Simple Peripheral sd card write test. Please work for me======\n\0", 64);
    if (res == 1) {
        int t2 = Timestamp_get32();

        System_sprintf(myBuf, "Write in %d clock cycles\n\0", t2 - t1);
        UART_write(uart, myBuf, strlen(myBuf));
    }
    else DA_get_status(res, "Writing Card");

}

void Sensors_read_test() {
    int res = da_read(myBuf, 64);
    if (res == 1) UART_write(uart, myBuf, 64);
    else DA_get_status(res, "Reading card");
}

void Sensors_size_test() {
    System_sprintf(myBuf, "s size: %d num s: %d\n\0", da_get_sector_size(), da_get_num_sectors());
    UART_write(uart, myBuf, strlen(myBuf));
}

void Sensors_pos_test() {
    char myBuf[64];
    System_sprintf(myBuf, "read pos: %d write pos: %d\n\0", da_get_read_pos(), da_get_write_pos());
    UART_write(uart, myBuf, strlen(myBuf));
}

void Sensors_clear_test() {
    DA_get_status(da_clear(), "Clearing card");
}

void Sensors_load_test() {
    DA_get_status(da_load(), "Loading card");
}

void Sensors_close_test() {
    DA_get_status(da_close(), "Closing card");
}

void Sensors_timer_test() {
    DACtimerCallback(NULL, NULL);
}

void hello_world() {
    UART_write(uart, "hello world\n", 12);
}

void hello_there() {
    UART_write(uart, "Hello there!\n", 13);
}

void ReplaceTheMess_GS(uint8_t muxidx_GS){
    switch(muxidx_GS) {
        case 0: //2
            PIN_setOutputValue(muxPinHandle, IOID_21, 0); //E
            PIN_setOutputValue(muxPinHandle, IOID_22, 0); //S3
            PIN_setOutputValue(muxPinHandle, IOID_23, 0); //S2
            PIN_setOutputValue(muxPinHandle, IOID_12, 0); //S1
            PIN_setOutputValue(muxPinHandle, IOID_15, 0); //S0
            break;
        case 1: //4
            PIN_setOutputValue(muxPinHandle, IOID_21, 0); //E
            PIN_setOutputValue(muxPinHandle, IOID_22, 0);
            PIN_setOutputValue(muxPinHandle, IOID_23, 0);
            PIN_setOutputValue(muxPinHandle, IOID_12, 0);
            PIN_setOutputValue(muxPinHandle, IOID_15, 1);
            break;
        case 2: //6
            PIN_setOutputValue(muxPinHandle, IOID_21, 0); //E
            PIN_setOutputValue(muxPinHandle, IOID_22, 0);
            PIN_setOutputValue(muxPinHandle, IOID_23, 0);
            PIN_setOutputValue(muxPinHandle, IOID_12, 1);
            PIN_setOutputValue(muxPinHandle, IOID_15, 0);
            break;
        case 3: //8
            PIN_setOutputValue(muxPinHandle, IOID_21, 0); //E
            PIN_setOutputValue(muxPinHandle, IOID_22, 0);
            PIN_setOutputValue(muxPinHandle, IOID_23, 0);
            PIN_setOutputValue(muxPinHandle, IOID_12, 1);
            PIN_setOutputValue(muxPinHandle, IOID_15, 1);
            break;
        case 4: //10
            PIN_setOutputValue(muxPinHandle, IOID_21, 0); //E
            PIN_setOutputValue(muxPinHandle, IOID_22, 0);
            PIN_setOutputValue(muxPinHandle, IOID_23, 1);
            PIN_setOutputValue(muxPinHandle, IOID_12, 0);
            PIN_setOutputValue(muxPinHandle, IOID_15, 0);
            break;
        case 5: //12
            PIN_setOutputValue(muxPinHandle, IOID_21, 0); //E
            PIN_setOutputValue(muxPinHandle, IOID_22, 0);
            PIN_setOutputValue(muxPinHandle, IOID_23, 1);
            PIN_setOutputValue(muxPinHandle, IOID_12, 0);
            PIN_setOutputValue(muxPinHandle, IOID_15, 1);
            break;
        case 6: //14
            PIN_setOutputValue(muxPinHandle, IOID_21, 0); //E
            PIN_setOutputValue(muxPinHandle, IOID_22, 0);
            PIN_setOutputValue(muxPinHandle, IOID_23, 1);
            PIN_setOutputValue(muxPinHandle, IOID_12, 1);
            PIN_setOutputValue(muxPinHandle, IOID_15, 0);
            break;
        case 7: //16
            PIN_setOutputValue(muxPinHandle, IOID_21, 0); //E
            PIN_setOutputValue(muxPinHandle, IOID_22, 0);
            PIN_setOutputValue(muxPinHandle, IOID_23, 1);
            PIN_setOutputValue(muxPinHandle, IOID_12, 1);
            PIN_setOutputValue(muxPinHandle, IOID_15, 1);
            break;
        case 15: //15
            PIN_setOutputValue(muxPinHandle, IOID_21, 0); //E
            PIN_setOutputValue(muxPinHandle, IOID_22, 1);
            PIN_setOutputValue(muxPinHandle, IOID_23, 0);
            PIN_setOutputValue(muxPinHandle, IOID_12, 0);
            PIN_setOutputValue(muxPinHandle, IOID_15, 0);
            break;
        case 14: //13
            PIN_setOutputValue(muxPinHandle, IOID_21, 0); //E
            PIN_setOutputValue(muxPinHandle, IOID_22, 1);
            PIN_setOutputValue(muxPinHandle, IOID_23, 0);
            PIN_setOutputValue(muxPinHandle, IOID_12, 0);
            PIN_setOutputValue(muxPinHandle, IOID_15, 1);
            break;
        case 13: //11
            PIN_setOutputValue(muxPinHandle, IOID_21, 0); //E
            PIN_setOutputValue(muxPinHandle, IOID_22, 1);
            PIN_setOutputValue(muxPinHandle, IOID_23, 0);
            PIN_setOutputValue(muxPinHandle, IOID_12, 1);
            PIN_setOutputValue(muxPinHandle, IOID_15, 0);
            break;
        case 12: //9
            PIN_setOutputValue(muxPinHandle, IOID_21, 0); //E
            PIN_setOutputValue(muxPinHandle, IOID_22, 1);
            PIN_setOutputValue(muxPinHandle, IOID_23, 0);
            PIN_setOutputValue(muxPinHandle, IOID_12, 1);
            PIN_setOutputValue(muxPinHandle, IOID_15, 1);
            break;
        case 11: //7
            PIN_setOutputValue(muxPinHandle, IOID_21, 0); //E
            PIN_setOutputValue(muxPinHandle, IOID_22, 1);
            PIN_setOutputValue(muxPinHandle, IOID_23, 1);
            PIN_setOutputValue(muxPinHandle, IOID_12, 0);
            PIN_setOutputValue(muxPinHandle, IOID_15, 0);
            break;
        case 10: //5
            PIN_setOutputValue(muxPinHandle, IOID_21, 0); //E
            PIN_setOutputValue(muxPinHandle, IOID_22, 1);
            PIN_setOutputValue(muxPinHandle, IOID_23, 1);
            PIN_setOutputValue(muxPinHandle, IOID_12, 0);
            PIN_setOutputValue(muxPinHandle, IOID_15, 1);
            break;
        case 9: //3
            PIN_setOutputValue(muxPinHandle, IOID_21, 0); //E
            PIN_setOutputValue(muxPinHandle, IOID_22, 1);
            PIN_setOutputValue(muxPinHandle, IOID_23, 1);
            PIN_setOutputValue(muxPinHandle, IOID_12, 1);
            PIN_setOutputValue(muxPinHandle, IOID_15, 0);
            break;
        case 8: //1
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
        muxidx += 1; // increment counter note: this happens after we have already set pot and sensor in case 2
        if(muxidx == channels){
            muxidx = 0; // reset counter back to zero, if it equals the number of channels
        }
        storage_buffer_length = 0;

        float amp; uint8_t ampFactor = 3;

        if (uartTxBufferOffset < UARTBUFFERSIZE) {
            amp = ADC_convertRawToMicroVolts(adc,lastAmp[muxmod])/ampFactor;
            uint32_t ampBase = (uint32_t)amp;
            uint32_t ampDecimal = (uint32_t)(amp * 100) - (ampBase * 100);
            storage_buffer_length += System_sprintf(storage_buffer + storage_buffer_length, "%u,%u,%u.%u,", (uint32_t)MILLISECONDS, muxmod, ampBase, ampDecimal);
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

        gain = (float)adcVal/amp;

        if (gain == 5.92){
            impedance = 10000;
        }
        else if (sensorValues[muxmod] == 5){
            impedance = fabs((-177.5 * gain * gain + 3909 * gain + -17140)/(gain * gain + -11.95 * gain + 35.68));
        }
        else if (sensorValues[muxmod] == 15){
            impedance = fabs((-167.3 * gain * gain + 6123 * gain + -30850)/(gain * gain + -11.96 * gain + 35.77));
        }
        else if (sensorValues[muxmod] == 35){
            impedance = fabs((-176.2 * gain * gain + 10770 * gain + -58910)/(gain * gain + -12 * gain + 36.01));
        }
        else if (sensorValues[muxmod] == 60){
            impedance = fabs((-170 * gain * gain + 16450 * gain + -94500)/(gain * gain + -12.08 * gain + 36.46));
        }
        else if (sensorValues[muxmod] == 100){
            impedance = fabs((-172.8 * gain * gain + 25750 * gain + -157100)/(gain * gain + -12.3 * gain + 37.8));
        }
        else if (sensorValues[muxmod] == 150){
            impedance = fabs(( -684.2 * gain + 43550)/(gain + -5.773));
        }
        if (impedance > 49999.99){
            impedance = 49999.99;
        }
        // THIS IS THE POSSIBLE LOWER LIMIT OF THE BLOCK COMMENT (FUNCTIONING) //
        //
        ////////// Continues to write to the UART Buffer /////////
        uint32_t impedanceBase = (uint32_t)impedance;
        uint32_t impedanceDecimal = (uint32_t)(impedance * 1000) - (impedanceBase * 1000);

        uint32_t gainBase = (uint32_t)gain;
        uint32_t gainDecimal = (uint32_t)(gain * 100) - (gain * 100);
        storage_buffer_length += System_sprintf(storage_buffer + storage_buffer_length, "%u.%u,%u.%u,%u,%u\n", impedanceBase, impedanceDecimal, gainBase, gainDecimal, sensorValues[muxmod], adcValue);

        // CAP'N'S LOG: I'VE NARROWED DOWN PROBLEMS TO THE LINES COMMENTED OUT, INCLUDING THE SIX fabs
        // AND THE FOUR snprintf FUNCTIONS. I SUSPECT A PROBLEM WITH THESE.
        GPIO_write(Board_GPIO_LED1, Board_GPIO_LED_OFF);

        // THIS IS THE LOWER LIMIT OF THE BLOCK COMMENT (FUNCTIONING) //

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


        counterDATA += 1; //increment sample counter once finished
        counterDAC++; //increments counter to 2
    }
    else if (counterDAC == 3) {
        ReplaceTheMess_GS(muxidx);

        ////////// Set potentiometer value for next read //////////
        txBuffer3[0] = 0;
        txBuffer3[1] = sensorValues[muxidx];
        I2C_transfer(I2Chandle, &i2cTrans3);

        ////////// Display the data via UART ///////////
        if (Semaphore_pend(storage_buffer_mutex, 0)) {
            UART_write(uart, storage_buffer, storage_buffer_length);
            Semaphore_post(storage_buffer_mailbox);
        }

        ////////// Updates milliseconds variable //////////
        MILLISECONDS = MILLISECONDS + PERIOD;
        counterDAC = 0; // Reset counter to case 0
    }
}

void Sensors_start_timers() {
    // GPTimerCC26XX_start(hMUXTimer);
    GPTimerCC26XX_start(hDACTimer);
}

void Sensors_stop_timers() {
    // GPTimerCC26XX_stop(hMUXTimer);
    GPTimerCC26XX_stop(hDACTimer);
}

void DA_get_status(int status_code, char* message) {
    switch (status_code) {
        case DISK_NULL_HANDLE:
            System_sprintf(myBuf, "%s: SD handle null\n\0", message);
            break;
        case DISK_FAILED_INIT:
            System_sprintf(myBuf, "%s: Failed to initialize SD card\n\0", message);
            break;
        case DISK_FAILED_READ:
            System_sprintf(myBuf, "%s: Sector reading error\n\0", message);
            break;
        case DISK_FAILED_WRITE:
            System_sprintf(myBuf, "%s: Sector writing error\n\0", message);
            break;
        case DISK_SUCCESS:
            System_sprintf(myBuf, "%s: Success\n\0", message);
            break;
        case DISK_LOCKED:
            System_sprintf(myBuf, "%s: Disk locked\n\0", message);
            break;
        default:
            System_sprintf(myBuf, "%s: Unknown status: %d\n\0", message, status_code);
   }
    UART_write(uart, myBuf, strlen(myBuf));
}

void print(char* str) {
    UART_write(uart, str, strlen(str));
}


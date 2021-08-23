/*
 * Copyright (c) 2015-2019, Texas Instruments Incorporated
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
#include <ti/drivers/SD.h>
#include <xdc/runtime/System.h>


/* Board Header file */
#include "Board.h"
#include "DiskAccess.h"

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

uint8_t DEVICENUM = 1;
int channels = 1;
int lastAmp[1] = {0}; //initialize to the value you want to start the signal2 at (must be as long as channel)
static int MUXFREQ = 200; //Switching frequency (this equals the number of channels to read each second). Must be less than half of DAC frequency (~line 320).
#define ADC_SAMPLE_COUNT    (1) //Number of samples to read each time we call the callback function (how many samples per row on output)
#define ADCMULTIPLE         (1) //How many times to call the ADC within one mux switch (total samples per switch will equal ADCMULTIPLE*ADC_SAMPLE_COUNT)
#define ADChiLimit          3000 //raw value that will be the threshold
#define ADCloLimit          500 //raw value that will be the threshold
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
        muxmod = muxidx % channels; //get remainder of muxidx for switch
    switch(muxmod) {
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
bool transferDone = false;
bool openDone = true;
uint8_t counterDAC = 0;
uint8_t counterDATA = 0;

struct { //Used to store the signal2 amplitude (max is 4095)
    uint16_t ampAC : 12;
    uint16_t ampDC : 12;
} signal2;

// Function Declarations
static void i2cWriteCallback(I2C_Handle handle, I2C_Transaction *transac, bool result);
void DACtimerCallback(GPTimerCC26XX_Handle handle, GPTimerCC26XX_IntMask interruptMask);


/* Driver handles */
GPTimerCC26XX_Handle hDACTimer;
I2C_Handle I2Chandle;
I2C_Params I2Cparams;
I2C_Transaction i2cTrans1;
I2C_Transaction i2cTrans2;

///////////////////////////////////// ADC/ Display Preamble /////////////////////////////////
/* ADC Global Variables */
uint16_t trigger = 0;
int_fast16_t res;
ADC_Handle adc;
ADC_Params params;

#define UARTBUFFERSIZE   ((20 * ADC_SAMPLE_COUNT) + 24)
//double adcValue[ADC_SAMPLE_COUNT];
int modBuffer[ADC_SAMPLE_COUNT];
char uartTxBuffer[UARTBUFFERSIZE];

UART_Handle uart;

// Callback function to use the UART in callback mode. It does nothing.
void uartCallback(UART_Handle handle, void *buf, size_t count) { return; }

/*
 *  ======== mainThread ========
 */
//void *mainThread(void *arg0)
//static void mainThread(UArg a0, UArg a1)
void Sensors_init()
{
    // Initialize Variables
    signal2.ampAC = lastAmp;

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
    GPTimerCC26XX_Value loadValDAC = 48000000/(MUXFREQ*2);
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

    signal2.ampAC = lastAmp[muxmod];
    signal2.ampDC = signal2.ampAC/2;
    txBuffer1[0] = signal2.ampAC >> 8; //hi byte
	txBuffer1[1] = signal2.ampAC; //lower 2 bytes
	txBuffer2[0] = signal2.ampDC >> 8; //hi byte
	txBuffer2[1] = signal2.ampDC; //lower 2 bytes
    I2C_transfer(I2Chandle, &i2cTrans1);
    I2C_transfer(I2Chandle, &i2cTrans2);

////////////////////////////////////////////////////////////////// MUX //////////////////////////////////////////////////////////
    muxPinHandle = PIN_open(&muxPinState, muxPinTable);
    if(!muxPinHandle) {
        /* Error initializing mux output pins */
        while(1);
    }
    PIN_setOutputValue(muxPinHandle, IOID_28, 0);



  GPTimerCC26XX_Params paramsMUX;
  GPTimerCC26XX_Params_init(&paramsMUX);
  paramsMUX.width          = GPT_CONFIG_32BIT;
  paramsMUX.mode           = GPT_MODE_PERIODIC_UP;
  paramsMUX.debugStallMode = GPTimerCC26XX_DEBUG_STALL_OFF;
  hMUXTimer = GPTimerCC26XX_open(CC2640R2_LAUNCHXL_GPTIMER1A, &paramsMUX); //Need timer 0A for ADCbuf

  if(hMUXTimer == NULL) {
    Task_exit();
  }

  GPTimerCC26XX_Value loadValMUX = 48000000/MUXFREQ;
  loadValMUX = loadValMUX - 1;
  GPTimerCC26XX_setLoadValue(hMUXTimer, loadValMUX);
  GPTimerCC26XX_registerInterrupt(hMUXTimer, MUXtimerCallback, GPT_INT_TIMEOUT);

////////////////////////////////////////////////////////////////// ADC/ UART //////////////////////////////////////////////////////////
    /* Create a UART with data processing off. */
    UART_Params uartParams;
    UART_init();
    UART_Params_init(&uartParams);
    uartParams.writeDataMode = UART_DATA_BINARY;
    uartParams.writeMode = /*UART_MODE_BLOCKING;*/UART_MODE_CALLBACK;
    uartParams.writeCallback = uartCallback;
    uartParams.baudRate = 230400;
    //uartParams.baudRate = 115200;
    uart = UART_open(Board_UART0, &uartParams);


    ADC_Params_init(&params);
    adc = ADC_open(Board_ADC0, &params);// ADC0 uses IDIO_25 (change in cc26xx.c file in ADC section by commenting things out)
    if (adc == NULL) {
        // Error initializing ADC channel 0
        return;
    }

    Sensors_load_test();
}

/////////////////////////////////////////// I2C Functions /////////////////////////////////////////////////
static void i2cWriteCallback(I2C_Handle handle, I2C_Transaction *transac, bool result){
    // Set length bytes
    if (result) {
        transferDone = true;
    } else {
        // Transaction failed, act accordingly...
        transferDone = false;
    }
};

void Sensors_write_test() {
    UART_write(uart, "Write test\n", 12);
    da_write("Simple Peripheral sd card write test. Please work for me======\n\0", 64);
}

void Sensors_read_test() {
    char myBuf[64];
    da_read(myBuf, 64);
    UART_write(uart, myBuf, 64);
}

void Sensors_size_test() {
    char myBuf[64];
    System_sprintf(myBuf, "s size: %d num s: %d\n\0", da_get_sector_size(), da_get_num_sectors());
    UART_write(uart, myBuf, strlen(myBuf));
}

void Sensors_pos_test() {
    char myBuf[64];
    System_sprintf(myBuf, "read pos: %d write pos: %d\n\0", da_get_read_pos(), da_get_write_pos());
    UART_write(uart, myBuf, strlen(myBuf));
}

void Sensors_clear_test() {
    UART_write(uart, "Clear test\n", 12);
    da_clear();
}

void Sensors_load_test() {
    int res = da_load();
    if (res == -1) {
        UART_write(uart, "Loading sd card: Card handle null\n", 35);
        return;
    }
    else if (res == -2) {
        UART_write(uart, "Loading sd card: Status returned failure\n", 42);
        return;
    }
    else if (res == -3) {
        UART_write(uart, "Loading sd card: Unable to read first sector\n", 46);
        return;
    }
    else if (res == 1) {
        UART_write(uart, "Loading sd card: Success\n", 26);
    }
    else {
        UART_write(uart, "Loading sd card: Unknown error\n", 32);
        return;
    }
}

void Sensors_close_test() {
    UART_write(uart, "Close test\n", 12);
    da_close();
}

void DACtimerCallback(GPTimerCC26XX_Handle handle, GPTimerCC26XX_IntMask interruptMask) {
    // interrupt callback code goes here. Minimize processing in interrupt.
    //GPIO_toggle(Board_GPIO_LED0);
    //GPIO_write(Board_GPIO_LED0, Board_GPIO_LED_ON);

    if (counterDAC%2==0){
        if (lastAmp[muxmod]==signal2.ampAC){
            // signal2 goes high
            // Do I2C transfer (in callback mode)
            txBuffer1[0] = signal2.ampAC >> 8; //hi byte
	        txBuffer1[1] = signal2.ampAC; //lower 2 bytes
        }else{ // Change to a new magnitude
            signal2.ampAC = lastAmp[muxmod];
            signal2.ampDC = signal2.ampAC/2;
            txBuffer1[0] = signal2.ampAC >> 8; //hi byte
	        txBuffer1[1] = signal2.ampAC; //lower 2 bytes
	        txBuffer2[0] = signal2.ampDC >> 8; //hi byte
	        txBuffer2[1] = signal2.ampDC; //lower 2 bytes
	        I2C_transfer(I2Chandle, &i2cTrans2);
        }
    }else{
        // signal2 goes to zero
        // Do I2C transfer (in callback mode)
        //signal2.ampAC = 0;
        txBuffer1[0] = 0; //hi byte
	   txBuffer1[1] = 0; //lower 2 bytes
    }
    I2C_transfer(I2Chandle, &i2cTrans1);
    if(counterDAC == 2){
        counterDAC = 0; //reset counter back to zero, if it equals the 2
    }else{
        //uint16_t     i;
        uint_fast16_t uartTxBufferOffset = 0;
        char uartTxBuffer[UARTBUFFERSIZE] = {0};

        float amp = 0;
        uint8_t ampFactor = 3;
        int res1 = 0;
        uint32_t adcVal = 0;

        if (uartTxBufferOffset < UARTBUFFERSIZE) {
            amp = ADC_convertRawToMicroVolts(adc,lastAmp[muxmod])/ampFactor;

            uartTxBufferOffset += snprintf(uartTxBuffer + uartTxBufferOffset,UARTBUFFERSIZE - uartTxBufferOffset, "%u,",(uint8_t)counterDATA); // outputs sample number
            uartTxBufferOffset += snprintf(uartTxBuffer + uartTxBufferOffset,UARTBUFFERSIZE - uartTxBufferOffset, "%u,",(uint8_t)muxmod); // outputs channel number
        }

        res1 = ADC_convert(adc, &adcValue);

        if (res1 == ADC_STATUS_SUCCESS) {
            adcVal = ADC_convertRawToMicroVolts(adc,adcValue);
        }

        avg = adcVal;
        gain = (float)avg/amp;

        uartTxBufferOffset += snprintf(uartTxBuffer + uartTxBufferOffset,UARTBUFFERSIZE - uartTxBufferOffset, "%.2f,",(float)gain); // outputs gain value

        GPIO_write(Board_GPIO_LED1, Board_GPIO_LED_OFF);
            /*
        * Ensure we don't write outside the buffer.
        * Append a newline after the data.
        */
        if (uartTxBufferOffset < UARTBUFFERSIZE) {
            uartTxBuffer[uartTxBufferOffset++] = '\n';
        }
        else {
            uartTxBuffer[UARTBUFFERSIZE-1] = '\n';
        }

        /* Display the data via UART */

         UART_write(uart, uartTxBuffer, uartTxBufferOffset);
         da_write(uartTxBuffer, uartTxBufferOffset);

        counterDATA += 1; //increment sample counter once finished

        //Check the magnitude of lastAmp[muxmod] and modulate it if necessary
        if (adcValue < ADCloLimit) {
            lastAmp[muxmod] += 10;
        } else if (adcValue > ADChiLimit){
            lastAmp[muxmod] -= 10;
        }
        if (adcValue < 100){
            lastAmp[muxmod] = minVOLT;
        }

        if (gain < 4){
            lastAmp[muxmod] = adcValue/5;
        }
    }
    counterDAC += 1;

//Check the magnitude of lastAmp[muxmod] and modulate it if necessary
        if (adcValue < ADCloLimit) {
            lastAmp[muxmod] += 10;
        } else if (adcValue > ADChiLimit){
            lastAmp[muxmod] -= 10;
        }
        if (adcValue < 100){
            lastAmp[muxmod] = minVOLT;
        }

        if (gain < 4){
            lastAmp[muxmod] = adcValue/5;
        }
    //GPIO_write(Board_GPIO_LED0, Board_GPIO_LED_OFF);



};

void Sensors_start_timers() {
    GPTimerCC26XX_start(hMUXTimer);
    GPTimerCC26XX_start(hDACTimer);
}

void Sensors_stop_timers() {
    GPTimerCC26XX_stop(hMUXTimer);
    GPTimerCC26XX_stop(hDACTimer);
}


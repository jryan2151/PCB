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

/* For usleep() */
//#include <unistd.h>
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



/* Board Header file */
#include "Board.h"

#include <pthread.h>


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
int lastAmp[1] = {0}; //initialize to the value you want to start the signal at (must be as long as channel)
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
//Task_Struct timerTask;
//char timerTaskStack[512];

GPTimerCC26XX_Handle hMUXTimer;
void MUXtimerCallback(GPTimerCC26XX_Handle handle, GPTimerCC26XX_IntMask interruptMask) {
    // interrupt callback code goes here. Minimize processing in interrupt.
    //GPIO_toggle(Board_GPIO_LED1);
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
    //GPIO_toggle(Board_GPIO_LED1);
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

struct { //Used to store the signal amplitude (max is 4095)
    uint16_t ampAC : 12;
    uint16_t ampDC : 12;
} signal;

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


/*
 * Callback function to use the UART in callback mode. It does nothing.
 */
void uartCallback(UART_Handle handle, void *buf, size_t count) {
   return;
}

/*
 *  ======== mainThread ========
 */
//void *mainThread(void *arg0)
static void mainThread(UArg a0, UArg a1)
{
    // Initialize Variables
    signal.ampAC = lastAmp;

    // Call Driver Init Functions
    I2C_init();
    ADC_init();
    GPIO_init();
    SD_init();

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
    i2cTrans1.writeBuf     = txBuffer1; //Square signal
    i2cTrans1.writeCount   = 2;
    i2cTrans1.readBuf      = NULL;
    i2cTrans1.readCount    = 0;
    i2cTrans1.slaveAddress = 0x4C; //hex converter: https://www.cs.princeton.edu/courses/archive/fall07/cos109/bc.html

    // Initialize master I2C transaction structure
    i2cTrans2.writeBuf     = txBuffer2; //DC Signal
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
    //GPTimerCC26XX_Value loadValDAC = freq.lo / 1000; //47999 = 1ms. 1 clock tick = 1/48e6
    //GPTimerCC26XX_Value loadValDAC = 48000000; //48e6 = 1 sec
    //GPTimerCC26XX_Value loadValDAC = 30000; //30e3 = 0.000625 sec = 1600 Hz (for 16 channels at 100 Hz)
    //GPTimerCC26XX_Value loadValDAC = 48000; //48e3 = 0.001 sec = 1000 Hz
    //GPTimerCC26XX_Value loadValDAC = 240000; //24e4 = 0.005 sec = 200 Hz
    //GPTimerCC26XX_Value loadValDAC = 320000; // 150 Hz
    //GPTimerCC26XX_Value loadValDAC = 480000; //48e4 = 0.01 sec = 100 Hz
    //GPTimerCC26XX_Value loadValDAC = 600000; //60e4 = 80 Hz
    //GPTimerCC26XX_Value loadValDAC = 960000; //96e4 = 0.02 sec = 50 Hz
    //GPTimerCC26XX_Value loadValDAC = 2400000; // 24e5 = 20 Hz
    //GPTimerCC26XX_Value loadValDAC = 4800000; //48e5 = 0.1 sec = 10 Hz
    //GPTimerCC26XX_Value loadValDAC = 24000000; //24e6 = 0.5 sec = 2 Hz
    //GPTimerCC26XX_Value loadValDAC = 48000000; //48e6 = 1 sec
    GPTimerCC26XX_Value loadValDAC = 48000000/(MUXFREQ*2);
    loadValDAC = loadValDAC - 1;
    GPTimerCC26XX_setLoadValue(hDACTimer, loadValDAC);
    GPTimerCC26XX_registerInterrupt(hDACTimer, DACtimerCallback, GPT_INT_TIMEOUT);

    GPTimerCC26XX_start(hDACTimer);

    /////////////////////////////////////////////////////////////////////////////////////////////
    // Open I2C
    I2Chandle = I2C_open(Board_I2C0, &I2Cparams);

    if (I2Chandle == NULL) {
        // Error opening I2C
        openDone = false;
        while (1);
    }

    signal.ampAC = lastAmp[muxmod];
    signal.ampDC = signal.ampAC/2;
    txBuffer1[0] = signal.ampAC >> 8; //hi byte
	txBuffer1[1] = signal.ampAC; //lower 2 bytes
	txBuffer2[0] = signal.ampDC >> 8; //hi byte
	txBuffer2[1] = signal.ampDC; //lower 2 bytes
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



  //GPTimerCC26XX_Value loadVal = freq.lo / 1000; //47999 = 1ms. 1 clock tick = 1/48e6
  //GPTimerCC26XX_Value loadVal = 48000000; //48e6 = 1 sec
  GPTimerCC26XX_Value loadValMUX = 48000000/MUXFREQ;
  loadValMUX = loadValMUX - 1;
  GPTimerCC26XX_setLoadValue(hMUXTimer, loadValMUX);
  GPTimerCC26XX_registerInterrupt(hMUXTimer, MUXtimerCallback, GPT_INT_TIMEOUT);


  GPTimerCC26XX_start(hMUXTimer);

////////////////////////////////////////////////////////////////// ADC/ UART //////////////////////////////////////////////////////////
    /* Create a UART with data processing off. */
    UART_Params uartParams;
    UART_init();
    UART_Params_init(&uartParams);
    uartParams.writeDataMode = UART_DATA_BINARY;
    uartParams.writeMode = UART_MODE_CALLBACK;
    uartParams.writeCallback = uartCallback;
    //uartParams.baudRate = 115200;
    uartParams.baudRate = 230400;
    //uartParams.baudRate = 460800;
    uart = UART_open(Board_UART0, &uartParams);

    ADC_Params_init(&params);
    adc = ADC_open(Board_ADC0, &params);// ADC0 uses IDIO_25 (change in cc26xx.c file in ADC section by commenting things out)
    if (adc == NULL) {
        // Error initializing ADC channel 0
        while (1);
    }

 ////////////////////////////////////// Set Up timer Based Interrupts /////////////////////////////////




  while(1) {
    Task_sleep(BIOS_WAIT_FOREVER);
    //sleep(1000);
  }
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

void DACtimerCallback(GPTimerCC26XX_Handle handle, GPTimerCC26XX_IntMask interruptMask) {
    // interrupt callback code goes here. Minimize processing in interrupt.
    GPIO_toggle(Board_GPIO_LED0);
    //GPIO_write(Board_GPIO_LED0, Board_GPIO_LED_ON);
    if (counterDAC%2==0){
        if (lastAmp[muxmod]==signal.ampAC){
            // Signal goes high
            // Do I2C transfer (in callback mode)
            txBuffer1[0] = signal.ampAC >> 8; //hi byte
	        txBuffer1[1] = signal.ampAC; //lower 2 bytes
        }else{ // Change to a new magnitude
            signal.ampAC = lastAmp[muxmod];
            signal.ampDC = signal.ampAC/2;
            txBuffer1[0] = signal.ampAC >> 8; //hi byte
	        txBuffer1[1] = signal.ampAC; //lower 2 bytes
	        txBuffer2[0] = signal.ampDC >> 8; //hi byte
	        txBuffer2[1] = signal.ampDC; //lower 2 bytes
	        I2C_transfer(I2Chandle, &i2cTrans2);
        }
    }else{
        // Signal goes to zero
        // Do I2C transfer (in callback mode)
        //signal.ampAC = 0;
        txBuffer1[0] = 0; //hi byte
	   txBuffer1[1] = 0; //lower 2 bytes
    }
    I2C_transfer(I2Chandle, &i2cTrans1);
    if(counterDAC == 2){
        counterDAC = 0; //reset counter back to zero, if it equals the 2
    }else{
        uint16_t     i;
        uint_fast16_t uartTxBufferOffset = 0;
        char uartTxBuffer[UARTBUFFERSIZE] = {0};

        float amp = 0;
        uint8_t ampFactor = 3;
        int res1 = 0;
        uint32_t adcVal = 0;

        //int c; //finagle a delay
        //for (c = 1; c <= 3200; c++)
        //    {}

        if (uartTxBufferOffset < UARTBUFFERSIZE) {
            //uartTxBufferOffset += snprintf(uartTxBuffer + uartTxBufferOffset, UARTBUFFERSIZE - uartTxBufferOffset, "\r\nChannel: ");
            amp = ADC_convertRawToMicroVolts(adc,lastAmp[muxmod])/ampFactor;
            //amp = lastAmp[muxmod]/ampFactor;

            //uartTxBufferOffset += snprintf(uartTxBuffer + uartTxBufferOffset,UARTBUFFERSIZE - uartTxBufferOffset, "%u,",(uint8_t)DEVICENUM); // outputs device number
            uartTxBufferOffset += snprintf(uartTxBuffer + uartTxBufferOffset,UARTBUFFERSIZE - uartTxBufferOffset, "%u,",(uint8_t)counterDATA); // outputs sample number
            uartTxBufferOffset += snprintf(uartTxBuffer + uartTxBufferOffset,UARTBUFFERSIZE - uartTxBufferOffset, "%u,",(uint8_t)muxmod); // outputs channel number
            //uartTxBufferOffset += snprintf(uartTxBuffer + uartTxBufferOffset,UARTBUFFERSIZE - uartTxBufferOffset, "%u,",(uint32_t)amp); // outputs input voltage
        }

        //GPIO_write(Board_GPIO_LED1, Board_GPIO_LED_ON);
        //double adcVal[ADC_SAMPLE_COUNT];

        //for (i = 0; i < ADC_SAMPLE_COUNT; i++) {
        //    res1 = ADC_convert(adc, &adcValue[i]);
                res1 = ADC_convert(adc, &adcValue);
            if (res1 == ADC_STATUS_SUCCESS) {
        //        adcVal[i] = ADC_convertRawToMicroVolts(adc,adcValue[i]);
                    adcVal = ADC_convertRawToMicroVolts(adc,adcValue);
                    /* Write channel number to the UART buffer if there is room. */
                //if (uartTxBufferOffset < UARTBUFFERSIZE) {
                    //uartTxBufferOffset += snprintf(uartTxBuffer + uartTxBufferOffset,UARTBUFFERSIZE - uartTxBufferOffset, "\rADC Reading: ");
                    //uartTxBufferOffset += snprintf(uartTxBuffer + uartTxBufferOffset,UARTBUFFERSIZE - uartTxBufferOffset, "%u,",(uint32_t)adcVal); // outputs output voltage
                //}
            }
        //}


        //double total=0;
        int j;//variable declaration
        //for(j = 0; j <= ADC_SAMPLE_COUNT; j++){
        //    total=total+adcVal[j];//loop for calculatin total
        //}
        //avg = total/j;//calculate average

        avg = adcVal;
        gain = (float)avg/amp;

        //uartTxBufferOffset += snprintf(uartTxBuffer + uartTxBufferOffset,UARTBUFFERSIZE - uartTxBufferOffset, "%u,",lastAmp[muxmod]); // outputs gain value
        //uartTxBufferOffset += snprintf(uartTxBuffer + uartTxBufferOffset,UARTBUFFERSIZE - uartTxBufferOffset, "%u,",adcValue); // outputs gain value
        uartTxBufferOffset += snprintf(uartTxBuffer + uartTxBufferOffset,UARTBUFFERSIZE - uartTxBufferOffset, "%.2f,",(float)gain); // outputs gain value
        //uartTxBufferOffset += snprintf(uartTxBuffer + uartTxBufferOffset,UARTBUFFERSIZE - uartTxBufferOffset, "%u,",(uint16_t)lastAmp[muxmod]); // outputs12-bit form of input voltage

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
        counterDATA += 1; //increment sample counter once finished

    int_fast8_t   result;
    uint_fast32_t cardCapacity;
    uint_fast32_t totalSectors;
    uint_fast32_t sectorSize;
    uint_fast32_t sectors;
    //int           i;
    SD_Handle     sdHandle;

        /*********Write to SD card*******/
    /*sdHandle = SD_open(Board_SD0, NULL);
    result = SD_initialize(sdHandle);
    totalSectors = SD_getNumSectors(sdHandle);
    sectorSize = SD_getSectorSize(sdHandle);
    cardCapacity = (totalSectors / BYTESPERKILOBYTE) * sectorSize;
    result = SD_write(sdHandle, uartTxBuffer, STARTINGSECTOR, sectors);
    //result = SD_read(sdHandle, cpy_buff, STARTINGSECTOR, sectors);
    SD_close(sdHandle);*/

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

void Sensors_createTask(void) {

    return;
}

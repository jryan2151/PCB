/*
 *`Copyright (c) 2015-2019, Texas Instruments Incorporated **Some libraries copywrited, not all code.**
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
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OFz USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

 _______________________________________________________________________________
 *************************** NOTES ON USING THIS CODE **************************
 *******************************************************************************
 _______________________________________________________________________________
 LAST MODIFIED: 2 August 2022 by Jared Brinkman

 DESCRIPTION OF CODE FUNCTIONALITY:
 This BLUETOOTH code is used on BACPAC PCBs in conjunction with the Spine Simulator app and BACPAC arrays in order
 to read and calculate sensor impedance on BACPAC arrays properly.

 EXAMPLE OUTPUT:
 6026,157.14,1209.18,475.99,804.80,41.14,264.74,71.10,49999.99,33474.11,3166.80,49999.99,49999.99,6816.37,49999.99,9870.85,4605.72
 (Time(milliseconds),Sensor 1 Impedance, Sensor 2 Impedance, ... Sensor 16 Impedance\n)

 The sampling duration in the CC2640R2_LAUNCHXL.c file (line 131) is a limiting
 factor for the MUXFREQ settings. The maximums are listed below:

 MUXFREQ max | adcsamplingDuration
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

 I2C TRANSMISSION PROTOCOL
 txBuffer1[0] is the high byte while txBuffer1[1] is the low byte. (same with txBuffer3)
 In order to transfer an integer of size 12 bits we need at least 2 bytes.  This is why we have
 to declare and define two bytes in the code.  See the spec sheet via box Important
 Data Sheets for a more detailed explanation of how we are using I2C protocol.

 >>8 is used to not read the lower 8 bits while simply setting txBuffer1[1] = signal.ampAC will
 read in the first 8 bits (lowest 8 bits)

 hex converter: https://www.cs.princeton.edu/courses/archive/fall07/cos109/bc.html for Slave Address
 */

/* 48 hour code Notes
You also need to set the FOURTYEIGHT boolian in a different file to true -> FILE SIMPLE_PERIPHERAL.C -> LINE 710
 */

// CODE VERSION 1.1
/* C included packages */
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

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

/* Board Header file */
#include "Board.h"
#include "DiskAccess.h"
#include "Storage.h"
#include "Serializer.h"
#include "sensors.h"
#include "ImpedanceCalc.h"

/////////////////////////// pin configuration ///////////////////////
/* Pin driver handles */
static PIN_Handle muxPinHandle1;

/* Global memory storage for a PIN_Config table */
static PIN_State muxPinState1;


//////////////// Global Variables ///////////////////////

// Unmodified - these values are not meant to be changed
uint8_t muxmod1 = 0; // allocates which array pin is being read (Values 0-15) - sets the associated mux sensor when call muxPinReset1()
uint16_t adcValue = 0; // adc read
float impedance = 0; // impedance (resistance) calculated for the current sensor
char *uartBuf; // used to store data that will then be output to the serial monitor
uint8_t stutter = 0; //checks to make sure we don't stutter more than 3 times in one cycle
const uint8_t channels = 16; //the number of channels corresponds to the number of sensors and should always be 16.
uint8_t res1 = 0; // confirms an adcRead read properly
uint8_t counterCYCLE = 0; // counts the number of DACtimerCallbacks between every output
uint8_t successImpAdd[channels] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }; // records the number of successful impedance values added to impSum for that cycle
float impSum[channels] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }; // compiles impedance values
float milliseconds = 0; // current time stamp
uint8_t sensorValues[channels] = { 125, 125, 125, 125, 125, 125, 125, 125, 125, 125, 125, 125, 125, 125, 125, 125 }; //initial tap value for each sensor (the tap value is a measure of the resistance of the potentiometer (variable resistor) in the circuit)
int8_t adjust_tap = 0; // p controller shifting tap value
long true_error = 0; // target_adc error for p controller - adcValue for current cycle
bool sumSample = false; // Tells us when to sum an aggregation of reads
int readposition = 0; // Sets read and start position
int startposition = 0; // Sets read and start position
unsigned char ucCommand[3];
const float MV_SCALE = 8.056640625; // (3300.0/4096.0) scale used to get actual milVolt reading
uint8_t AUTOMATE = 1; // AUTOCAL - increments tap during automated calibration

// Modifiable
const uint16_t MUXFREQ = 800; // Frequency (the number of channels to be read per second). Must be less than half of DAC frequency (~line 320).
const uint8_t DACTIMER_CASE_COUNT = 3; // Number of Cases in our DACTIMER Finite State Machine
const float PERIOD_OF_TIME = 1.2522821; // time it takes to complete one round through the DACtimercallbac
const uint16_t HIGHCUTSHIGH = 2770; // high tap values upper bound
const uint16_t LOWCUTSHIGH = 2720; // high tap values lower bound
const uint16_t HIGHCUTSLOW = 2500; // low tap values upper bound
const uint16_t LOWCUTSLOW = 2250; // low tap values lower bound
const uint16_t HIGHCUTSHIGHTHREE = 2700; // high tap values upper bound
const uint16_t LOWCUTSHIGHTHREE = 2200; // high tap values lower bound
const uint16_t HIGHCUTSLOWTHREE = 2700; // low tap values upper bound
const uint16_t LOWCUTSLOWTHREE = 1000; // low tap values lower bound
const uint8_t CALIBRATION_LIMIT = 8; // the lower tap values don't quite reach 3000 adc so we need lower cutoffs. This is the point where these different cutoffs apply.
const uint8_t CALIBRATION_LIMITTHREE = 4; // the lower tap values don't quite reach 3000 adc so we need lower cutoffs. This is the point where these different cutoffs apply.
const uint8_t TAP_HIGHEST_VALUE = 254; // highest tap value possible
const uint8_t TAP_LOWEST_VALUE = 1; // lowest tap value possible
const uint8_t NUM_CYCLES_PER_OUTPUT = 5; // How many cycles through DACTimerCallback before one output
const uint8_t lastAmp = 250; //Initialize all sensors to the value (in milli-amps) you want to run the signal.
const uint16_t target_adc = 2750; // target adc value for p controller
const float kp_value_high = .0065; // p controller
const float kp_value_low = .002; // p controller


// Board Type and settings
const bool print_uart = true;
const bool CALIBRATE = false; // false runs functional code.  true runs calibration code
const bool FOURTYEIGHT = false; // runs 48 hour code. Will immediately start writing data to sd card when device turned on.

/* Starting sector to write/read to on the SD card*/
#define STARTINGSECTOR 0
#define BYTESPERKILOBYTE 1024

// this table declares the specific Mux Pins which are to be used later in the code
    PIN_Config muxPinTable1[] = {
    IOID_28 | PIN_GPIO_OUTPUT_EN | PIN_GPIO_HIGH | PIN_PUSHPULL | PIN_DRVSTR_MAX, //ENABLE
        IOID_22 | PIN_GPIO_OUTPUT_EN | PIN_GPIO_HIGH | PIN_PUSHPULL| PIN_DRVSTR_MAX, //A3
        IOID_23 | PIN_GPIO_OUTPUT_EN | PIN_GPIO_HIGH | PIN_PUSHPULL| PIN_DRVSTR_MAX, //A2
        IOID_12 | PIN_GPIO_OUTPUT_EN | PIN_GPIO_HIGH | PIN_PUSHPULL| PIN_DRVSTR_MAX, //A1
        IOID_15 | PIN_GPIO_OUTPUT_EN | PIN_GPIO_HIGH | PIN_PUSHPULL| PIN_DRVSTR_MAX, //A0
    PIN_TERMINATE };

///////////////////////////////////// I2C preamble //////////////////////////
uint8_t rxBuffer1[0];          // Receive buffer for the DAC that is on.
uint8_t txBuffer1[2];          // Transmit buffer for the DAC that is on.
uint8_t rxBuffer2[0];          // Receive buffer for the DAC that is off. When we remove it from the board delete these 2 lines.
uint8_t txBuffer2[2];          // Transmit buffer for the DAC that is off.
uint8_t rxBuffer3[1];          // Receive buffer for the potentiometer
uint8_t txBuffer3[2];          // Transmit buffer for the potentiometer
bool transferDone = false;     // signify the I2C has finished for this cycle
bool openDone = true; // signify the I2C has opened successfully in order to transmit data
uint8_t counterDAC = 0; // declaring the counterDac used in DACtimerCallback function

//Used to store the signal2 current amplitude (max is 4095)
struct {
    uint16_t ampAC :12; // signal to the system that will go high.
    uint16_t ampDC :12; // reference signal. Remains 0 so we have something to measure against.
} Signal; //&&& signal-> Signal

/*///////////////////////////////////// Function Declarations /////////////////////////////////////
 The majority of these functions act as callback functions and will interrupt any running code every few milliseconds or so in order
 to perform their functions.  The majority of the functionality on the PCB happens in DACtimerCallback */

static void i2cWriteCallback(I2C_Handle handle, I2C_Transaction *transac, bool result);
void DACtimerCallback(GPTimerCC26XX_Handle handle, GPTimerCC26XX_IntMask interruptMask);
void muxPinReset1(uint8_t muxmod1_GS, bool autocal);
void muxPower1(uint8_t power);

/* Driver handles */
GPTimerCC26XX_Handle hDACTimer;
I2C_Handle I2Chandle;
I2C_Params I2Cparams;
I2C_Transaction i2cTrans1;
I2C_Transaction i2cTrans2;
I2C_Transaction i2cTrans3;

///////////////////////////////////// ADC/Display Preamble /////////////////////////////////

/* ADC Global Variables */
ADC_Handle adc; // used in turning on adc
ADC_Params params; // used in turning on adc
UART_Handle uart;

void uartCallback(UART_Handle handle, void *buf, size_t count){
    return;
}

//                              ======== MAIN THREAD ========
// this function is run immediately when the PCB is programmed. Any time you reset the PCB it will run again.
void Sensors_init(){
    uartBuf = (char*) malloc(256 * sizeof(char));

    // Initialize Variables
    Signal.ampAC = lastAmp; //Set the Signal to what it is initialized to in the array declared on line 138 (lastAmp[])

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

    // Initialize master I2C transaction structure for the DAC that is ON
    i2cTrans1.writeBuf = txBuffer1; //AC (square) signal2
    i2cTrans1.writeCount = 2;
    i2cTrans1.readBuf = NULL;
    i2cTrans1.readCount = 0;
    i2cTrans1.slaveAddress = 0x4C; // See data sheet via Box-> Important Data Sheets for appropriate address for the DAC.

    // Initialize master I2C transaction structure for the potentiometer
    i2cTrans3.writeBuf = txBuffer3; //DC Signal
    i2cTrans3.writeCount = 2;
    i2cTrans3.readBuf = NULL;
    i2cTrans3.readCount = 0;
    i2cTrans3.slaveAddress = 0x2C; // See data via Box-> Important Data Sheets for appropriate address for the Potentiometer.

    /////////////////////////////////////////////////// UART //////////////////////////////////////////////////
    UART_Params uartParams;
    UART_init();
    UART_Params_init(&uartParams);
    uartParams.writeDataMode = UART_DATA_BINARY;
    uartParams.writeMode = UART_MODE_CALLBACK;
    uartParams.writeCallback = uartCallback;
    uartParams.baudRate = 460800; // Baud Rate.
    uart = UART_open(Board_UART0, &uartParams);

    ////////////////////////////////////////////// GPTimer for DAC //////////////////////////////////////////
    GPTimerCC26XX_Params paramsDAC;
    GPTimerCC26XX_Params_init(&paramsDAC);
    paramsDAC.width = GPT_CONFIG_32BIT;
    paramsDAC.mode = GPT_MODE_PERIODIC_UP;
    paramsDAC.debugStallMode = GPTimerCC26XX_DEBUG_STALL_OFF;
    hDACTimer = GPTimerCC26XX_open(CC2640R2_LAUNCHXL_GPTIMER0A, &paramsDAC); //Need timer 0A for ADCbuf
    if (hDACTimer == NULL){
        System_sprintf(uartBuf, "Error starting DAC timer");
        print(uartBuf);
        while (1);
    }
    GPTimerCC26XX_Value loadValDAC = 48000000 / (MUXFREQ * DACTIMER_CASE_COUNT);
    loadValDAC = loadValDAC - 1;
    GPTimerCC26XX_setLoadValue(hDACTimer, loadValDAC);
    GPTimerCC26XX_registerInterrupt(hDACTimer, DACtimerCallback, GPT_INT_TIMEOUT);
    // Open I2C
    I2Chandle = I2C_open(Board_I2C0, &I2Cparams);
    if (I2Chandle == NULL){
        // Error opening I2C
        System_sprintf(uartBuf, "Error Opening I2C");
        print(uartBuf);
        while (1);
    }

////////////////////////////////////////////////////////////////// MUX 1 //////////////////////////////////////////////////////////
    muxPinHandle1 = PIN_open(&muxPinState1, muxPinTable1);
    if (!muxPinHandle1){
        /* Error initializing mux output pins */
        System_sprintf(uartBuf, "Error Initializing Mux Output Pins");
        print(uartBuf);
        while (1);
    }


//////////////////////////////////////////////////////////////////// ADC //////////////////////////////////////////////////////////
    ADC_Params_init(&params);
    adc = ADC_open(1, &params);
    if (adc == NULL){
        System_sprintf(uartBuf, "Error Initializing ADC channel"); //- isProtected = %s,\n custom: %p\n", params.isProtected ? "true" : "false", params.custom); // Error initializing ADC channel 0
        print(uartBuf);
        while (1);
    }

    Signal.ampAC = lastAmp; // High signal.
    Signal.ampDC = 0; // reference signal.  Needs to be low so we can measure against it.
    txBuffer1[0] = Signal.ampAC >> 8; //high byte
    txBuffer1[1] = Signal.ampAC; //low byte
    txBuffer2[0] = Signal.ampDC >> 8; //high byte.
    txBuffer2[1] = Signal.ampDC; //low byte.
    I2C_transfer(I2Chandle, &i2cTrans1); // communication for the DAC that is currently ON.
    I2C_transfer(I2Chandle, &i2cTrans2); // communication for the DAC that is currently OFF. Delete when confirmed we don't need it.

    // set the mux configuration to array pin 0 which is really sensor 10 on the PCB
    muxmod1 = 0;
    muxPinReset1(muxmod1, CALIBRATE);
    if (CALIBRATE) Sensors_start_timers(); // AUTOCAL - starts spitting out data immediately.
    else {
        DA_get_status(da_load(), "Loading Disk"); // BLUETOOTH
        startposition = da_get_read_pos();
    }
    if (FOURTYEIGHT) Sensors_start_timers();
    if (print_uart){
        Sensors_start_timers();
    }
}


////////////////////////////////////////////// Functions used Later /////////////////////////////////////////

void adc_read() {
    res1 = ADC_convert(adc, &adcValue); // read the current adc Value
    switch (res1){
        case ADC_STATUS_SUCCESS:
            break;
        default:
            res1 = ADC_convert(adc, &adcValue);
    }
}

void load_serializer(uint16_t read_value) {
    if (serializer_isFull()){
        if (FOURTYEIGHT) serializer_setTimestamp((uint16_t) (milliseconds/1000)); // checking if 16 impedance values have been added to the array
        else serializer_setTimestamp((uint16_t) milliseconds); // checking if 16 impedance values have been added to the array
    }
    serializer_addImpedance(read_value); //adding current value for  read
    if (serializer_isFull() && Semaphore_pend(storage_buffer_mutex, 0)) {
        storage_buffer_length += serializer_serialize(storage_buffer);
        if (print_uart){
            serializer_serializeReadable(uartBuf); // convert serializer array so it is readable by UART (comment out if UART is unnecessary)
            print(uartBuf); // write to the UART Buf (comment out if UART is unnecessary)
        }
        Semaphore_post(storage_buffer_mailbox); // writing to the sd card
    }
}

// Function to output during standard testing
void Sensors_serializer_output() {

    if (sumSample) {
        if (successImpAdd[muxmod1])impedance = impSum[muxmod1] / successImpAdd[muxmod1];
        else  impedance = 49999.99;
        sumSample = false;
        impSum[muxmod1] = 0;
        successImpAdd[muxmod1] = 0;

        /* IMPORTANT: WRITE IMPEDANCE VALUE TO SD CARD AND/OR UART BUF */
        load_serializer(impedance);
        if (muxmod1 == (channels - 1)){
            counterCYCLE = 0;
        }
    }
}

void set_impedance() {
    if ((adcValue < 2950) || (stutter > 3)){
        if (adcValue < 400) impedance = 49999.99; // if our adcValue is too low. We don't want to interpret it as valid data.
        else {
            impedance = impedanceCalc(sensorValues[muxmod1], adcValue);
        }
        if (impedance > 49999.99) {
            impedance = 49999.99; // we only need impedance values within a certain range. This is our cap.
        }
        if (res1 == ADC_STATUS_SUCCESS){
            impSum[muxmod1] += impedance; // if ,adc read correctly we want to add the calculated impedance to a sum to be averaged later
            successImpAdd[muxmod1] += 1; // increment number of successful impedance values added this round
        }
    }
}

void adjust_pot_V_One_Three() { // adjust potentiometer value
    if (sensorValues[muxmod1] > CALIBRATION_LIMITTHREE) {
       if (adcValue < LOWCUTSHIGHTHREE) sensorValues[muxmod1]++; // move up a tap
       else if (adcValue > HIGHCUTSHIGHTHREE) sensorValues[muxmod1]--; // move down a tap
   }
   else {
       if (adcValue < LOWCUTSLOWTHREE) sensorValues[muxmod1]++; // move up a tap
       else if (adcValue > HIGHCUTSLOWTHREE) sensorValues[muxmod1]--; // move down a tap
   }
   if (sensorValues[muxmod1] > TAP_HIGHEST_VALUE) {
       sensorValues[muxmod1] = TAP_HIGHEST_VALUE; // if we are out of our tap value range we want to bring it back.
   }
   else if (sensorValues[muxmod1] < TAP_LOWEST_VALUE) {
       sensorValues[muxmod1] = TAP_LOWEST_VALUE; // if we are out of our tap value range we want to bring it back.
   }
}

void adjust_pot_V_One_Two() { // proportional integral controller
    if (adcValue < LOWCUTSHIGH){
        true_error = LOWCUTSHIGH - adcValue;
        adjust_tap = round(true_error * pow(sensorValues[muxmod1], 0.7)* kp_value_low); // + kd_value * (true_error - last_error[muxmod1]) + ki_value * (i_error[muxmod1] + true_error);
        if (adjust_tap > 20) adjust_tap = 20; //Arbitrary bounds on the adjustment - we need to make this a PARAMETER (const int) later
        if (adjust_tap < 0) adjust_tap = 0; //Arbitrary bounds on the adjustment - we need to make this a PARAMETER (const int) later
    }
    else if (adcValue > HIGHCUTSHIGH){
        true_error = HIGHCUTSHIGH - adcValue;
        adjust_tap = round( true_error * pow(sensorValues[muxmod1], 0.7)* kp_value_high); // + kd_value * (true_error - last_error[muxmod1]) + ki_value * (i_error[muxmod1] + true_error);
        if (adjust_tap > 0) adjust_tap = 0; //Arbitrary bounds on the adjustment - we need to make this a PARAMETER (const int) later
        if (adjust_tap < -20) adjust_tap = -20; //Arbitrary bounds on the adjustment - we need to make this a PARAMETER (const int) later
    }
    if (sensorValues[muxmod1] < CALIBRATION_LIMIT && adjust_tap < 3){
        if (adcValue < LOWCUTSLOW) sensorValues[muxmod1]++; // move up a tap
        else if (adcValue > HIGHCUTSLOW) sensorValues[muxmod1]--; // move down a tap
    }
    else if (adcValue < LOWCUTSHIGH || adcValue > HIGHCUTSHIGH) sensorValues[muxmod1] = sensorValues[muxmod1] + adjust_tap;
    if (sensorValues[muxmod1] > TAP_HIGHEST_VALUE) sensorValues[muxmod1] = TAP_HIGHEST_VALUE; // if we are out of our tap value range we want to bring it back.
        //IF we have an Integral Overrun - reset it here. This is where we'll find it most likely to be pinned (these two walls)
    else if (sensorValues[muxmod1] < TAP_LOWEST_VALUE) sensorValues[muxmod1] = TAP_LOWEST_VALUE; // if we are out of our tap value range we want to bring it back.
}

void check_cycle_count() {
    if (counterCYCLE < NUM_CYCLES_PER_OUTPUT && muxmod1 == 0) {
       counterCYCLE++;
   }
   if (counterCYCLE >= NUM_CYCLES_PER_OUTPUT) {
       sumSample = true;
   }
}

void calibration_output() {
    if (muxmod1 == 0) {
        System_sprintf(uartBuf, "%u,%u,%u,", (uint32_t) milliseconds, AUTOMATE, adcValue); // output time stamp, tap, adc value of current sensor
        print(uartBuf);
    }
    else if (muxmod1 < 15) {
        System_sprintf(uartBuf, "%u,", adcValue); // output adc Value of current sensor
        print(uartBuf);
    }
    else {
        System_sprintf(uartBuf, "%u\n\r", adcValue); // output adc value of current sensor and end line
        print(uartBuf);
        AUTOMATE++;
        if (AUTOMATE > 254) AUTOMATE = 2; // calibrate from tap 2 to 253
    }
    muxmod1++;
    if (muxmod1 == channels){
        muxmod1 = 0; // reset counter back to zero if it equals the number of channels
    }
}

/////////////////////////////////////////// I2C Functions /////////////////////////////////////////////////
static void i2cWriteCallback(I2C_Handle handle, I2C_Transaction *transac, bool result){
    // Set length bytes
    if (result) transferDone = true;
    else transferDone = false; // Transaction failed, act accordingly...
};

////////////// FINITE STATE MACHINE - this is where the bulk of the functionality of this file takes place /////////

void DACtimerCallback(GPTimerCC26XX_Handle handle,GPTimerCC26XX_IntMask interruptMask) {
    if (counterDAC == 0){
        ////////// ADC Read  ///////////
        adc_read();
        storage_buffer_length = 0; // stores length of the data in the buffer. Useful for writing purposes. Don't know if necessary

        muxPower1(0); // turn off MUX to conserve POWER

        //AUTOCAL CODE
        if (CALIBRATE){
            calibration_output();
        }

        ////////// CALCULATE IMPEDANCE //////////
        set_impedance();

        counterDAC ++; // increments DACtimerCallback counter to 2
    }
    else if (counterDAC == 1) {

        if (CALIBRATE){}
        else {
            ////////// CHANGE TAP VALUE FOR NEXT READ IF NECESSARY //////////
            adjust_pot_V_One_Two();
            check_cycle_count();

            Sensors_serializer_output();
            GPIO_write(Board_GPIO_LED1, Board_GPIO_LED_OFF);

            muxmod1++;
            if (muxmod1 == channels) {
                muxmod1 = 0; // reset counter back to zero if it equals the number of channels
            }
        }

        counterDAC ++;
    }
    else if (counterDAC == 2){

        /////////// RESET MUX FOR NEXT  READ ///////////
        muxPinReset1(muxmod1, CALIBRATE); // convert the mux to new setting to account for next sensor channel
        txBuffer3[0] = 0; // 8 bit device so we don't need the high byte - transfers info to the hardware
        // AUTOCAL CODE. Switches muxmod1 with AUTOMATE.
        if (CALIBRATE) txBuffer3[1] = AUTOMATE;
        else txBuffer3[1] = sensorValues[muxmod1];
        I2C_transfer(I2Chandle, &i2cTrans3); // writes to the potentiometer the values from above over I2C communication.
        muxPower1(1); // turn on mux for next read

        /// Updates milliseconds variable (time stamp)
        milliseconds = milliseconds + PERIOD_OF_TIME; // End of a cycle. Update current time stamp.
        counterDAC = 0; // Reset DACtimerCallback to case 0
    }
}

// Function to configure our mux enable pin
void muxPower1(uint8_t power){
        if (power == 1) PIN_setOutputValue(muxPinHandle1, IOID_28, 0);
        if (power == 0) PIN_setOutputValue(muxPinHandle1, IOID_28, 1);
}

/* Every time we start recording data we need our time stamp and sensor channel to reset to 0 */
void Sensors_start_timers() {
    milliseconds = 0;
    muxmod1 = 0;
    GPTimerCC26XX_start(hDACTimer);
}

/* Every time we stop recording data we clear our serializer because our sensors channel will reset next time we start writing again */
void Sensors_stop_timers() {
    serializer_clear();
    milliseconds = 0;
    GPTimerCC26XX_stop(hDACTimer);
}

/*
 * DA_get_status returns an explanation of what is happening with the SD Card.
 * Success means everything is working. Failed to initialize SD card implies there is no SD card present.
 */
void DA_get_status(int status_code, char *message) {
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

// Write to the UART/terminal with print()
void print(char *str) {
    UART_write(uart, str, strlen(str));
}

// calibration code and functional code have different pin configurations - configuring the sensors to match the array pins
void muxPinReset1(uint8_t muxmod1, bool autoCal) {
    if (autoCal) {
        switch (muxmod1) {
        //  AUTOCAL CODE
            case 14: // AUTOCAL
                PIN_setOutputValue(muxPinHandle1, IOID_22, 0); //S3
                PIN_setOutputValue(muxPinHandle1, IOID_23, 0); //S2
                PIN_setOutputValue(muxPinHandle1, IOID_12, 0); //S1
                PIN_setOutputValue(muxPinHandle1, IOID_15, 0); //S0
                break;
            case 13: // sensor 1 array pin 13
                PIN_setOutputValue(muxPinHandle1, IOID_22, 0); //S3
                PIN_setOutputValue(muxPinHandle1, IOID_23, 0); //S2
                PIN_setOutputValue(muxPinHandle1, IOID_12, 0); //S1
                PIN_setOutputValue(muxPinHandle1, IOID_15, 1); //S0
                break;
            case 15: // AUTOCAL
                PIN_setOutputValue(muxPinHandle1, IOID_22, 0); //S3
                PIN_setOutputValue(muxPinHandle1, IOID_23, 0); //S2
                PIN_setOutputValue(muxPinHandle1, IOID_12, 1); //S1
                PIN_setOutputValue(muxPinHandle1, IOID_15, 0); //S0
                break;
            case 12: // ATUOCAL
                PIN_setOutputValue(muxPinHandle1, IOID_22, 0); //S3
                PIN_setOutputValue(muxPinHandle1, IOID_23, 0); //S2
                PIN_setOutputValue(muxPinHandle1, IOID_12, 1); //S1
                PIN_setOutputValue(muxPinHandle1, IOID_15, 1); //S0
                break;
            case 11: // AUTOCAL
                PIN_setOutputValue(muxPinHandle1, IOID_22, 0); //S3
                PIN_setOutputValue(muxPinHandle1, IOID_23, 1); //S2
                PIN_setOutputValue(muxPinHandle1, IOID_12, 0); //S1
                PIN_setOutputValue(muxPinHandle1, IOID_15, 0); //S0
                break;
            case 10: // AUTOCAL
                PIN_setOutputValue(muxPinHandle1, IOID_22, 0); //S3
                PIN_setOutputValue(muxPinHandle1, IOID_23, 1); //S2
                PIN_setOutputValue(muxPinHandle1, IOID_12, 0); //S1
                PIN_setOutputValue(muxPinHandle1, IOID_15, 1); //S0
                break;
            case 9: // AUTOCAL
                PIN_setOutputValue(muxPinHandle1, IOID_22, 0); //S3
                PIN_setOutputValue(muxPinHandle1, IOID_23, 1); //S2
                PIN_setOutputValue(muxPinHandle1, IOID_12, 1); //S1
                PIN_setOutputValue(muxPinHandle1, IOID_15, 0); //S0
                break;
            case 0: // AUTOCAL
                PIN_setOutputValue(muxPinHandle1, IOID_22, 0); //S3
                PIN_setOutputValue(muxPinHandle1, IOID_23, 1); //S2
                PIN_setOutputValue(muxPinHandle1, IOID_12, 1); //S1
                PIN_setOutputValue(muxPinHandle1, IOID_15, 1); //S0
                break;
            case 1: // AUTOCAL
                PIN_setOutputValue(muxPinHandle1, IOID_22, 1); //S3
                PIN_setOutputValue(muxPinHandle1, IOID_23, 0); //S2
                PIN_setOutputValue(muxPinHandle1, IOID_12, 0); //S1
                PIN_setOutputValue(muxPinHandle1, IOID_15, 0); //S0
                break;
            case 2: // AUTOCAL
                PIN_setOutputValue(muxPinHandle1, IOID_22, 1); //S3
                PIN_setOutputValue(muxPinHandle1, IOID_23, 0); //S2
                PIN_setOutputValue(muxPinHandle1, IOID_12, 0); //S1
                PIN_setOutputValue(muxPinHandle1, IOID_15, 1); //S0
                break;
            case 3: // AUTOCAL
                PIN_setOutputValue(muxPinHandle1, IOID_22, 1); //S3
                PIN_setOutputValue(muxPinHandle1, IOID_23, 0); //S2
                PIN_setOutputValue(muxPinHandle1, IOID_12, 1); //S1
                PIN_setOutputValue(muxPinHandle1, IOID_15, 0); //S0
                break;
            case 4: // AUTOCAL
                PIN_setOutputValue(muxPinHandle1, IOID_22, 1); //S3
                PIN_setOutputValue(muxPinHandle1, IOID_23, 0); //S2
                PIN_setOutputValue(muxPinHandle1, IOID_12, 1); //S1
                PIN_setOutputValue(muxPinHandle1, IOID_15, 1); //S0
                break;
            case 5: // AUTOCAL
                PIN_setOutputValue(muxPinHandle1, IOID_22, 1); //S3
                PIN_setOutputValue(muxPinHandle1, IOID_23, 1); //S2
                PIN_setOutputValue(muxPinHandle1, IOID_12, 0); //S1
                PIN_setOutputValue(muxPinHandle1, IOID_15, 0); //S0
                break;
            case 6: // AUTOCAL
                PIN_setOutputValue(muxPinHandle1, IOID_22, 1); //S3
                PIN_setOutputValue(muxPinHandle1, IOID_23, 1); //S2
                PIN_setOutputValue(muxPinHandle1, IOID_12, 0); //S1
                PIN_setOutputValue(muxPinHandle1, IOID_15, 1); //S0
                break;
            case 7: // AUTOCAL
                PIN_setOutputValue(muxPinHandle1, IOID_22, 1); //S3
                PIN_setOutputValue(muxPinHandle1, IOID_23, 1); //S2
                PIN_setOutputValue(muxPinHandle1, IOID_12, 1); //S1
                PIN_setOutputValue(muxPinHandle1, IOID_15, 0); //S0
                break;
            case 8: // AUTOCAL
                PIN_setOutputValue(muxPinHandle1, IOID_22, 1); //S3
                PIN_setOutputValue(muxPinHandle1, IOID_23, 1); //S2
                PIN_setOutputValue(muxPinHandle1, IOID_12, 1); //S1
                PIN_setOutputValue(muxPinHandle1, IOID_15, 1); //S0
                break;
        }
    }
    else {
        switch (muxmod1) {
            case 10: //sensor 0 array pin 10
                PIN_setOutputValue(muxPinHandle1, IOID_22, 0); //S3
                PIN_setOutputValue(muxPinHandle1, IOID_23, 0); //S2
                PIN_setOutputValue(muxPinHandle1, IOID_12, 0); //S1
                PIN_setOutputValue(muxPinHandle1, IOID_15, 0); //S0
                break;
            case 13: // sensor 1 array pin 13
                PIN_setOutputValue(muxPinHandle1, IOID_22, 0); //S3
                PIN_setOutputValue(muxPinHandle1, IOID_23, 0); //S2
                PIN_setOutputValue(muxPinHandle1, IOID_12, 0); //S1
                PIN_setOutputValue(muxPinHandle1, IOID_15, 1); //S0
                break;
            case 11: // sensor 2 array pin 11
                PIN_setOutputValue(muxPinHandle1, IOID_22, 0); //S3
                PIN_setOutputValue(muxPinHandle1, IOID_23, 0); //S2
                PIN_setOutputValue(muxPinHandle1, IOID_12, 1); //S1
                PIN_setOutputValue(muxPinHandle1, IOID_15, 0); //S0
                break;
            case 8: // sensor 3 array pin 8
                PIN_setOutputValue(muxPinHandle1, IOID_22, 0); //S3
                PIN_setOutputValue(muxPinHandle1, IOID_23, 0); //S2
                PIN_setOutputValue(muxPinHandle1, IOID_12, 1); //S1
                PIN_setOutputValue(muxPinHandle1, IOID_15, 1); //S0
                break;
            case 14: //sensor 4 array pin 14
                PIN_setOutputValue(muxPinHandle1, IOID_22, 0); //S3
                PIN_setOutputValue(muxPinHandle1, IOID_23, 1); //S2
                PIN_setOutputValue(muxPinHandle1, IOID_12, 0); //S1
                PIN_setOutputValue(muxPinHandle1, IOID_15, 0); //S0
                break;
            case 12: //sensor 5 array pin 12
                PIN_setOutputValue(muxPinHandle1, IOID_22, 0); //S3
                PIN_setOutputValue(muxPinHandle1, IOID_23, 1); //S2
                PIN_setOutputValue(muxPinHandle1, IOID_12, 0); //S1
                PIN_setOutputValue(muxPinHandle1, IOID_15, 1); //S0
                break;
            case 15: //sensor 6 array pin 15
                PIN_setOutputValue(muxPinHandle1, IOID_22, 0); //S3
                PIN_setOutputValue(muxPinHandle1, IOID_23, 1); //S2
                PIN_setOutputValue(muxPinHandle1, IOID_12, 1); //S1
                PIN_setOutputValue(muxPinHandle1, IOID_15, 0); //S0
                break;
            case 7: // sensor 7 array pin 7
                PIN_setOutputValue(muxPinHandle1, IOID_22, 0); //S3
                PIN_setOutputValue(muxPinHandle1, IOID_23, 1); //S2
                PIN_setOutputValue(muxPinHandle1, IOID_12, 1); //S1
                PIN_setOutputValue(muxPinHandle1, IOID_15, 1); //S0
                break;
            case 4: // sensor 8 array pin 4
                PIN_setOutputValue(muxPinHandle1, IOID_22, 1); //S3
                PIN_setOutputValue(muxPinHandle1, IOID_23, 0); //S2
                PIN_setOutputValue(muxPinHandle1, IOID_12, 0); //S1
                PIN_setOutputValue(muxPinHandle1, IOID_15, 0); //S0
                break;
            case 6: //sensor 9 array pin 6
                PIN_setOutputValue(muxPinHandle1, IOID_22, 1); //S3
                PIN_setOutputValue(muxPinHandle1, IOID_23, 0); //S2
                PIN_setOutputValue(muxPinHandle1, IOID_12, 0); //S1
                PIN_setOutputValue(muxPinHandle1, IOID_15, 1); //S0
                break;
            case 0: // sensor 10 array pin 0
                PIN_setOutputValue(muxPinHandle1, IOID_22, 1); //S3
                PIN_setOutputValue(muxPinHandle1, IOID_23, 0); //S2
                PIN_setOutputValue(muxPinHandle1, IOID_12, 1); //S1
                PIN_setOutputValue(muxPinHandle1, IOID_15, 0); //S0
                break;
            case 5: // sensor 11 array pin 5
                PIN_setOutputValue(muxPinHandle1, IOID_22, 1); //S3
                PIN_setOutputValue(muxPinHandle1, IOID_23, 0); //S2
                PIN_setOutputValue(muxPinHandle1, IOID_12, 1); //S1
                PIN_setOutputValue(muxPinHandle1, IOID_15, 1); //S0
                break;
            case 2: // sensor 12 array pin 2
                PIN_setOutputValue(muxPinHandle1, IOID_22, 1); //S3
                PIN_setOutputValue(muxPinHandle1, IOID_23, 1); //S2
                PIN_setOutputValue(muxPinHandle1, IOID_12, 0); //S1
                PIN_setOutputValue(muxPinHandle1, IOID_15, 0); //S0
                break;
            case 3: // sensor 13 array pin 3
                PIN_setOutputValue(muxPinHandle1, IOID_22, 1); //S3
                PIN_setOutputValue(muxPinHandle1, IOID_23, 1); //S2
                PIN_setOutputValue(muxPinHandle1, IOID_12, 0); //S1
                PIN_setOutputValue(muxPinHandle1, IOID_15, 1); //S0
                break;
            case 1: // sensor 14 array pin 1
                PIN_setOutputValue(muxPinHandle1, IOID_22, 1); //S3
                PIN_setOutputValue(muxPinHandle1, IOID_23, 1); //S2
                PIN_setOutputValue(muxPinHandle1, IOID_12, 1); //S1
                PIN_setOutputValue(muxPinHandle1, IOID_15, 0); //S0
                break;
            case 9: // sensor 15 array pin 9
                PIN_setOutputValue(muxPinHandle1, IOID_22, 1); //S3
                PIN_setOutputValue(muxPinHandle1, IOID_23, 1); //S2
                PIN_setOutputValue(muxPinHandle1, IOID_12, 1); //S1
                PIN_setOutputValue(muxPinHandle1, IOID_15, 1); //S0
                break;
        }
    }
}

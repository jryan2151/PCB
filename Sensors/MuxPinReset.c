/*
 * MuxPinReset.c
 *
 *  Created on: Aug 4, 2022
 *      Author: Jared Brinkman
 */

//#include "MuxPinReset.h"

//PIN_Config muxPinTable[] = {
//    IOID_28 | PIN_GPIO_OUTPUT_EN | PIN_GPIO_HIGH | PIN_PUSHPULL | PIN_DRVSTR_MAX, //ENABLE
//    IOID_22 | PIN_GPIO_OUTPUT_EN | PIN_GPIO_HIGH | PIN_PUSHPULL | PIN_DRVSTR_MAX, //A3
//    IOID_23 | PIN_GPIO_OUTPUT_EN | PIN_GPIO_HIGH | PIN_PUSHPULL | PIN_DRVSTR_MAX, //A2
//    IOID_12 | PIN_GPIO_OUTPUT_EN | PIN_GPIO_HIGH | PIN_PUSHPULL | PIN_DRVSTR_MAX, //A1
//    IOID_15 | PIN_GPIO_OUTPUT_EN | PIN_GPIO_HIGH | PIN_PUSHPULL | PIN_DRVSTR_MAX, //A0
//    PIN_TERMINATE
//};

//void muxInit() {
//    /////////////////////////// pin configuration ///////////////////////
//    /* Pin driver handles */
//    static PIN_Handle muxPinHandle;
//
//    /* Global memory storage for a PIN_Config table */
//    static PIN_State muxPinState;
//
//    PIN_Config muxPinTable[] = {
//                                IOID_28 | PIN_GPIO_OUTPUT_EN | PIN_GPIO_HIGH | PIN_PUSHPULL | PIN_DRVSTR_MAX, //ENABLE
//                                IOID_22 | PIN_GPIO_OUTPUT_EN | PIN_GPIO_HIGH | PIN_PUSHPULL | PIN_DRVSTR_MAX, //A3
//                                IOID_23 | PIN_GPIO_OUTPUT_EN | PIN_GPIO_HIGH | PIN_PUSHPULL | PIN_DRVSTR_MAX, //A2
//                                IOID_12 | PIN_GPIO_OUTPUT_EN | PIN_GPIO_HIGH | PIN_PUSHPULL | PIN_DRVSTR_MAX, //A1
//                                IOID_15 | PIN_GPIO_OUTPUT_EN | PIN_GPIO_HIGH | PIN_PUSHPULL | PIN_DRVSTR_MAX, //A0
//                                PIN_TERMINATE
//    };
//
//    muxPinHandle = PIN_open(&muxPinState, muxPinTable);
//    if(!muxPinHandle) {
//        /* Error initializing mux output pins */
//        System_sprintf(uartBuf, "Error Initializing Mux Output Pins");
//        print(uartBuf);
//        // Jared -Make this more noticable by displaying uart. f("string") makes it flash memory. Look into this
//        while(1);
//    }
//}

//void muxPinReset(uint8_t muxmod, bool autoCal, PIN_Handle muxPinHandle, PIN_Config muxPinTable){
//    if (autoCal){
//        switch(muxmod) {
//            //  AUTOCAL CODE
//              case 14: // AUTOCAL
//                    PIN_setOutputValue(muxPinHandle, IOID_22, 0); //S3
//                    PIN_setOutputValue(muxPinHandle, IOID_23, 0); //S2
//                    PIN_setOutputValue(muxPinHandle, IOID_12, 0); //S1
//                    PIN_setOutputValue(muxPinHandle, IOID_15, 0); //S0
//                    break;
//                case 13: // sensor 1 array pin 13
//                    PIN_setOutputValue(muxPinHandle, IOID_22, 0); //S3
//                    PIN_setOutputValue(muxPinHandle, IOID_23, 0); //S2
//                    PIN_setOutputValue(muxPinHandle, IOID_12, 0); //S1
//                    PIN_setOutputValue(muxPinHandle, IOID_15, 1); //S0
//                    break;
//                case 15: // AUTOCAL
//                    PIN_setOutputValue(muxPinHandle, IOID_22, 0); //S3
//                    PIN_setOutputValue(muxPinHandle, IOID_23, 0); //S2
//                    PIN_setOutputValue(muxPinHandle, IOID_12, 1); //S1
//                    PIN_setOutputValue(muxPinHandle, IOID_15, 0); //S0
//                    break;
//                 case 12: // ATUOCAL
//                    PIN_setOutputValue(muxPinHandle, IOID_22, 0); //S3
//                    PIN_setOutputValue(muxPinHandle, IOID_23, 0); //S2
//                    PIN_setOutputValue(muxPinHandle, IOID_12, 1); //S1
//                    PIN_setOutputValue(muxPinHandle, IOID_15, 1); //S0
//                    break;
//                case 11: // AUTOCAL
//                    PIN_setOutputValue(muxPinHandle, IOID_22, 0); //S3
//                    PIN_setOutputValue(muxPinHandle, IOID_23, 1); //S2
//                    PIN_setOutputValue(muxPinHandle, IOID_12, 0); //S1
//                    PIN_setOutputValue(muxPinHandle, IOID_15, 0); //S0
//                    break;
//                case 10: // AUTOCAL
//                    PIN_setOutputValue(muxPinHandle, IOID_22, 0); //S3
//                    PIN_setOutputValue(muxPinHandle, IOID_23, 1); //S2
//                    PIN_setOutputValue(muxPinHandle, IOID_12, 0); //S1
//                    PIN_setOutputValue(muxPinHandle, IOID_15, 1); //S0
//                    break;
//                case 9: // AUTOCAL
//                    PIN_setOutputValue(muxPinHandle, IOID_22, 0); //S3
//                    PIN_setOutputValue(muxPinHandle, IOID_23, 1); //S2
//                    PIN_setOutputValue(muxPinHandle, IOID_12, 1); //S1
//                    PIN_setOutputValue(muxPinHandle, IOID_15, 0); //S0
//                    break;
//                case 0: // AUTOCAL
//                    PIN_setOutputValue(muxPinHandle, IOID_22, 0); //S3
//                    PIN_setOutputValue(muxPinHandle, IOID_23, 1); //S2
//                    PIN_setOutputValue(muxPinHandle, IOID_12, 1); //S1
//                    PIN_setOutputValue(muxPinHandle, IOID_15, 1); //S0
//                    break;
//                case 1: // AUTOCAL
//                    PIN_setOutputValue(muxPinHandle, IOID_22, 1); //S3
//                    PIN_setOutputValue(muxPinHandle, IOID_23, 0); //S2
//                    PIN_setOutputValue(muxPinHandle, IOID_12, 0); //S1
//                    PIN_setOutputValue(muxPinHandle, IOID_15, 0); //S0
//                    break;
//                case 2: // AUTOCAL
//                    PIN_setOutputValue(muxPinHandle, IOID_22, 1); //S3
//                    PIN_setOutputValue(muxPinHandle, IOID_23, 0); //S2
//                    PIN_setOutputValue(muxPinHandle, IOID_12, 0); //S1
//                    PIN_setOutputValue(muxPinHandle, IOID_15, 1); //S0
//                    break;
//                case 3: // AUTOCAL
//                    PIN_setOutputValue(muxPinHandle, IOID_22, 1); //S3
//                    PIN_setOutputValue(muxPinHandle, IOID_23, 0); //S2
//                    PIN_setOutputValue(muxPinHandle, IOID_12, 1); //S1
//                    PIN_setOutputValue(muxPinHandle, IOID_15, 0); //S0
//                    break;
//                case 4: // AUTOCAL
//                    PIN_setOutputValue(muxPinHandle, IOID_22, 1); //S3
//                    PIN_setOutputValue(muxPinHandle, IOID_23, 0); //S2
//                    PIN_setOutputValue(muxPinHandle, IOID_12, 1); //S1
//                    PIN_setOutputValue(muxPinHandle, IOID_15, 1); //S0
//                    break;
//                case 5: // AUTOCAL
//                    PIN_setOutputValue(muxPinHandle, IOID_22, 1); //S3
//                    PIN_setOutputValue(muxPinHandle, IOID_23, 1); //S2
//                    PIN_setOutputValue(muxPinHandle, IOID_12, 0); //S1
//                    PIN_setOutputValue(muxPinHandle, IOID_15, 0); //S0
//                    break;
//                case 6: // AUTOCAL
//                    PIN_setOutputValue(muxPinHandle, IOID_22, 1); //S3
//                    PIN_setOutputValue(muxPinHandle, IOID_23, 1); //S2
//                    PIN_setOutputValue(muxPinHandle, IOID_12, 0); //S1
//                    PIN_setOutputValue(muxPinHandle, IOID_15, 1); //S0
//                    break;
//               case 7: // AUTOCAL
//                    PIN_setOutputValue(muxPinHandle, IOID_22, 1); //S3
//                    PIN_setOutputValue(muxPinHandle, IOID_23, 1); //S2
//                    PIN_setOutputValue(muxPinHandle, IOID_12, 1); //S1
//                    PIN_setOutputValue(muxPinHandle, IOID_15, 0); //S0
//                    break;
//                case 8: // AUTOCAL
//                    PIN_setOutputValue(muxPinHandle, IOID_22, 1); //S3
//                    PIN_setOutputValue(muxPinHandle, IOID_23, 1); //S2
//                    PIN_setOutputValue(muxPinHandle, IOID_12, 1); //S1
//                    PIN_setOutputValue(muxPinHandle, IOID_15, 1); //S0
//                    break;
//            }
//        }
//    else {
//        switch(muxmod) {
//                case 10: //sensor 0 array pin 10
//                    PIN_setOutputValue(muxPinHandle, IOID_22, 0); //S3
//                    PIN_setOutputValue(muxPinHandle, IOID_23, 0); //S2
//                    PIN_setOutputValue(muxPinHandle, IOID_12, 0); //S1
//                    PIN_setOutputValue(muxPinHandle, IOID_15, 0); //S0
//                    break;
//                case 13: // sensor 1 array pin 13
//                    PIN_setOutputValue(muxPinHandle, IOID_22, 0); //S3
//                    PIN_setOutputValue(muxPinHandle, IOID_23, 0); //S2
//                    PIN_setOutputValue(muxPinHandle, IOID_12, 0); //S1
//                    PIN_setOutputValue(muxPinHandle, IOID_15, 1); //S0
//                    break;
//                case 11: // sensor 2 array pin 11
//                    PIN_setOutputValue(muxPinHandle, IOID_22, 0); //S3
//                    PIN_setOutputValue(muxPinHandle, IOID_23, 0); //S2
//                    PIN_setOutputValue(muxPinHandle, IOID_12, 1); //S1
//                    PIN_setOutputValue(muxPinHandle, IOID_15, 0); //S0
//                    break;
//                case 8: // sensor 3 array pin 8
//                    PIN_setOutputValue(muxPinHandle, IOID_22, 0); //S3
//                    PIN_setOutputValue(muxPinHandle, IOID_23, 0); //S2
//                    PIN_setOutputValue(muxPinHandle, IOID_12, 1); //S1
//                    PIN_setOutputValue(muxPinHandle, IOID_15, 1); //S0
//                    break;
//                case 14: //sensor 4 array pin 14
//                    PIN_setOutputValue(muxPinHandle, IOID_22, 0); //S3
//                    PIN_setOutputValue(muxPinHandle, IOID_23, 1); //S2
//                    PIN_setOutputValue(muxPinHandle, IOID_12, 0); //S1
//                    PIN_setOutputValue(muxPinHandle, IOID_15, 0); //S0
//                    break;
//                case 12: //sensor 5 array pin 12
//                    PIN_setOutputValue(muxPinHandle, IOID_22, 0); //S3
//                    PIN_setOutputValue(muxPinHandle, IOID_23, 1); //S2
//                    PIN_setOutputValue(muxPinHandle, IOID_12, 0); //S1
//                    PIN_setOutputValue(muxPinHandle, IOID_15, 1); //S0
//                    break;
//                case 15: //sensor 6 array pin 15
//                    PIN_setOutputValue(muxPinHandle, IOID_22, 0); //S3
//                    PIN_setOutputValue(muxPinHandle, IOID_23, 1); //S2
//                    PIN_setOutputValue(muxPinHandle, IOID_12, 1); //S1
//                    PIN_setOutputValue(muxPinHandle, IOID_15, 0); //S0
//                    break;
//                case 7: // sensor 7 array pin 7
//                    PIN_setOutputValue(muxPinHandle, IOID_22, 0); //S3
//                    PIN_setOutputValue(muxPinHandle, IOID_23, 1); //S2
//                    PIN_setOutputValue(muxPinHandle, IOID_12, 1); //S1
//                    PIN_setOutputValue(muxPinHandle, IOID_15, 1); //S0
//                    break;
//                case 4: // sensor 8 array pin 4
//                    PIN_setOutputValue(muxPinHandle, IOID_22, 1); //S3
//                    PIN_setOutputValue(muxPinHandle, IOID_23, 0); //S2
//                    PIN_setOutputValue(muxPinHandle, IOID_12, 0); //S1
//                    PIN_setOutputValue(muxPinHandle, IOID_15, 0); //S0
//                    break;
//                case 6: //sensor 9 array pin 6
//                    PIN_setOutputValue(muxPinHandle, IOID_22, 1); //S3
//                    PIN_setOutputValue(muxPinHandle, IOID_23, 0); //S2
//                    PIN_setOutputValue(muxPinHandle, IOID_12, 0); //S1
//                    PIN_setOutputValue(muxPinHandle, IOID_15, 1); //S0
//                    break;
//                case 0: // sensor 10 array pin 0
//                    PIN_setOutputValue(muxPinHandle, IOID_22, 1); //S3
//                    PIN_setOutputValue(muxPinHandle, IOID_23, 0); //S2
//                    PIN_setOutputValue(muxPinHandle, IOID_12, 1); //S1
//                    PIN_setOutputValue(muxPinHandle, IOID_15, 0); //S0
//                    break;
//                case 5: // sensor 11 array pin 5
//                    PIN_setOutputValue(muxPinHandle, IOID_22, 1); //S3
//                    PIN_setOutputValue(muxPinHandle, IOID_23, 0); //S2
//                    PIN_setOutputValue(muxPinHandle, IOID_12, 1); //S1
//                    PIN_setOutputValue(muxPinHandle, IOID_15, 1); //S0
//                    break;
//                case 2: // sensor 12 array pin 2
//                    PIN_setOutputValue(muxPinHandle, IOID_22, 1); //S3
//                    PIN_setOutputValue(muxPinHandle, IOID_23, 1); //S2
//                    PIN_setOutputValue(muxPinHandle, IOID_12, 0); //S1
//                    PIN_setOutputValue(muxPinHandle, IOID_15, 0); //S0
//                    break;
//                case 3: // sensor 13 array pin 3
//                    PIN_setOutputValue(muxPinHandle, IOID_22, 1); //S3
//                    PIN_setOutputValue(muxPinHandle, IOID_23, 1); //S2
//                    PIN_setOutputValue(muxPinHandle, IOID_12, 0); //S1
//                    PIN_setOutputValue(muxPinHandle, IOID_15, 1); //S0
//                    break;
//                case 1: // sensor 14 array pin 1
//                    PIN_setOutputValue(muxPinHandle, IOID_22, 1); //S3
//                    PIN_setOutputValue(muxPinHandle, IOID_23, 1); //S2
//                    PIN_setOutputValue(muxPinHandle, IOID_12, 1); //S1
//                    PIN_setOutputValue(muxPinHandle, IOID_15, 0); //S0
//                    break;
//                case 9: // sensor 15 array pin 9
//                    PIN_setOutputValue(muxPinHandle, IOID_22, 1); //S3
//                    PIN_setOutputValue(muxPinHandle, IOID_23, 1); //S2
//                    PIN_setOutputValue(muxPinHandle, IOID_12, 1); //S1
//                    PIN_setOutputValue(muxPinHandle, IOID_15, 1); //S0
//                    break;
//            }
//    }
//}

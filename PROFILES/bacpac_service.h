/**********************************************************************************************
 * Filename:       bacpac_service.h
 *
 * Description:    This file contains the bacpac_service service definitions and
 *                 prototypes.
 *
 * Copyright (c) 2015-2020, Texas Instruments Incorporated
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
 *
 *************************************************************************************************/


#ifndef _BACPAC_SERVICE_H_
#define _BACPAC_SERVICE_H_

#ifdef __cplusplus
extern "C"
{
#endif

/*********************************************************************
 * INCLUDES
 */

#include <ti/sysbios/knl/Semaphore.h>
extern Semaphore_Handle bacpac_channel_mutex;
extern Semaphore_Handle bacpac_channel_success_mutex;
extern Semaphore_Handle bacpac_channel_error_mutex;
extern Semaphore_Handle bacpac_channel_initialize_mutex;
extern int remaining_data;

/*********************************************************************
* CONSTANTS
*/
// Service UUID
#define BACPAC_SERVICE_SERV_UUID        0xBAC0

//  Characteristic defines
#define BACPAC_SERVICE_CHANNEL_ID       0
#define BACPAC_SERVICE_CHANNEL_UUID     0xBAC1
#define BACPAC_SERVICE_CHANNEL_LEN      20

//  Characteristic defines
#define BACPAC_SERVICE_TRANSFERRING_ID   1
#define BACPAC_SERVICE_TRANSFERRING_UUID 0xBAC2
#define BACPAC_SERVICE_TRANSFERRING_LEN  1

//  Characteristic defines
#define BACPAC_SERVICE_EXERCISING_ID   2
#define BACPAC_SERVICE_EXERCISING_UUID 0xBAC3
#define BACPAC_SERVICE_EXERCISING_LEN  1

/*********************************************************************
 * TYPEDEFS
 */

/*********************************************************************
 * MACROS
 */

/*********************************************************************
 * Profile Callbacks
 */

// Callback when a characteristic value has changed
typedef void (*bacpac_serviceChange_t)(uint16_t connHandle, uint16_t svcUuid, uint8_t paramID, uint16_t len, uint8_t *pValue);

typedef struct
{
  bacpac_serviceChange_t        pfnChangeCb;  // Called when characteristic value changes
  bacpac_serviceChange_t        pfnCfgChangeCb;
} bacpac_serviceCBs_t;



/*********************************************************************
 * API FUNCTIONS
 */


/*
 * Bacpac_service_AddService- Initializes the Bacpac_service service by registering
 *          GATT attributes with the GATT server.
 *
 */
extern bStatus_t Bacpac_service_AddService( uint8_t rspTaskId);

/*
 * Bacpac_service_RegisterAppCBs - Registers the application callback function.
 *                    Only call this function once.
 *
 *    appCallbacks - pointer to application callbacks.
 */
extern bStatus_t Bacpac_service_RegisterAppCBs( bacpac_serviceCBs_t *appCallbacks );

/*
 * Bacpac_service_SetParameter - Set a Bacpac_service parameter.
 *
 *    param - Profile parameter ID
 *    len - length of data to right
 *    value - pointer to data to write.  This is dependent on
 *          the parameter ID and WILL be cast to the appropriate
 *          data type (example: data type of uint16 will be cast to
 *          uint16 pointer).
 */
extern bStatus_t Bacpac_service_SetParameter(uint8_t param, uint16_t len, void *value);

/*
 * Bacpac_service_GetParameter - Get a Bacpac_service parameter.
 *
 *    param - Profile parameter ID
 *    value - pointer to data to write.  This is dependent on
 *          the parameter ID and WILL be cast to the appropriate
 *          data type (example: data type of uint16 will be cast to
 *          uint16 pointer).
 */
extern bStatus_t Bacpac_service_GetParameter(uint8_t param, uint16_t *len, void *value);


extern Semaphore_Handle bacpac_channel_mutex;
/*********************************************************************
*********************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* _BACPAC_SERVICE_H_ */

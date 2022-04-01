/**********************************************************************************************
 * Filename:       bacpac_service.c
 *
 * Description:    This file contains the implementation of the service.
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


/*********************************************************************
 * INCLUDES
 */
#include <string.h>

#include <icall.h>

/* This Header file contains all BLE API and icall structure definition */
#include "icall_ble_api.h"

#include "bacpac_service.h"
#include "Sensors/sensors.h"
#include "Sensors/DiskAccess.h"

/*********************************************************************
 * MACROS
 */

/*********************************************************************
 * CONSTANTS
 */

/*********************************************************************
 * TYPEDEFS
 */

/*********************************************************************
* GLOBAL VARIABLES
*/

Semaphore_Handle bacpac_channel_mutex;
Semaphore_Handle bacpac_channel_success_mutex;
Semaphore_Handle bacpac_channel_error_mutex;
Semaphore_Handle bacpac_channel_initialize_mutex;

// bacpac_service Service UUID
CONST uint8_t bacpac_serviceUUID[ATT_BT_UUID_SIZE] =
{
  LO_UINT16(BACPAC_SERVICE_SERV_UUID), HI_UINT16(BACPAC_SERVICE_SERV_UUID)
};

// channel UUID
CONST uint8_t bacpac_service_ChannelUUID[ATT_UUID_SIZE] =
{
  TI_BASE_UUID_128(BACPAC_SERVICE_CHANNEL_UUID)
};
// transferring UUID
CONST uint8_t bacpac_service_TransferringUUID[ATT_UUID_SIZE] =
{
  TI_BASE_UUID_128(BACPAC_SERVICE_TRANSFERRING_UUID)
};
// exercising UUID
CONST uint8_t bacpac_service_ExercisingUUID[ATT_UUID_SIZE] =
{
  TI_BASE_UUID_128(BACPAC_SERVICE_EXERCISING_UUID)
};

int remaining_data = -1;
/*********************************************************************
 * LOCAL VARIABLES
 */

static bacpac_serviceCBs_t *pAppCBs = NULL;

/*********************************************************************
* Profile Attributes - variables
*/

// Service declaration
static CONST gattAttrType_t bacpac_serviceDecl = { ATT_BT_UUID_SIZE, bacpac_serviceUUID };

// Characteristic "Channel" Properties (for declaration)
static uint8_t bacpac_service_ChannelProps = GATT_PROP_READ | GATT_PROP_NOTIFY;

// Characteristic "Channel" Value variable
static uint8_t bacpac_service_ChannelVal[BACPAC_SERVICE_CHANNEL_LEN] = { 0 };

// Characteristic "Channel" description
static uint8 bacpac_service_ChannelDesc[8] = "Channel";

// Characteristic "Channel" CCCD
static gattCharCfg_t *bacpac_service_ChannelConfig;

// Characteristic "Transferring" Properties (for declaration)
static uint8_t bacpac_service_TransferringProps = GATT_PROP_READ | GATT_PROP_WRITE;

// Characteristic "Transferring" Value variable
static uint8_t bacpac_service_TransferringVal[BACPAC_SERVICE_TRANSFERRING_LEN] = {0};

// Characteristic "Transferring" description
static uint8 bacpac_service_TransferringDesc[13] = "Transferring";

// Characteristic "Exercising" Properties (for declaration)
static uint8_t bacpac_service_ExercisingProps = GATT_PROP_READ | GATT_PROP_WRITE;

// Characteristic "Exercising" Value variable
static uint8_t bacpac_service_ExercisingVal[BACPAC_SERVICE_EXERCISING_LEN] = {0};

// Characteristic "Exercising" description
static uint8 bacpac_service_ExercisingDesc[11] = "Exercising";




/*********************************************************************
* Profile Attributes - Table
*/

static gattAttribute_t bacpac_serviceAttrTbl[11] =
{
  // bacpac_service Service Declaration
  {
    { ATT_BT_UUID_SIZE, primaryServiceUUID },
    GATT_PERMIT_READ,
    0,
    (uint8_t *)&bacpac_serviceDecl
  },
    // Channel Characteristic Declaration
    {
      { ATT_BT_UUID_SIZE, characterUUID },
      GATT_PERMIT_READ,
      0,
      &bacpac_service_ChannelProps
    },
      // Channel Characteristic Value
      {
        { ATT_UUID_SIZE, bacpac_service_ChannelUUID },
        GATT_PERMIT_READ,
        0,
        bacpac_service_ChannelVal
      },
      // Channel Description
      {
        { ATT_BT_UUID_SIZE, charUserDescUUID },
        GATT_PERMIT_READ,
        0,
        bacpac_service_ChannelDesc
      },
      // Channel CCCD
      {
        { ATT_BT_UUID_SIZE, clientCharCfgUUID },
        GATT_PERMIT_READ | GATT_PERMIT_WRITE,
        0,
        (uint8 *)&bacpac_service_ChannelConfig
      },
    // Transferring Characteristic Declaration
    {
      { ATT_BT_UUID_SIZE, characterUUID },
      GATT_PERMIT_READ,
      0,
      &bacpac_service_TransferringProps
    },
      // Transferring Characteristic Value
      {
        { ATT_UUID_SIZE, bacpac_service_TransferringUUID },
        GATT_PERMIT_READ | GATT_PERMIT_WRITE,
        0,
        bacpac_service_TransferringVal
      },
      // Transferring Description
      {
        { ATT_BT_UUID_SIZE, charUserDescUUID },
        GATT_PERMIT_READ,
        0,
        bacpac_service_TransferringDesc
      },
    // Exercising Characteristic Declaration
    {
      { ATT_BT_UUID_SIZE, characterUUID },
      GATT_PERMIT_READ,
      0,
      &bacpac_service_ExercisingProps
    },
      // Exercising Characteristic Value
      {
        { ATT_UUID_SIZE, bacpac_service_ExercisingUUID },
        GATT_PERMIT_READ | GATT_PERMIT_WRITE,
        0,
        bacpac_service_ExercisingVal
      },
      // Exercising Description
      {
        { ATT_BT_UUID_SIZE, charUserDescUUID },
        GATT_PERMIT_READ,
        0,
        bacpac_service_ExercisingDesc
      },
};

/*********************************************************************
 * LOCAL FUNCTIONS
 */
static bStatus_t bacpac_service_ReadAttrCB( uint16_t connHandle, gattAttribute_t *pAttr,
                                           uint8_t *pValue, uint16_t *pLen, uint16_t offset,
                                           uint16_t maxLen, uint8_t method );
static bStatus_t bacpac_service_WriteAttrCB( uint16_t connHandle, gattAttribute_t *pAttr,
                                            uint8_t *pValue, uint16_t len, uint16_t offset,
                                            uint8_t method );

/*********************************************************************
 * PROFILE CALLBACKS
 */
// Simple Profile Service Callbacks
CONST gattServiceCBs_t bacpac_serviceCBs =
{
  bacpac_service_ReadAttrCB,  // Read callback function pointer
  bacpac_service_WriteAttrCB, // Write callback function pointer
  NULL                       // Authorization callback function pointer
};

/*********************************************************************
* PUBLIC FUNCTIONS
*/

/*
 * Bacpac_service_AddService- Initializes the Bacpac_service service by registering
 *          GATT attributes with the GATT server.
 *
 */
extern bStatus_t Bacpac_service_AddService( uint8_t rspTaskId )
{
  uint8_t status;

  bacpac_service_ChannelConfig = (gattCharCfg_t *)ICall_malloc( sizeof(gattCharCfg_t) * linkDBNumConns );
   if ( bacpac_service_ChannelConfig == NULL )
   {
     return ( bleMemAllocError );
   }

   // Initialize Client Characteristic Configuration attributes
   GATTServApp_InitCharCfg( LINKDB_CONNHANDLE_INVALID, bacpac_service_ChannelConfig );


   // Register GATT attribute list and CBs with GATT Server App
    status = GATTServApp_RegisterService( bacpac_serviceAttrTbl,
                                       GATT_NUM_ATTRS( bacpac_serviceAttrTbl ),
                                       GATT_MAX_ENCRYPT_KEY_SIZE,
                                       &bacpac_serviceCBs );




  return ( status );
}

/*
 * Bacpac_service_RegisterAppCBs - Registers the application callback function.
 *                    Only call this function once.
 *
 *    appCallbacks - pointer to application callbacks.
 */
bStatus_t Bacpac_service_RegisterAppCBs( bacpac_serviceCBs_t *appCallbacks )
{
  if ( appCallbacks )
  {
    pAppCBs = appCallbacks;

    return ( SUCCESS );
  }
  else
  {
    return ( bleAlreadyInRequestedMode );
  }
}

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
bStatus_t Bacpac_service_SetParameter( uint8_t param, uint16_t len, void *value )
{
  bStatus_t ret = SUCCESS;
  switch ( param )
  {
    case BACPAC_SERVICE_CHANNEL_ID:
      if ( len == BACPAC_SERVICE_CHANNEL_LEN )
      {
        memcpy(bacpac_service_ChannelVal, value, len);

        // Try to send notification.
        GATTServApp_ProcessCharCfg( bacpac_service_ChannelConfig, (uint8_t *)&bacpac_service_ChannelVal, FALSE,
                                    bacpac_serviceAttrTbl, GATT_NUM_ATTRS( bacpac_serviceAttrTbl ),
                                    INVALID_TASK_ID,  bacpac_service_ReadAttrCB);
      }
      else
      {
        ret = bleInvalidRange;
      }
      break;

    case BACPAC_SERVICE_TRANSFERRING_ID:
      if ( len == BACPAC_SERVICE_TRANSFERRING_LEN )
      {
        memcpy(bacpac_service_TransferringVal, value, len);
      }
      else
      {
        ret = bleInvalidRange;
      }
      break;

    case BACPAC_SERVICE_EXERCISING_ID:
      if ( len == BACPAC_SERVICE_EXERCISING_LEN )
      {
        memcpy(bacpac_service_ExercisingVal, value, len);
      }
      else
      {
        ret = bleInvalidRange;
      }
      break;

    default:
      ret = INVALIDPARAMETER;
      break;
  }
  return ret;
}


/*
 * Bacpac_service_GetParameter - Get a Bacpac_service parameter.
 *
 *    param - Profile parameter ID
 *    value - pointer to data to write.  This is dependent on
 *          the parameter ID and WILL be cast to the appropriate
 *          data type (example: data type of uint16 will be cast to
 *          uint16 pointer).
 */
bStatus_t Bacpac_service_GetParameter( uint8_t param, uint16_t *len, void *value )
{
  bStatus_t ret = SUCCESS;
  switch ( param )
  {
    case BACPAC_SERVICE_TRANSFERRING_ID:
      memcpy(value, bacpac_service_TransferringVal, BACPAC_SERVICE_TRANSFERRING_LEN);
      break;

    case BACPAC_SERVICE_EXERCISING_ID:
      memcpy(value, bacpac_service_ExercisingVal, BACPAC_SERVICE_EXERCISING_LEN);
      break;

    default:
      ret = INVALIDPARAMETER;
      break;
  }
  return ret;
}


/*********************************************************************
 * @fn          bacpac_service_ReadAttrCB
 *
 * @brief       Read an attribute.
 *
 * @param       connHandle - connection message was received on
 * @param       pAttr - pointer to attribute
 * @param       pValue - pointer to data to be read
 * @param       pLen - length of data to be read
 * @param       offset - offset of the first octet to be read
 * @param       maxLen - maximum length of data to be read
 * @param       method - type of read message
 *
 * @return      SUCCESS, blePending or Failure
 */
static bStatus_t bacpac_service_ReadAttrCB( uint16_t connHandle, gattAttribute_t *pAttr,
                                       uint8_t *pValue, uint16_t *pLen, uint16_t offset,
                                       uint16_t maxLen, uint8_t method )
{
  bStatus_t status = SUCCESS;

  // See if request is regarding the Channel Characteristic Value
if ( ! memcmp(pAttr->type.uuid, bacpac_service_ChannelUUID, pAttr->type.len) )
  {
    if ( offset > BACPAC_SERVICE_CHANNEL_LEN )  // Prevent malicious ATT ReadBlob offsets.
    {
      status = ATT_ERR_INVALID_OFFSET;
    }
    else
    {
      *pLen = MIN(maxLen, BACPAC_SERVICE_CHANNEL_LEN - offset);  // Transmit as much as possible
      memcpy(pValue, pAttr->pValue + offset, *pLen);
      //hello_world();
      //if (remaining_data > 0) Semaphore_post(bacpac_channel_mutex);
    }
  }
  // See if request is regarding the Transferring Characteristic Value
else if ( ! memcmp(pAttr->type.uuid, bacpac_service_TransferringUUID, pAttr->type.len) )
  {
    if ( offset > BACPAC_SERVICE_TRANSFERRING_LEN )  // Prevent malicious ATT ReadBlob offsets.
    {
      status = ATT_ERR_INVALID_OFFSET;
    }
    else
    {
      *pLen = MIN(maxLen, BACPAC_SERVICE_TRANSFERRING_LEN - offset);  // Transmit as much as possible
      memcpy(pValue, pAttr->pValue + offset, *pLen);
    }
  }
  // See if request is regarding the Exercising Characteristic Value
else if ( ! memcmp(pAttr->type.uuid, bacpac_service_ExercisingUUID, pAttr->type.len) )
  {
    if ( offset > BACPAC_SERVICE_EXERCISING_LEN )  // Prevent malicious ATT ReadBlob offsets.
    {
      status = ATT_ERR_INVALID_OFFSET;
    }
    else
    {
      *pLen = MIN(maxLen, BACPAC_SERVICE_EXERCISING_LEN - offset);  // Transmit as much as possible
      memcpy(pValue, pAttr->pValue + offset, *pLen);
    }
  }
  else
  {
    // If we get here, that means you've forgotten to add an if clause for a
    // characteristic value attribute in the attribute table that has READ permissions.
    *pLen = 0;
    status = ATT_ERR_ATTR_NOT_FOUND;
  }

  return status;
}


/*********************************************************************
 * @fn      bacpac_service_WriteAttrCB
 *
 * @brief   Validate attribute data prior to a write operation
 *
 * @param   connHandle - connection message was received on
 * @param   pAttr - pointer to attribute
 * @param   pValue - pointer to data to be written
 * @param   len - length of data
 * @param   offset - offset of the first octet to be written
 * @param   method - type of write message
 *
 * @return  SUCCESS, blePending or Failure
 */
static bStatus_t bacpac_service_WriteAttrCB( uint16_t connHandle, gattAttribute_t *pAttr,
                                        uint8_t *pValue, uint16_t len, uint16_t offset,
                                        uint8_t method )
{
  bStatus_t status  = SUCCESS;
  uint8_t   paramID = 0xFF;

  // See if request is regarding a Client Characterisic Configuration
  if ( ! memcmp(pAttr->type.uuid, clientCharCfgUUID, pAttr->type.len) )
  {
    // Allow only notifications.
    status = GATTServApp_ProcessCCCWriteReq( connHandle, pAttr, pValue, len,
                                             offset, GATT_CLIENT_CFG_NOTIFY);
  }
  // See if request is regarding the Transferring Characteristic Value
  else if ( ! memcmp(pAttr->type.uuid, bacpac_service_TransferringUUID, pAttr->type.len) )
  {
    if ( offset + len > BACPAC_SERVICE_TRANSFERRING_LEN )
    {
      status = ATT_ERR_INVALID_OFFSET;
    }
    else
    {
      // Copy pValue into the variable we point to from the attribute table.
      memcpy(pAttr->pValue + offset, pValue, len);

      switch (pAttr->pValue[0]){
      case 0:
          Sensors_read_test();
          break;
      case 1:
          Sensors_write_test();
          break;
      case 2:
          Sensors_clear_test();
          break;
      case 3:
          Sensors_close_test();
          break;
      case 4:
          Sensors_load_test();
          break;
      case 5:
          Sensors_size_test();
          break;
      case 6:
          Sensors_timer_test();
          break;
      case 0x07:
          Semaphore_post(bacpac_channel_initialize_mutex);
          break;
      case 0x08:
          Semaphore_post(bacpac_channel_success_mutex);
          // chunk success;
          break;
      case 0x09:
          Semaphore_post(bacpac_channel_error_mutex);
          // chunk failed
          break;
      default:
          Sensors_pos_test();
      };
      // Only notify application if entire expected value is written
      if ( offset + len == BACPAC_SERVICE_TRANSFERRING_LEN)
        paramID = BACPAC_SERVICE_TRANSFERRING_ID;
    }
  }
  // See if request is regarding the Exercising Characteristic Value
  else if ( ! memcmp(pAttr->type.uuid, bacpac_service_ExercisingUUID, pAttr->type.len) )
  {
    if ( offset + len > BACPAC_SERVICE_EXERCISING_LEN )
    {
      status = ATT_ERR_INVALID_OFFSET;
    }
    else
    {
      // Copy pValue into the variable we point to from the attribute table.
      memcpy(pAttr->pValue + offset, pValue, len);
      if (pAttr->pValue[0]) Sensors_start_timers();
      else Sensors_stop_timers();

      // Only notify application if entire expected value is written
      if ( offset + len == BACPAC_SERVICE_EXERCISING_LEN)
        paramID = BACPAC_SERVICE_EXERCISING_ID;
    }
  }
  else
  {
    // If we get here, that means you've forgotten to add an if clause for a
    // characteristic value attribute in the attribute table that has WRITE permissions.
    status = ATT_ERR_ATTR_NOT_FOUND;
  }

  // Let the application know something changed (if it did) by using the
  // callback it registered earlier (if it did).
  if (paramID != 0xFF)
    if ( pAppCBs && pAppCBs->pfnChangeCb )
    {
      uint16_t svcUuid = BACPAC_SERVICE_SERV_UUID;
      pAppCBs->pfnChangeCb(connHandle, svcUuid, paramID, len, pValue); // Call app function from stack task context.
    }
  return status;
}

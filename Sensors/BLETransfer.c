#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/BIOS.h>

#include "DiskAccess.h"
#include "icall_ble_api.h"
#include "../PROFILES/bacpac_service.h"
#include "BLETransfer.h"

#define BLE_TRANSFER_TASK_PRIORITY       1

#ifndef BLE_TRANSFER_TASK_STACK_SIZE
#define BLE_TRANSFER_TASK_STACK_SIZE     300
#endif

Task_Struct BLETransferTask;
Char BLETransferTaskStack[BLE_TRANSFER_TASK_STACK_SIZE];

//Semaphore_Handle bacpac_channel_mutex;
//Semaphore_Struct bacpac_channel_mutex_struct;
//char bleChannelBuf[BACPAC_SERVICE_CHANNEL_LEN];

static void BLE_transfer_taskFxn(UArg a0, UArg a1) {
    BLE_transfer_init();

   Task_sleep(BIOS_WAIT_FOREVER);
}

void BLE_transfer_init() {
/*
    Semaphore_Params channelParams;
    Semaphore_Params_init(&channelParams);
    channelParams.mode = Semaphore_Mode_BINARY;
    Semaphore_construct(&bacpac_channel_mutex_struct, 0, &channelParams);
    bacpac_channel_mutex = Semaphore_handle(&bacpac_channel_mutex_struct);
*/
}

void BLE_transfer_createTask(void) {

    Task_Params taskParams;

    // Configure task
    Task_Params_init(&taskParams);
    taskParams.stack = BLETransferTaskStack;
    taskParams.stackSize = BLE_TRANSFER_TASK_STACK_SIZE;
    taskParams.priority = BLE_TRANSFER_TASK_PRIORITY;

    Task_construct(&BLETransferTask, BLE_transfer_taskFxn, &taskParams, NULL);

}




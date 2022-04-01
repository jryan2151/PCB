#include "Storage.h"
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/BIOS.h>
#include <stdlib.h>

#define STORAGE_TASK_PRIORITY       1

#ifndef STORAGE_TASK_STACK_SIZE
#define STORAGE_TASK_STACK_SIZE     448//644
#endif

#ifndef STORAGE_BUF_SIZE
#define STORAGE_BUF_SIZE            64
#endif

Semaphore_Struct storage_buffer_mailbox_struct;
Semaphore_Handle storage_buffer_mailbox;
Semaphore_Struct storage_buffer_mutex_struct;
Semaphore_Handle storage_buffer_mutex;

char storage_buffer[STORAGE_BUF_SIZE];
uint8_t storage_buffer_length;
static uint8_t storage_status;

Task_Struct storageTask;
Char storageTaskStack[STORAGE_TASK_STACK_SIZE];

uint8_t getStatus() {
    return storage_status;
}

static void Storage_taskFxn(UArg a0, UArg a1) {
    Storage_init();
    const int SLEEP_TIME = 10;

    while (storage_status == 0) {
        Semaphore_pend(storage_buffer_mailbox, BIOS_WAIT_FOREVER);

        if (storage_status == 0) {
            if (da_write(storage_buffer, storage_buffer_length) != DISK_SUCCESS) ;//storage_status = 1;
        }

        Semaphore_post(storage_buffer_mutex);
    }
}

void Storage_init() {
    Semaphore_Params bufParams;
    Semaphore_Params mailParams;


    Semaphore_Params_init(&bufParams);
    Semaphore_Params_init(&mailParams);

    bufParams.mode = Semaphore_Mode_BINARY;
    mailParams.mode = Semaphore_Mode_BINARY;

    Semaphore_construct(&storage_buffer_mutex_struct, 1, &bufParams);
    Semaphore_construct(&storage_buffer_mailbox_struct, 0, &mailParams);

    storage_buffer_mutex = Semaphore_handle(&storage_buffer_mutex_struct);
    storage_buffer_mailbox = Semaphore_handle(&storage_buffer_mailbox_struct);

}

void Storage_createTask(void) {
  Task_Params taskParams;

  // Configure task
  Task_Params_init(&taskParams);
  taskParams.stack = storageTaskStack;
  taskParams.stackSize = STORAGE_TASK_STACK_SIZE;
  taskParams.priority = STORAGE_TASK_PRIORITY;

  Task_construct(&storageTask, Storage_taskFxn, &taskParams, NULL);
}

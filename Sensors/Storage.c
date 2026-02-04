#include "Storage.h"
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/BIOS.h>
#include <ti/drivers/UART.h>
#include <stdlib.h>

extern UART_Handle uart;

#define STORAGE_TASK_PRIORITY       1

#ifndef STORAGE_TASK_STACK_SIZE
#define STORAGE_TASK_STACK_SIZE     448//644
#endif

#ifndef STORAGE_BUF_SIZE
#define STORAGE_BUF_SIZE            128
#endif

Semaphore_Struct storage_buffer_mailbox_struct;
Semaphore_Handle storage_buffer_mailbox;
Semaphore_Struct storage_buffer_mutex_struct;
Semaphore_Handle storage_buffer_mutex;
Semaphore_Struct storage_init_complete_struct;
Semaphore_Handle storage_init_complete;

char storage_buffer[STORAGE_BUF_SIZE];
uint8_t storage_buffer_length;
static uint8_t storage_status;

Task_Struct storageTask;
Char storageTaskStack[STORAGE_TASK_STACK_SIZE];

uint8_t getStatus() {
    return storage_status;
}

static void Storage_taskFxn(UArg a0, UArg a1) {
    // Note: Storage_init() is now called in Storage_createTask() to avoid race condition

    // Wait for sensors/UART/disk initialization to complete before starting
    Semaphore_pend(storage_init_complete, BIOS_WAIT_FOREVER);

    UART_write(uart, "ST\r\n", 4);  // Storage Task started

    while (true) {
        Semaphore_pend(storage_buffer_mailbox, BIOS_WAIT_FOREVER);
        storage_status = 0;

        UART_write(uart, "SW\r\n", 4);  // Storage Write starting

        int wr = da_write(storage_buffer, storage_buffer_length);
        if (wr != DISK_SUCCESS) {
            storage_status = 1;
            UART_write(uart, "WF\r\n", 4);  // Write Failed
        }

        int cm = da_commit();
        if (cm != DISK_SUCCESS) {
            storage_status = 1;
            UART_write(uart, "CF\r\n", 4);  // Commit Failed
        }

        if (storage_status == 0) {
            UART_write(uart, "OK\r\n", 4);  // Write OK
        }

        Semaphore_post(storage_buffer_mutex);
    }
}

void Storage_init() {
    Semaphore_Params bufParams;
    Semaphore_Params mailParams;
    Semaphore_Params initParams;

    Semaphore_Params_init(&bufParams);
    Semaphore_Params_init(&mailParams);
    Semaphore_Params_init(&initParams);

    bufParams.mode = Semaphore_Mode_BINARY;
    mailParams.mode = Semaphore_Mode_BINARY;
    initParams.mode = Semaphore_Mode_BINARY;

    Semaphore_construct(&storage_buffer_mutex_struct, 1, &bufParams);
    Semaphore_construct(&storage_buffer_mailbox_struct, 0, &mailParams);
    Semaphore_construct(&storage_init_complete_struct, 0, &initParams);  // Starts at 0, blocks until posted

    storage_buffer_mutex = Semaphore_handle(&storage_buffer_mutex_struct);
    storage_buffer_mailbox = Semaphore_handle(&storage_buffer_mailbox_struct);
    storage_init_complete = Semaphore_handle(&storage_init_complete_struct);
}

void Storage_createTask(void) {
  Task_Params taskParams;

  // Initialize semaphores BEFORE creating the task to avoid race condition
  Storage_init();

  // Configure task
  Task_Params_init(&taskParams);
  taskParams.stack = storageTaskStack;
  taskParams.stackSize = STORAGE_TASK_STACK_SIZE;
  taskParams.priority = STORAGE_TASK_PRIORITY;

  Task_construct(&storageTask, Storage_taskFxn, &taskParams, NULL);
}

char* Storage_get_transaction_buffer() {
    return da_get_transaction_buffer();
}

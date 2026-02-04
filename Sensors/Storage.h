#ifndef STORAGE_H
#define STORAGE_H

#include <ti/sysbios/knl/Semaphore.h>
#include "DiskAccess.h"

extern Semaphore_Handle storage_buffer_mailbox;
extern Semaphore_Handle storage_buffer_mutex;
extern Semaphore_Handle storage_init_complete;

extern char storage_buffer[];
extern uint8_t storage_buffer_length;

void Storage_init();
extern void Storage_createTask(void);
uint8_t getStatus();

//TODO: remove this dangerous function
char* Storage_get_transaction_buffer();


#endif

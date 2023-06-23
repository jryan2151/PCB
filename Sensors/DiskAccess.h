#ifndef DISKACCESS_H
#define DISKACCESS_H

#include <ti/drivers/SD.h>
#include <xdc/runtime/System.h>
#include "Board.h"
#include <semaphore.h>
//#include "Application/simple_peripheral.h"



// comment out these lines below when putting on board
//#include "SDRaw.h"
// =======================================================

#define DISK_SUCCESS         1
#define DISK_NULL_HANDLE    -1
#define DISK_FAILED_INIT    -2
#define DISK_FAILED_READ    -3
#define DISK_FAILED_WRITE   -4
#define DISK_LOCKED         -5

static unsigned int cur_sector_num = -1;

extern sem_t storage_mutex;

// struct SDCard card;

// initializes sd card
int da_initialize();

int da_get_read_pos();
int da_get_write_pos();
int da_get_sector_size();
unsigned int da_get_num_sectors();


//free txn buffer
int da_destructor();

int da_clear();

// load SD card info into SD struct
int da_load();
int da_close();

// writes to sd card. We only append.
int da_write(char* buffer, int size);
void da_set_write_pos(int position);

// reads from position. Position should be initialized to second sector.
// first sector reserved to track file size
int da_read(char* buffer, int size);
int da_get_cur_sector();
int da_get_sector(int sector);
int da_get_data_size();

int da_soft_commit();
int da_soft_rollback();
int da_commit();

// TODO: delete this function. Only adding it for debugging purposes. This is a dangerous function
char* da_get_transaction_buffer();

#endif

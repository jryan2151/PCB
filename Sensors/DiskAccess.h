#ifndef DISKACCESS_H
#define DISKACCESS_H

#include <ti/drivers/SD.h>
#include <xdc/runtime/System.h>
#include "Board.h"
#include <semaphore.h>


// comment out these lines below when putting on board
//#include "SDRaw.h"
//#define Board_SD0 0
// =======================================================

#define DISK_SUCCESS         1
#define DISK_NULL_HANDLE    -1
#define DISK_FAILED_INIT    -2
#define DISK_FAILED_READ    -3
#define DISK_FAILED_WRITE   -4
#define DISK_LOCKED         -5


extern sem_t storage_mutex;

// struct SDCard card;

// initializes sd card
int da_initialize();

int da_get_read_pos();
int da_get_write_pos();
int da_get_sector_size();
int da_get_num_sectors();

//free txn buffer
int da_destructor();

int da_clear();

// load SD card info into SD struct
int da_load();
int da_close();

// writes to sd card. We only append.
int da_write(char* buffer, int size);

// reads from position. Position should be initialized to second sector.
// first sector reserved to track file size
int da_read(char* buffer, int size);

int da_get_sector(int sector);

int da_get_data_size();

int da_soft_commit();
int da_soft_rollback();

#endif

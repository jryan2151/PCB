#ifndef DISKACCESS_H
#define DISKACCESS_H

#include <ti/drivers/SD.h>
#include <xdc/runtime/System.h>
#include "Board.h"
#include <stdint.h>

/* -----------------------------------------------------------------------
 * Return codes
 * --------------------------------------------------------------------- */
#define DISK_SUCCESS         1
#define DISK_NULL_HANDLE    -1
#define DISK_FAILED_INIT    -2
#define DISK_FAILED_READ    -3
#define DISK_FAILED_WRITE   -4
#define DISK_LOCKED         -5
#define DISK_NO_SPACE       -6   /* SD card full — no free clusters */

/* -----------------------------------------------------------------------
 * Thresholds (tunable)
 * --------------------------------------------------------------------- */
/* Sectors accumulated before a hard-commit (metadata + f_sync).
 * 16 × 512 B = 8 KB — covers MLC/TLC NAND page sizes.          */
#define DA_SYNC_SECTORS             16u

/* File size at which a rollover to the next dataN.txt is triggered. */
#define DA_FILE_ROLLOVER_THRESHOLD  (1048576UL)   /* 1 MB */

/* -----------------------------------------------------------------------
 * Public API
 * --------------------------------------------------------------------- */

/* Mount filesystem, query geometry, malloc txn_buffer.
 * Must be called before da_load(). */
int da_initialize(void);

/* Scan SD for next available dataN.txt, open+preallocate it, write
 * initial metadata sector, f_sync.  Idempotent on remount. */
int da_load(void);

/* Flush dirty sector, write metadata, f_sync, f_close, unmount. */
int da_close(void);

/* Append <size> bytes from <buffer> into the circular data area.
 * Triggers file rollover internally when DA_FILE_ROLLOVER_THRESHOLD
 * is reached. */
int da_write(char* buffer, int size);

/* Flush dirty sector to SD.  Writes metadata + f_sync only when
 * DA_SYNC_SECTORS sectors have accumulated since last hard-commit. */
int da_commit(void);

/* Read <size> bytes from current read position. */
int da_read(char* buffer, int size);

/* Reset write/read positions and zero txn_buffer (no SD I/O). */
int da_clear(void);

/* Getters */
int          da_get_read_pos(void);
int          da_get_write_pos(void);
int          da_get_sector_size(void);
unsigned int da_get_num_sectors(void);
int          da_get_cur_sector(void);
int          da_get_data_size(void);
uint32_t     da_get_current_file_number(void);
const char*  da_get_current_filename(void);

void da_set_write_pos(int position);

/* Soft read-position checkpoint (for BLE streaming) */
int da_soft_commit(void);
int da_soft_rollback(void);

/* Low-level sector access */
int da_get_sector(int sector);

/* Debug — do not use in production */
char* da_get_transaction_buffer(void);

#endif /* DISKACCESS_H */

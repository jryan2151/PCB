#ifndef DISKACCESS_H
#define DISKACCESS_H

#include <xdc/runtime/System.h>
#include <ti/drivers/UART.h>

#define DISK_SUCCESS         1
#define DISK_NULL_HANDLE    -1
#define DISK_FAILED_INIT    -2
#define DISK_FAILED_READ    -3
#define DISK_FAILED_WRITE   -4
#define DISK_LOCKED         -5

// Initialize (mount filesystem)
int da_initialize();

// Open next available log file (logN.csv)
int da_load();

// Close file and unmount
int da_close();

// Append a line of text to the log file
int da_append(const char* buffer, int size);

// Read bytes from current read position (for BLE readback)
int da_read(char* buffer, int size);

// Flush file to disk
int da_commit();

// Reset read position to 0
int da_clear();

// Getters
int da_get_data_size();
int da_get_read_pos();
int da_get_write_pos();
int da_get_sector_size();
unsigned int da_get_num_sectors();

// No-op: append-only writes
void da_set_write_pos(int position);

// Soft commit/rollback for BLE chunked reads
int da_soft_commit();
int da_soft_rollback();

// Debug
const char* da_get_debug_msg(void);
int da_get_last_error();
int da_get_last_file_num();
int da_is_mounted(void);
void da_set_uart(UART_Handle h);

#endif

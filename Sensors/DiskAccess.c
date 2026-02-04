#include "DiskAccess.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "ff.h"
#include "diskio.h"
#include <ti/sysbios/knl/Task.h>
#include <ti/drivers/UART.h>
extern UART_Handle uart;  // Use the uart handle from sensors.c
extern char* uartBuf;      // Use the buffer from sensors.c

static FATFS g_sFatFs;
static FIL   g_logFile;
static int   fs_mounted = 0;


static unsigned long write_pos;
static unsigned long read_pos;
static unsigned int  sector_size;
static unsigned int  num_sectors;
static unsigned char dirty;
static unsigned long long total_size;
static char* txn_buffer;

static unsigned long soft_read_pos;

uint32_t cur_sector_num = 0U;
static uint32_t current_session_id = 0;
static char current_log_filename[32];

int da_initialize() {
    FRESULT fr;

    // Use mode 1 (immediate mount) like the working version
    fr = f_mount(&g_sFatFs, "0:", 1);

    if (fr != FR_OK) {
        fs_mounted = 0;
        return DISK_FAILED_INIT;
    }

    fs_mounted = 1;

    WORD  phys_sector_size = 0;
    DWORD sector_count     = 0;

    if (disk_ioctl(0, GET_SECTOR_SIZE, &phys_sector_size) == RES_OK && phys_sector_size > 0) {
        sector_size = (unsigned int)phys_sector_size;
    } else {
        sector_size = 512;
    }

    if (disk_ioctl(0, GET_SECTOR_COUNT, &sector_count) == RES_OK && sector_count > 1) {
        num_sectors = (unsigned int)(sector_count - 1);
    } else {
        num_sectors = 2047;
    }

    total_size = (unsigned long long)num_sectors * sector_size;

    txn_buffer = (char *)malloc(sector_size * sizeof(char));
    if (!txn_buffer) {
        f_mount(NULL, "0:", 1);
        fs_mounted = 0;
        return DISK_FAILED_INIT;
    }

    soft_read_pos = 0;

    return DISK_SUCCESS;
}

// Helper function to read session counter from index file
static uint32_t da_read_session_counter() {
    FRESULT fr;
    FIL indexFile;
    UINT br;
    char buffer[32];
    uint32_t session_id = 1;

    fr = f_open(&indexFile, "session.idx", FA_READ);
    if (fr == FR_OK) {
        // File exists, read the session counter
        memset(buffer, 0, sizeof(buffer));
        fr = f_read(&indexFile, buffer, sizeof(buffer) - 1, &br);
        if (fr == FR_OK && br > 0) {
            buffer[br] = '\0';
            session_id = (uint32_t)atoi(buffer);
            if (session_id == 0) session_id = 1; // Safety check
            System_printf("da_read_session_counter: Read session ID %lu from file\n", session_id);
        } else {
            System_printf("da_read_session_counter: Read failed, using default session ID 1\n");
        }
        f_close(&indexFile);
    } else {
        System_printf("da_read_session_counter: session.idx not found, using session ID 1\n");
    }

    return session_id;
}

// Helper function to write session counter to index file
static int da_write_session_counter(uint32_t session_id) {
    FRESULT fr;
    FIL indexFile;
    UINT bw;
    char buffer[32];

    fr = f_open(&indexFile, "session.idx", FA_WRITE | FA_CREATE_ALWAYS);
    if (fr != FR_OK) {
        System_printf("da_write_session_counter: Failed to open session.idx, error %d\n", fr);
        return DISK_FAILED_WRITE;
    }

    System_sprintf(buffer, "%lu", session_id);
    fr = f_write(&indexFile, buffer, strlen(buffer), &bw);
    if (fr != FR_OK || bw != strlen(buffer)) {
        System_printf("da_write_session_counter: Write failed, error %d\n", fr);
        f_close(&indexFile);
        return DISK_FAILED_WRITE;
    }

    f_sync(&indexFile);
    f_close(&indexFile);

    System_printf("da_write_session_counter: Wrote session ID %lu to file\n", session_id);
    return DISK_SUCCESS;
}

int da_load() {
//    UART_write(uart, "LOAD\r\n", 6);

    if (!fs_mounted) {
        UART_write(uart, "REMOUNT\r\n", 9);
        int result = da_initialize();
        if (result != DISK_SUCCESS) {
            return result;
        }
    }

    FRESULT fr;
    UINT br, bw;

//    UART_write(uart, "SESSION\r\n", 9);

    // Read current session counter
    current_session_id = da_read_session_counter();

//    UART_write(uart, "FILENAME\r\n", 10);  // ADD THIS

    // Create new log filename for this session
    System_sprintf(current_log_filename, "log_%03lu.bin", current_session_id);

    UART_write(uart, "FOPEN\r\n", 7);  // ADD THIS

    // Open the new session log file
    fr = f_open(&g_logFile, current_log_filename, FA_READ | FA_WRITE | FA_CREATE_ALWAYS);

    UART_write(uart, "FOPEN_DONE\r\n", 12);  // ADD THIS

    if (fr != FR_OK) {
        return DISK_FAILED_INIT;
    }

    UART_write(uart, "OPENED\r\n", 8);  // ADD THIS

    // Preallocate file space
    if (num_sectors == 0) {
        num_sectors = 2047;
        total_size  = (unsigned long long)num_sectors * sector_size;
    }

    DWORD newSize = (DWORD)(num_sectors + 1) * sector_size;

    UART_write(uart, "SEEK\r\n", 6);  // ADD THIS

    fr = f_lseek(&g_logFile, newSize - 1);

    UART_write(uart, "SEEK_DONE\r\n", 11);  // ADD THIS

    System_printf("da_load: f_lseek returned %d\n", fr);
    System_flush();

    if (fr != FR_OK) {
        System_printf("da_load: f_lseek failed, error %d\n", fr);
        System_flush();
        f_close(&g_logFile);
        return DISK_FAILED_INIT;
    }

    System_printf("da_load: Writing preallocation byte...\n");
    System_flush();

    BYTE zero = 0;
    fr = f_write(&g_logFile, &zero, 1, &bw);

    System_printf("da_load: f_write returned %d, wrote %u bytes\n", fr, bw);
    System_flush();

    if (fr != FR_OK || bw != 1) {
        System_printf("da_load: Preallocation write failed, error %d\n", fr);
        System_flush();
        f_close(&g_logFile);
        return DISK_FAILED_INIT;
    }

    System_printf("da_load: Preallocation complete\n");
    System_flush();

    // Initialize positions for new session
    write_pos = 0;
    read_pos  = 0;

    // Write initial metadata to first sector
    System_printf("da_load: Preparing metadata...\n");
    System_flush();

    memset(txn_buffer, 0, sector_size);

    System_printf("da_load: Seeking to start of file...\n");
    System_flush();

    fr = f_lseek(&g_logFile, 0);
    if (fr != FR_OK) {
        System_printf("da_load: f_lseek to 0 failed, error %d\n", fr);
        System_flush();
        f_close(&g_logFile);
        return DISK_FAILED_WRITE;
    }

    System_sprintf(txn_buffer, "SESSION:%lu:0:0", current_session_id);

    System_printf("da_load: Writing metadata sector...\n");
    System_flush();

    fr = f_write(&g_logFile, txn_buffer, sector_size, &bw);

    System_printf("da_load: Metadata write returned %d, wrote %u bytes\n", fr, bw);
    System_flush();

    if (fr != FR_OK || bw != sector_size) {
        System_printf("da_load: Metadata write failed, error %d, bytes written %u\n", fr, bw);
        System_flush();
        f_close(&g_logFile);
        return DISK_FAILED_WRITE;
    }

    System_printf("da_load: Calling f_sync...\n");
    System_flush();

    fr = f_sync(&g_logFile);

    System_printf("da_load: f_sync returned %d\n", fr);
    System_flush();

    if (fr != FR_OK) {
        System_printf("da_load: f_sync failed, error %d\n", fr);
        System_flush();
        f_close(&g_logFile);
        return DISK_FAILED_WRITE;
    }

    System_printf("da_load: Metadata written successfully\n");
    System_flush();

    // Update session counter for next boot
    System_printf("da_load: Updating session counter to %lu...\n", current_session_id + 1);
    System_flush();

    uint32_t next_session_id = current_session_id + 1;
    int result = da_write_session_counter(next_session_id);
    if (result != DISK_SUCCESS) {
        System_printf("da_load: Warning - failed to update session counter\n");
        System_flush();
        // Don't fail the entire load operation, just warn
    }

    cur_sector_num = -1;
    dirty = 0;

    System_printf("da_load: Success - Session %lu ready\n", current_session_id);
    System_flush();

    UART_write(uart, "LD+\r\n", 5);  // Load: Success
    return DISK_SUCCESS;
}

int da_clear() {
    write_pos = 0;
    read_pos  = 0;
    memset(txn_buffer, 0, sector_size);
    return DISK_SUCCESS;
}

int da_close() {
    int rc = da_commit();
    if (rc != DISK_SUCCESS) {
        System_printf("da_close: da_commit failed\n");
        return DISK_FAILED_WRITE;
    }

    if (fs_mounted) {
        f_close(&g_logFile);
        f_mount(NULL, "0:", 1);
        fs_mounted = 0;
    }

    if (txn_buffer) {
        free(txn_buffer);
        txn_buffer = NULL;
    }

    System_printf("da_close: Success\n");
    return DISK_SUCCESS;
}


int da_commit() {
    if (!fs_mounted) {
        UART_write(uart, "CNM\r\n", 5);  // Commit: Not Mounted
        return DISK_NULL_HANDLE;
    }

    FRESULT fr;
    UINT    bw;

    if (dirty != 0 && cur_sector_num >= 0) {
        DWORD dataOffset = (DWORD)(cur_sector_num + 1) * sector_size;

        fr = f_lseek(&g_logFile, dataOffset);
        if (fr != FR_OK) {
            UART_write(uart, "CS1\r\n", 5);  // Commit: Seek1 failed
            return DISK_FAILED_WRITE;
        }

        fr = f_write(&g_logFile, txn_buffer, sector_size, &bw);
        if (fr != FR_OK || bw != sector_size) {
            UART_write(uart, "CW1\r\n", 5);  // Commit: Write1 failed
            return DISK_FAILED_WRITE;
        }

        dirty = 0;
    }

    cur_sector_num = -1;

    memset(txn_buffer, 0, sector_size);
    System_sprintf(txn_buffer, "SESSION:%lu:%ld:%ld", current_session_id, write_pos, read_pos);

    fr = f_lseek(&g_logFile, 0);
    if (fr != FR_OK) {
        UART_write(uart, "CS2\r\n", 5);  // Commit: Seek2 failed
        return DISK_FAILED_WRITE;
    }

    fr = f_write(&g_logFile, txn_buffer, sector_size, &bw);
    if (fr != FR_OK || bw != sector_size) {
        UART_write(uart, "CW2\r\n", 5);  // Commit: Write2 failed
        return DISK_FAILED_WRITE;
    }

    fr = f_sync(&g_logFile);
    if (fr != FR_OK) {
        UART_write(uart, "CSY\r\n", 5);  // Commit: Sync failed
        return DISK_FAILED_WRITE;
    }

    UART_write(uart, "C+\r\n", 4);  // Commit: Success
    return DISK_SUCCESS;
}

int da_get_sector(int sector) {
    if (!fs_mounted) return DISK_NULL_HANDLE;

    FRESULT fr;
    UINT    bw;

    sector = sector % num_sectors;

    if (dirty != 0 && cur_sector_num >= 0) {
        DWORD oldOffset = (DWORD)(cur_sector_num + 1) * sector_size;

        fr = f_lseek(&g_logFile, oldOffset);
        if (fr != FR_OK) return DISK_FAILED_WRITE;

        fr = f_write(&g_logFile, txn_buffer, sector_size, &bw);
        if (fr != FR_OK || bw != sector_size) return DISK_FAILED_WRITE;

        dirty = 0;
    }

    cur_sector_num = sector;
    return DISK_SUCCESS;
}

int da_get_read_sector(int sector) {
    if (!fs_mounted) return DISK_NULL_HANDLE;

    FRESULT fr;
    UINT    br, bw;

    sector = sector % num_sectors;

    if (dirty != 0 && cur_sector_num >= 0) {
        // Flush current dirty sector first
        DWORD oldOffset = (DWORD)(cur_sector_num + 1) * sector_size;

        fr = f_lseek(&g_logFile, oldOffset);
        if (fr != FR_OK) return DISK_FAILED_WRITE;

        fr = f_write(&g_logFile, txn_buffer, sector_size, &bw);
        if (fr != FR_OK || bw != sector_size) return DISK_FAILED_WRITE;

        dirty = 0;
    }

    // Load requested sector into txn_buffer
    DWORD offset = (DWORD)(sector + 1) * sector_size;
    fr = f_lseek(&g_logFile, offset);
    if (fr != FR_OK) return DISK_FAILED_READ;

    fr = f_read(&g_logFile, txn_buffer, sector_size, &br);
    if (fr != FR_OK || br != sector_size) return DISK_FAILED_READ;

    cur_sector_num = sector;

    return DISK_SUCCESS;
}

// --------------------------------------------------------
// Byte-wise read/write into circular buffer (unchanged logic)
// --------------------------------------------------------
int da_write(char* buffer, int size) {
    if (!fs_mounted) {
        UART_write(uart, "WNM\r\n", 5);  // Write: Not Mounted
        return DISK_NULL_HANDLE;
    }
    int result = 0;
    int totalWritten = 0;

    while (size > 0) {
        if (write_pos / sector_size != (unsigned long)cur_sector_num) {
            result = da_get_read_sector(write_pos / sector_size);
            if (result < 0) {
                UART_write(uart, "WGS\r\n", 5);  // Write: Get Sector failed
                write_pos -= totalWritten;
                return result;
            }
        }
        int nwrite = (size > (int)(sector_size - (write_pos % sector_size))) ?
                     (int)(sector_size - (write_pos % sector_size)) : size;

        memcpy(txn_buffer + (write_pos % sector_size),
               buffer + totalWritten,
               nwrite);

        dirty       = 1;
        write_pos   += nwrite;
        totalWritten += nwrite;
        size        -= nwrite;
    }
    UART_write(uart, "W+\r\n", 4);  // Write: Success
    return DISK_SUCCESS;
}

int da_read(char* buffer, int size) {
    if (!fs_mounted) return DISK_NULL_HANDLE;
    int result = 0;
    int totalRead = 0;

    while (size > 0) {
        if (read_pos / sector_size != (unsigned long)cur_sector_num) {
            result = da_get_read_sector(read_pos / sector_size);
            if (result < 0) {
                read_pos -= totalRead;
                return result;
            }
        }

        int nread = (size > (int)(sector_size - (read_pos % sector_size))) ?
                    (int)(sector_size - (read_pos % sector_size)) : size;

        memcpy(buffer + totalRead,
               txn_buffer + (read_pos % sector_size),
               nread);

        read_pos  += nread;
        totalRead += nread;
        size      -= nread;
    }

    return DISK_SUCCESS;
}

// --------------------------------------------------------
// Helpers / getters (unchanged API)
// --------------------------------------------------------
int da_get_data_size() {
    int size = (int)(write_pos - read_pos);
    if (size < 0) size = (int)(total_size - size);
    return size;
}

int da_get_cur_sector() {
    return cur_sector_num;
}

int da_get_read_pos() {
    return (int)read_pos;
}

int da_get_write_pos() {
    return (int)write_pos;
}

void da_set_write_pos(int position) {
    write_pos = (unsigned long)position;
}

int da_get_sector_size() {
    return (int)sector_size;
}

unsigned int da_get_num_sectors() {
    return num_sectors;
}

int da_soft_commit() {
    soft_read_pos = read_pos;
    return (int)read_pos;
}

int da_soft_rollback() {
    read_pos = soft_read_pos;
    return (int)read_pos;
}

char* da_get_transaction_buffer() {
    return txn_buffer;
}

// --------------------------------------------------------
// New helper functions for session management
// --------------------------------------------------------
uint32_t da_get_current_session_id() {
    return current_session_id;
}

const char* da_get_current_filename() {
    return current_log_filename;
}

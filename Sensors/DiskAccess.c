#include "DiskAccess.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "ff.h"
#include "diskio.h"
#include <ti/sysbios/knl/Task.h>
#include <ti/drivers/UART.h>
extern UART_Handle uart;
extern char* uartBuf;

/* -----------------------------------------------------------------------
 * FatFS state
 * --------------------------------------------------------------------- */
static FATFS g_sFatFs;
static FIL   g_logFile;
static int   fs_mounted = 0;

/* -----------------------------------------------------------------------
 * Geometry (set in da_initialize)
 * --------------------------------------------------------------------- */
static unsigned int  sector_size;
static unsigned int  num_sectors;
static unsigned long long total_size;
static uint32_t      da_sync_threshold;   /* bytes — 16 × sector_size    */

/* -----------------------------------------------------------------------
 * Circular-buffer state
 * --------------------------------------------------------------------- */
static unsigned long write_pos;
static unsigned long read_pos;
static unsigned long soft_read_pos;
static unsigned char dirty;
static char*         txn_buffer;          /* malloc'd, sector_size bytes  */
int32_t              cur_sector_num = -1;   /* -1 = no sector cached */

/* -----------------------------------------------------------------------
 * File / commit tracking
 * --------------------------------------------------------------------- */
static uint32_t current_file_number   = 0;
static char     current_log_filename[32];
static uint32_t bytes_since_sync      = 0;   /* resets on hard-commit       */
static uint32_t bytes_written_to_file = 0;   /* resets on rollover / load   */

/* ======================================================================
 * Internal helpers
 * ==================================================================== */

/*
 * da_find_next_file
 * Scans data1.txt, data2.txt, … starting one above current_file_number
 * until a missing slot is found.  Updates current_file_number and
 * current_log_filename on success.
 * Returns DISK_SUCCESS or DISK_FAILED_INIT.
 */
static int da_find_next_file(void)
{
    FILINFO    fno;
    FRESULT    fr;
    uint32_t   retries = 0;

    do {
        current_file_number++;
        sprintf(current_log_filename, "data%lu.txt",
                (unsigned long)current_file_number);

        if (++retries > 9999u) {
            UART_write(uart, "SCAN_LIMIT\r\n", 12);
            return DISK_FAILED_INIT;
        }

        fr = f_stat(current_log_filename, &fno);
        /* FR_OK  → file exists, keep scanning
         * FR_NO_FILE → free slot found           */
    } while (fr == FR_OK);

    if (fr != FR_NO_FILE) {
        /* Unexpected error (disk error, not-ready, etc.) */
        UART_write(uart, "SCAN_ERR\r\n", 10);
        return DISK_FAILED_INIT;
    }

    return DISK_SUCCESS;
}

/*
 * da_flush_metadata
 * Flushes any dirty data sector, then writes the SESSION metadata to
 * sector 0 and calls f_sync.  Always resets bytes_since_sync and
 * invalidates cur_sector_num (txn_buffer is overwritten with metadata).
 */
static int da_flush_metadata(void)
{
    FRESULT fr;
    UINT    bw;

    /* Flush dirty data sector first so txn_buffer can be reused */
    if (dirty != 0 && cur_sector_num >= 0) {
        DWORD dataOffset = (DWORD)(cur_sector_num + 1) * sector_size;

        fr = f_lseek(&g_logFile, dataOffset);
        if (fr != FR_OK) {
            UART_write(uart, "FM_S1\r\n", 7);
            return DISK_FAILED_WRITE;
        }
        fr = f_write(&g_logFile, txn_buffer, sector_size, &bw);
        if (fr != FR_OK || bw != sector_size) {
            UART_write(uart, "FM_W1\r\n", 7);
            return DISK_FAILED_WRITE;
        }
        dirty = 0;
    }

    /* Write metadata to sector 0 */
    memset(txn_buffer, 0, sector_size);
    sprintf(txn_buffer, "SESSION:%lu:%lu:%lu",
            (unsigned long)current_file_number,
            (unsigned long)write_pos,
            (unsigned long)read_pos);

    fr = f_lseek(&g_logFile, 0);
    if (fr != FR_OK) {
        UART_write(uart, "FM_S2\r\n", 7);
        return DISK_FAILED_WRITE;
    }
    fr = f_write(&g_logFile, txn_buffer, sector_size, &bw);
    if (fr != FR_OK || bw != sector_size) {
        UART_write(uart, "FM_W2\r\n", 7);
        return DISK_FAILED_WRITE;
    }
    fr = f_sync(&g_logFile);
    if (fr != FR_OK) {
        UART_write(uart, "FM_SY\r\n", 7);
        return DISK_FAILED_WRITE;
    }

    bytes_since_sync = 0;
    /* txn_buffer now holds metadata — invalidate data-sector cache */
    cur_sector_num = -1;

    return DISK_SUCCESS;
}

/*
 * da_open_and_preallocate
 * Opens current_log_filename with FA_CREATE_NEW, preallocates the full
 * file, writes the initial metadata sector, and calls f_sync.
 * Resets all write/commit state.
 */
static int da_open_and_preallocate(void)
{
    FRESULT fr;
    UINT    bw;
    int     retry_count = 0;

    /* Open loop: FA_CREATE_NEW is safe — it will never overwrite.
     * On FR_EXIST (FAT inconsistency despite f_stat saying absent),
     * skip forward to the next available slot.                       */
    while (1) {
        fr = f_open(&g_logFile, current_log_filename,
                    FA_READ | FA_WRITE | FA_CREATE_NEW);

        if (fr == FR_OK) {
            break;  /* success */
        }
        if (fr == FR_DENIED) {    /* FR_DENIED covers disk-full and directory-full */
            UART_write(uart, "NSP\r\n", 5);
            return DISK_NO_SPACE;
        }
        if (fr == FR_EXIST) {
            /* FAT inconsistency — advance to next slot */
            if (++retry_count > 10) {
                UART_write(uart, "OPN_RTY\r\n", 9);
                return DISK_FAILED_INIT;
            }
            int rc = da_find_next_file();
            if (rc != DISK_SUCCESS) return rc;
            continue;
        }
        /* Any other error */
        UART_write(uart, "OPN_ERR\r\n", 9);
        return DISK_FAILED_INIT;
    }

    UART_write(uart, "OPENED\r\n", 8);

    /* Preallocate full file so FAT cluster chain + directory entry
     * are committed to NAND at creation time.                       */
    if (num_sectors == 0) {
        num_sectors = 2047;
        total_size  = (unsigned long long)num_sectors * sector_size;
    }
    DWORD newSize = (DWORD)(num_sectors + 1) * sector_size;

    UART_write(uart, "SEEK\r\n", 6);
    fr = f_lseek(&g_logFile, newSize - 1);
    UART_write(uart, "SEEK_DONE\r\n", 11);
    if (fr != FR_OK) {
        f_close(&g_logFile);
        return DISK_FAILED_INIT;
    }

    BYTE zero = 0;
    fr = f_write(&g_logFile, &zero, 1, &bw);
    if (fr != FR_OK || bw != 1) {
        f_close(&g_logFile);
        return DISK_FAILED_INIT;
    }

    /* Write initial metadata to sector 0 and f_sync — this commits
     * the full file size + cluster chain to the FAT on the SD card. */
    fr = f_lseek(&g_logFile, 0);
    if (fr != FR_OK) {
        f_close(&g_logFile);
        return DISK_FAILED_WRITE;
    }
    memset(txn_buffer, 0, sector_size);
    sprintf(txn_buffer, "SESSION:%lu:0:0",
            (unsigned long)current_file_number);
    fr = f_write(&g_logFile, txn_buffer, sector_size, &bw);
    if (fr != FR_OK || bw != sector_size) {
        f_close(&g_logFile);
        return DISK_FAILED_WRITE;
    }
    fr = f_sync(&g_logFile);
    if (fr != FR_OK) {
        f_close(&g_logFile);
        return DISK_FAILED_WRITE;
    }

    /* Reset all state for the new file */
    write_pos             = 0;
    read_pos              = 0;
    cur_sector_num        = -1;
    dirty                 = 0;
    bytes_since_sync      = 0;
    bytes_written_to_file = 0;

    return DISK_SUCCESS;
}

/*
 * da_rollover
 * Hard-commits the current file, closes it, finds the next available
 * filename, and opens+preallocates it.  Called automatically from
 * da_commit() when DA_FILE_ROLLOVER_THRESHOLD is reached.
 */
static int da_rollover(void)
{
    UART_write(uart, "RO\r\n", 4);

    /* Seal current file with metadata + f_sync */
    int rc = da_flush_metadata();
    if (rc != DISK_SUCCESS) {
        /* Best-effort: close anyway */
        f_close(&g_logFile);
    } else {
        f_close(&g_logFile);
    }

    /* Find next available slot (skips any existing files) */
    rc = da_find_next_file();
    if (rc != DISK_SUCCESS) return rc;

    /* Open and preallocate new file */
    rc = da_open_and_preallocate();
    if (rc != DISK_SUCCESS) return rc;

    UART_write(uart, "RO+\r\n", 5);
    return DISK_SUCCESS;
}

/* ======================================================================
 * Public API
 * ==================================================================== */

int da_initialize(void)
{
    FRESULT fr;

    f_mount(NULL, "0:", 0);
    Task_sleep(200);

    fr = f_mount(&g_sFatFs, "0:", 0);
    if (fr != FR_OK) {
        fs_mounted = 0;
        return DISK_FAILED_INIT;
    }
    fs_mounted = 1;

    WORD  phys_sector_size = 0;
    DWORD sector_count     = 0;

    if (disk_ioctl(0, GET_SECTOR_SIZE, &phys_sector_size) == RES_OK
            && phys_sector_size > 0) {
        sector_size = (unsigned int)phys_sector_size;
    } else {
        sector_size = 512;
    }

    if (disk_ioctl(0, GET_SECTOR_COUNT, &sector_count) == RES_OK
            && sector_count > 1) {
        num_sectors = (unsigned int)(sector_count - 1);
    } else {
        num_sectors = 2047;
    }

    total_size        = (unsigned long long)num_sectors * sector_size;
    da_sync_threshold = (uint32_t)DA_SYNC_SECTORS * (uint32_t)sector_size;

    txn_buffer = (char *)malloc(sector_size * sizeof(char));
    if (!txn_buffer) {
        f_mount(NULL, "0:", 1);
        fs_mounted = 0;
        return DISK_FAILED_INIT;
    }

    soft_read_pos = 0;

    return DISK_SUCCESS;
}

int da_load(void)
{
    if (!fs_mounted) {
        UART_write(uart, "REMOUNT\r\n", 9);
        int result = da_initialize();
        if (result != DISK_SUCCESS) return result;
    }

    /* Scan for next available dataN.txt from slot 1 upward */
    current_file_number = 0;
    int rc = da_find_next_file();
    if (rc != DISK_SUCCESS) return rc;

    UART_write(uart, "FOPEN\r\n", 7);
    rc = da_open_and_preallocate();
    UART_write(uart, "FOPEN_DONE\r\n", 12);

    if (rc == DISK_SUCCESS) {
        System_printf("da_load: Success — %s ready\n", current_log_filename);
        System_flush();
        UART_write(uart, "LD+\r\n", 5);
    }
    return rc;
}

int da_close(void)
{
    /* Force full metadata sync regardless of threshold */
    da_flush_metadata();

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

int da_clear(void)
{
    write_pos = 0;
    read_pos  = 0;
    memset(txn_buffer, 0, sector_size);
    return DISK_SUCCESS;
}

/* -----------------------------------------------------------------------
 * da_commit
 *
 * SOFT PATH (every call):
 *   Flush dirty txn_buffer sector to SD.  cur_sector_num is intentionally
 *   kept so txn_buffer remains valid — eliminates the f_read re-load on
 *   the next da_write() into the same sector.
 *
 * HARD PATH (every DA_SYNC_SECTORS worth of data, or on rollover/close):
 *   Metadata rewrite + f_sync via da_flush_metadata().
 *   cur_sector_num is reset to -1 (txn_buffer is overwritten).
 *
 * ROLLOVER (when bytes_written_to_file >= DA_FILE_ROLLOVER_THRESHOLD):
 *   Hard-commit current file, seal it, open next dataN.txt.
 * --------------------------------------------------------------------- */
int da_commit(void)
{
    if (!fs_mounted) {
        UART_write(uart, "CNM\r\n", 5);
        return DISK_NULL_HANDLE;
    }

    FRESULT fr;
    UINT    bw;

    /* --- Soft commit: flush dirty sector -------------------------------- */
    if (dirty != 0 && cur_sector_num >= 0) {
        DWORD dataOffset = (DWORD)(cur_sector_num + 1) * sector_size;

        fr = f_lseek(&g_logFile, dataOffset);
        if (fr != FR_OK) {
            UART_write(uart, "CS1\r\n", 5);
            return DISK_FAILED_WRITE;
        }
        fr = f_write(&g_logFile, txn_buffer, sector_size, &bw);
        if (fr != FR_OK || bw != sector_size) {
            UART_write(uart, "CW1\r\n", 5);
            return DISK_FAILED_WRITE;
        }
        dirty = 0;
        bytes_since_sync += sector_size;
        /* cur_sector_num intentionally NOT reset — txn_buffer still valid */
    }

    /* --- File rollover check -------------------------------------------- */
    if (bytes_written_to_file >= DA_FILE_ROLLOVER_THRESHOLD) {
        return da_rollover();
    }

    /* --- Hard commit: metadata + f_sync when threshold reached ---------- */
    if (bytes_since_sync >= da_sync_threshold) {
        UART_write(uart, "HC\r\n", 4);
        return da_flush_metadata();
    }

    return DISK_SUCCESS;
}

/* -----------------------------------------------------------------------
 * da_get_sector
 * Flushes dirty sector then sets cur_sector_num to <sector> (write mode).
 * txn_buffer is NOT reloaded — caller must fill it.
 * --------------------------------------------------------------------- */
int da_get_sector(int sector)
{
    if (!fs_mounted) return DISK_NULL_HANDLE;

    FRESULT fr;
    UINT    bw;

    sector = (int)((unsigned int)sector % num_sectors);

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

/* -----------------------------------------------------------------------
 * da_get_read_sector
 * Flushes dirty sector, then reads <sector> into txn_buffer.
 * --------------------------------------------------------------------- */
int da_get_read_sector(int sector)
{
    if (!fs_mounted) return DISK_NULL_HANDLE;

    FRESULT fr;
    UINT    br, bw;

    sector = (int)((unsigned int)sector % num_sectors);

    if (dirty != 0 && cur_sector_num >= 0) {
        DWORD oldOffset = (DWORD)(cur_sector_num + 1) * sector_size;
        fr = f_lseek(&g_logFile, oldOffset);
        if (fr != FR_OK) return DISK_FAILED_WRITE;
        fr = f_write(&g_logFile, txn_buffer, sector_size, &bw);
        if (fr != FR_OK || bw != sector_size) return DISK_FAILED_WRITE;
        dirty = 0;
    }

    DWORD offset = (DWORD)(sector + 1) * sector_size;
    fr = f_lseek(&g_logFile, offset);
    if (fr != FR_OK) return DISK_FAILED_READ;
    fr = f_read(&g_logFile, txn_buffer, sector_size, &br);
    if (fr != FR_OK || br != sector_size) return DISK_FAILED_READ;

    cur_sector_num = sector;
    return DISK_SUCCESS;
}

/* -----------------------------------------------------------------------
 * da_write
 * Copies <size> bytes from <buffer> into txn_buffer, flushing sector
 * boundaries via da_get_read_sector().  Tracks bytes_written_to_file
 * for the rollover threshold (checked in da_commit).
 * --------------------------------------------------------------------- */
int da_write(char* buffer, int size)
{
    if (!fs_mounted) {
        UART_write(uart, "WNM\r\n", 5);
        return DISK_NULL_HANDLE;
    }

    int result      = 0;
    int totalWritten = 0;

    while (size > 0) {
        if ((int32_t)(write_pos / sector_size) != cur_sector_num) {
            result = da_get_read_sector((int)(write_pos / sector_size));
            if (result < 0) {
                UART_write(uart, "WGS\r\n", 5);
                write_pos -= totalWritten;
                return result;
            }
        }

        int nwrite = (size > (int)(sector_size - (write_pos % sector_size)))
                   ? (int)(sector_size - (write_pos % sector_size))
                   : size;

        memcpy(txn_buffer + (write_pos % sector_size),
               buffer + totalWritten,
               nwrite);

        dirty                  = 1;
        write_pos             += nwrite;
        totalWritten          += nwrite;
        size                  -= nwrite;
        bytes_written_to_file += (uint32_t)nwrite;
    }

    UART_write(uart, "W+\r\n", 4);
    return DISK_SUCCESS;
}

/* -----------------------------------------------------------------------
 * da_read
 * --------------------------------------------------------------------- */
int da_read(char* buffer, int size)
{
    if (!fs_mounted) return DISK_NULL_HANDLE;

    int result   = 0;
    int totalRead = 0;

    while (size > 0) {
        if ((int32_t)(read_pos / sector_size) != cur_sector_num) {
            result = da_get_read_sector((int)(read_pos / sector_size));
            if (result < 0) {
                read_pos -= totalRead;
                return result;
            }
        }

        int nread = (size > (int)(sector_size - (read_pos % sector_size)))
                  ? (int)(sector_size - (read_pos % sector_size))
                  : size;

        memcpy(buffer + totalRead,
               txn_buffer + (read_pos % sector_size),
               nread);

        read_pos  += nread;
        totalRead += nread;
        size      -= nread;
    }

    return DISK_SUCCESS;
}

/* -----------------------------------------------------------------------
 * Getters / helpers
 * --------------------------------------------------------------------- */
int da_get_data_size(void)
{
    int size = (int)(write_pos - read_pos);
    if (size < 0) size = (int)(total_size - size);
    return size;
}

int da_get_cur_sector(void)    { return cur_sector_num; }
int da_get_read_pos(void)      { return (int)read_pos;  }
int da_get_write_pos(void)     { return (int)write_pos; }
int da_get_sector_size(void)   { return (int)sector_size; }

unsigned int da_get_num_sectors(void) { return num_sectors; }

void da_set_write_pos(int position)
{
    write_pos = (unsigned long)position;
}

int da_soft_commit(void)
{
    soft_read_pos = read_pos;
    return (int)read_pos;
}

int da_soft_rollback(void)
{
    read_pos = soft_read_pos;
    return (int)read_pos;
}

char* da_get_transaction_buffer(void) { return txn_buffer; }

uint32_t da_get_current_file_number(void) { return current_file_number; }

const char* da_get_current_filename(void) { return current_log_filename; }

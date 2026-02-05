#include "DiskAccess.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "ff.h"
#include "diskio.h"

static FATFS g_sFatFs;
static FIL   g_logFile;
static int   fs_mounted = 0;

static char  g_logFileName[13];  // "logNNN.bin" + null


static unsigned long write_pos;
static unsigned long read_pos;
static unsigned int  sector_size;
static unsigned int  num_sectors;
static unsigned char dirty;
static unsigned long long total_size;
static char* txn_buffer;

static unsigned long soft_read_pos;

uint32_t cur_sector_num = 0U;

// Build filename: "log1.bin", "log2.bin", ... "log999.bin"
static void build_filename(int n) {
    g_logFileName[0] = 'l';
    g_logFileName[1] = 'o';
    g_logFileName[2] = 'g';
    int pos = 3;
    if (n >= 100) {
        g_logFileName[pos++] = '0' + (n / 100);
        n %= 100;
        g_logFileName[pos++] = '0' + (n / 10);
        g_logFileName[pos++] = '0' + (n % 10);
    } else if (n >= 10) {
        g_logFileName[pos++] = '0' + (n / 10);
        g_logFileName[pos++] = '0' + (n % 10);
    } else {
        g_logFileName[pos++] = '0' + n;
    }
    g_logFileName[pos++] = '.';
    g_logFileName[pos++] = 'b';
    g_logFileName[pos++] = 'i';
    g_logFileName[pos++] = 'n';
    g_logFileName[pos] = '\0';
}

int da_initialize() {
    FRESULT fr;

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

int da_load() {
    if (!fs_mounted) return DISK_FAILED_INIT;

    FRESULT fr;
    UINT    br;
    int     n;

    // Find next available log number by trying to create each file
    // FA_CREATE_NEW fails if file already exists
    for (n = 1; n <= 999; n++) {
        build_filename(n);
        fr = f_open(&g_logFile, g_logFileName, FA_READ | FA_WRITE | FA_CREATE_NEW);
        if (fr == FR_OK) {
            // Successfully created new file - keep it open and use it
            break;
        }
        if (fr != FR_EXIST) {
            // Some error other than "file exists" - try FA_OPEN_ALWAYS as fallback
            fr = f_open(&g_logFile, g_logFileName, FA_READ | FA_WRITE | FA_OPEN_ALWAYS);
            if (fr == FR_OK) {
                break;
            }
        }
        // FR_EXIST means file exists, try next number
    }

    if (fr != FR_OK) {
        return DISK_FAILED_INIT;
    }

    // Initialize the new file
    if (num_sectors == 0) {
        num_sectors = 2047;
        total_size  = (unsigned long long)num_sectors * sector_size;
    }

    DWORD newSize = (DWORD)(num_sectors + 1) * sector_size;

    fr = f_lseek(&g_logFile, newSize - 1);
    if (fr != FR_OK) return DISK_FAILED_INIT;

    BYTE zero = 0;
    fr = f_write(&g_logFile, &zero, 1, &br);
    if (fr != FR_OK || br != 1) return DISK_FAILED_INIT;

    write_pos = 0;
    read_pos  = 0;

    memset(txn_buffer, 0, sector_size);
    f_lseek(&g_logFile, 0);
    System_sprintf(txn_buffer, "%ld:%ld", write_pos, read_pos);
    fr = f_write(&g_logFile, txn_buffer, sector_size, &br);
    if (fr != FR_OK || br != sector_size) return DISK_FAILED_WRITE;

    f_sync(&g_logFile);

    cur_sector_num = -1;
    dirty = 0;

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
    if (rc != DISK_SUCCESS) return DISK_FAILED_WRITE;

    if (fs_mounted) {
        f_close(&g_logFile);
        f_mount(NULL, "0:", 1);
        fs_mounted = 0;
    }

    if (txn_buffer) {
        free(txn_buffer);
        txn_buffer = NULL;
    }

    return DISK_SUCCESS;
}


int da_commit() {
    if (!fs_mounted) return DISK_NULL_HANDLE;

    FRESULT fr;
    UINT    bw;

    if (dirty != 0 && cur_sector_num >= 0) {
        DWORD dataOffset = (DWORD)(cur_sector_num + 1) * sector_size;

        fr = f_lseek(&g_logFile, dataOffset);
        if (fr != FR_OK) return DISK_FAILED_WRITE;

        fr = f_write(&g_logFile, txn_buffer, sector_size, &bw);
        if (fr != FR_OK || bw != sector_size) return DISK_FAILED_WRITE;

        dirty = 0;
    }

    cur_sector_num = -1;

    memset(txn_buffer, 0, sector_size);
    System_sprintf(txn_buffer, "%ld:%ld", write_pos, read_pos);

    fr = f_lseek(&g_logFile, 0);
    if (fr != FR_OK) return DISK_FAILED_WRITE;

    fr = f_write(&g_logFile, txn_buffer, sector_size, &bw);
    if (fr != FR_OK || bw != sector_size) return DISK_FAILED_WRITE;

    fr = f_sync(&g_logFile);
    if (fr != FR_OK) return DISK_FAILED_WRITE;

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
    if (!fs_mounted) return DISK_NULL_HANDLE;
    int result = 0;
    int totalWritten = 0;

    while (size > 0) {
        if (write_pos / sector_size != (unsigned long)cur_sector_num) {
            result = da_get_read_sector(write_pos / sector_size);
            if (result < 0) {
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
    if (size < 0) size = (int)(total_size - size);  // same logic as original
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

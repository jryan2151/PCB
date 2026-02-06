#include "DiskAccess.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "ff.h"
#include "diskio.h"

static FATFS g_sFatFs;
static FIL   g_logFile;
static int   fs_mounted = 0;

static char  g_logFileName[13];  // "logNNN.csv" + null

static unsigned long write_pos;
static unsigned long read_pos;
static unsigned long soft_read_pos;

// Debug info
static int g_lastError = 0;
static int g_lastFileNum = 0;

const char* da_get_debug_msg() {
    return "";
}

int da_get_last_error() {
    return g_lastError;
}

int da_get_last_file_num() {
    return g_lastFileNum;
}

// Build filename: "log1.csv", "log2.csv", ... "log999.csv"
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
    g_logFileName[pos++] = 'c';
    g_logFileName[pos++] = 's';
    g_logFileName[pos++] = 'v';
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

    return DISK_SUCCESS;
}

int da_load() {
    if (!fs_mounted) {
        g_lastError = -1;
        return DISK_FAILED_INIT;
    }

    FRESULT fr;
    int     n;

    // Find next available log number
    for (n = 1; n <= 999; n++) {
        build_filename(n);
        fr = f_open(&g_logFile, g_logFileName, FA_WRITE | FA_READ | FA_CREATE_NEW);
        g_lastFileNum = n;
        g_lastError = (int)fr;
        if (fr == FR_OK) {
            break;
        }
        if (fr != FR_EXIST) {
            fr = f_open(&g_logFile, g_logFileName, FA_WRITE | FA_READ | FA_OPEN_ALWAYS);
            g_lastError = (int)fr;
            if (fr == FR_OK) {
                break;
            }
        }
    }

    if (fr != FR_OK) {
        return DISK_FAILED_INIT;
    }

    // Seek to end for appending
    f_lseek(&g_logFile, f_size(&g_logFile));
    write_pos = f_tell(&g_logFile);
    read_pos  = 0;
    soft_read_pos = 0;

    return DISK_SUCCESS;
}

int da_clear() {
    read_pos = 0;
    return DISK_SUCCESS;
}

int da_close() {
    if (fs_mounted) {
        f_sync(&g_logFile);
        f_close(&g_logFile);
        f_mount(NULL, "0:", 1);
        fs_mounted = 0;
    }

    return DISK_SUCCESS;
}

int da_commit() {
    if (!fs_mounted) return DISK_NULL_HANDLE;

    FRESULT fr = f_sync(&g_logFile);
    return (fr == FR_OK) ? DISK_SUCCESS : DISK_FAILED_WRITE;
}

int da_append(const char* buffer, int size) {
    if (!fs_mounted) return DISK_NULL_HANDLE;

    FRESULT fr;
    UINT    bw;

    fr = f_lseek(&g_logFile, write_pos);
    if (fr != FR_OK) return DISK_FAILED_WRITE;

    fr = f_write(&g_logFile, buffer, size, &bw);
    if (fr != FR_OK || (int)bw != size) return DISK_FAILED_WRITE;

    write_pos += bw;

    fr = f_sync(&g_logFile);
    if (fr != FR_OK) return DISK_FAILED_WRITE;

    return DISK_SUCCESS;
}

int da_read(char* buffer, int size) {
    if (!fs_mounted) return DISK_NULL_HANDLE;

    FRESULT fr;
    UINT    br;

    fr = f_lseek(&g_logFile, read_pos);
    if (fr != FR_OK) return DISK_FAILED_READ;

    fr = f_read(&g_logFile, buffer, size, &br);
    if (fr != FR_OK || (int)br != size) return DISK_FAILED_READ;

    read_pos += br;

    return DISK_SUCCESS;
}

// --------------------------------------------------------
// Helpers / getters
// --------------------------------------------------------
int da_get_data_size() {
    return (int)(write_pos - read_pos);
}

int da_get_read_pos() {
    return (int)read_pos;
}

int da_get_write_pos() {
    return (int)write_pos;
}

void da_set_write_pos(int position) {
    // No-op: writes are append-only now
}

int da_get_sector_size() {
    return 512;
}

unsigned int da_get_num_sectors() {
    return 0;
}

int da_soft_commit() {
    soft_read_pos = read_pos;
    return (int)read_pos;
}

int da_soft_rollback() {
    read_pos = soft_read_pos;
    return (int)read_pos;
}

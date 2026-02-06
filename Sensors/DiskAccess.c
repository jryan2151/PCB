#include "DiskAccess.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

#include <ti/drivers/SDFatFS.h>
#include <third_party/fatfs/ff.h>
#include <ti/drivers/UART.h>

static SDFatFS_Handle sdfatfsHandle = NULL;
static FIL   g_logFile;
static int   fs_mounted = 0;

static char  g_logFileName[13];  // "logNNN.csv" + null
static char  g_logFilePath[16];  // "0:logNNN.csv" + null

static unsigned long write_pos;
static unsigned long read_pos;
static unsigned long soft_read_pos;

// Debug info
static int g_lastError = 0;
static int g_lastFileNum = 0;
static char g_debugMsg[160];
static UART_Handle g_daUart = NULL;
static char g_dbg[128];

void da_set_uart(UART_Handle h)
{
    g_daUart = h;
}

static const char* fresult_str(FRESULT fr)
{
    switch (fr) {
    case FR_OK:                  return "OK";
    case FR_DISK_ERR:            return "DISK_ERR";
    case FR_INT_ERR:             return "INT_ERR";
    case FR_NOT_READY:           return "NOT_READY";
    case FR_NO_FILE:             return "NO_FILE";
    case FR_NO_PATH:             return "NO_PATH";
    case FR_INVALID_NAME:        return "INVALID_NAME";
    case FR_DENIED:              return "DENIED";
    case FR_EXIST:               return "EXIST";
    case FR_INVALID_OBJECT:      return "INVALID_OBJECT";
    case FR_WRITE_PROTECTED:     return "WRITE_PROTECTED";
    case FR_INVALID_DRIVE:       return "INVALID_DRIVE";
    case FR_NOT_ENABLED:         return "NOT_ENABLED";
    case FR_NO_FILESYSTEM:       return "NO_FILESYSTEM";
    default:                     return "UNKNOWN";
    }
}

static void da_uart_log(const char *fmt, ...)
{
    if (!g_daUart) return;

    va_list ap;
    va_start(ap, fmt);
    int n = vsnprintf(g_dbg, sizeof(g_dbg), fmt, ap);
    va_end(ap);

    if (n < 0) return;
    if (n > (int)sizeof(g_dbg)) n = sizeof(g_dbg);

    UART_write(g_daUart, g_dbg, n);
}

static void set_dbg(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(g_debugMsg, sizeof(g_debugMsg), fmt, ap);
    va_end(ap);
}

int da_is_mounted(void)
{
    return fs_mounted;
}

const char* da_get_debug_msg(void)
{
    return g_debugMsg;
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

static const char* build_filepath(void)
{
    g_logFilePath[0] = '0';
    g_logFilePath[1] = ':';
    strncpy(&g_logFilePath[2], g_logFileName, sizeof(g_logFilePath) - 3);
    g_logFilePath[sizeof(g_logFilePath) - 1] = '\0';
    return g_logFilePath;
}

int da_initialize(void)
{
    set_dbg("da_initialize: start");

    SDFatFS_init();
    set_dbg("da_initialize: after SDFatFS_init");

    sdfatfsHandle = SDFatFS_open(0, 0);

    if (sdfatfsHandle == NULL) {
        fs_mounted = 0;
        g_lastError = DISK_NULL_HANDLE;
        set_dbg("da_initialize: SDFatFS_open FAILED handle=NULL");
        return DISK_FAILED_INIT;
    }

    fs_mounted = 1;
    g_lastError = 0;
    set_dbg("da_initialize: OK handle!=NULL mounted=1");

    return DISK_SUCCESS;
}

int da_load(void)
{

    set_dbg("da_load: enter");

    if (!fs_mounted) {
        g_lastError = -1;
        set_dbg("da_load: NOT MOUNTED");
        da_uart_log("da_load: NOT MOUNTED\r\n");
        return DISK_FAILED_INIT;
    }

    FRESULT fr = FR_OK;
    int n = 0;

    for (n = 1; n <= 999; n++) {
        const char *logFilePath;

        build_filename(n);
        logFilePath = build_filepath();

        set_dbg("da_load: trying CREATE_NEW %s", logFilePath);
        da_uart_log("da_load: f_open CREATE_NEW %s\r\n", logFilePath);
        fr = f_open(&g_logFile, logFilePath, FA_WRITE | FA_READ | FA_CREATE_NEW);
        da_uart_log("da_load: f_open CREATE_NEW returned fr=%d (%s)\r\n", (int)fr, fresult_str(fr));

        g_lastFileNum = n;
        g_lastError   = (int)fr;

        if (fr == FR_OK) {
            set_dbg("da_load: created %s", g_logFileName);
            da_uart_log("da_load: created %s\r\n", g_logFileName);
            break;
        }

        if (fr == FR_EXIST) {
            continue; // try next number
        }

        set_dbg("da_load: CREATE_NEW %s failed fr=%d(%s), trying OPEN_ALWAYS",
                logFilePath, (int)fr, fresult_str(fr));
        da_uart_log("da_load: f_open OPEN_ALWAYS %s\r\n", logFilePath);
        fr = f_open(&g_logFile, logFilePath, FA_WRITE | FA_READ | FA_OPEN_ALWAYS);
        da_uart_log("da_load: f_open OPEN_ALWAYS returned fr=%d (%s)\r\n", (int)fr, fresult_str(fr));

        g_lastError = (int)fr;

        if (fr == FR_OK) {
            set_dbg("da_load: opened %s via OPEN_ALWAYS", g_logFileName);
            da_uart_log("da_load: opened %s\r\n", g_logFileName);
            break;
        }
    }

    if (fr != FR_OK) {
        set_dbg("da_load: FAIL fr=%d(%s) file=%s n=%d",
                (int)fr, fresult_str(fr), g_logFileName, n);
        da_uart_log("da_load: FAIL final fr=%d (%s) last=%s\r\n",
                    (int)fr, fresult_str(fr), g_logFileName);
        return DISK_FAILED_INIT;
    }

    da_uart_log("da_load: seeking end\r\n");
    fr = f_lseek(&g_logFile, f_size(&g_logFile));
    da_uart_log("da_load: lseek returned fr=%d\r\n", (int)fr);

    if (fr != FR_OK) {
        g_lastError = (int)fr;
        set_dbg("da_load: lseek FAIL fr=%d(%s) file=%s",
                (int)fr, fresult_str(fr), g_logFileName);
        da_uart_log("da_load: lseek FAIL fr=%d (%s)\r\n", (int)fr, fresult_str(fr));
        return DISK_FAILED_INIT;
    }

    write_pos = f_tell(&g_logFile);
    read_pos  = 0;
    soft_read_pos = 0;

    set_dbg("da_load: OK file=%s write_pos=%lu", g_logFileName, (unsigned long)write_pos);
    da_uart_log("da_load: OK write_pos=%lu\r\n", (unsigned long)write_pos);
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
        SDFatFS_close(sdfatfsHandle);
        sdfatfsHandle = NULL;
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

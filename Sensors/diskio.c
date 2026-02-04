#include <stdint.h>
#include <stdbool.h>
#include "diskio.h"
#include <ti/drivers/SD.h>
#include <ti/drivers/UART.h>
#include "Board.h"
#include <string.h>

extern UART_Handle uart;
extern char* uartBuf;

/* One logical drive: pdrv = 0 */
static SD_Handle gSd = NULL;
static DSTATUS   gStat = STA_NOINIT;
static int       gInitFailed = 0;  // Flag to prevent repeated init attempts


DSTATUS disk_status(BYTE pdrv)
{
    if (pdrv != 0) return STA_NOINIT;
    return gStat;
}

DSTATUS disk_initialize(BYTE pdrv)
{
    UART_write(uart, "DI\r\n", 4);  // Disk Initialize starting
    if (pdrv != 0) return STA_NOINIT;

    // If we already failed init, don't try again (prevents hang on repeated attempts)
    if (gInitFailed) {
        UART_write(uart, "DI:SKIP\r\n", 9);  // Skipping - already failed
        return STA_NOINIT;
    }

    // If already initialized, just return success
    if (gSd != NULL && !(gStat & STA_NOINIT)) {
        UART_write(uart, "DI:OK\r\n", 7);  // Already initialized
        return gStat;
    }

    // Only open if not already open
    if (gSd == NULL) {
        UART_write(uart, "DI:OPEN\r\n", 9);  // Opening SD
        gSd = SD_open(Board_SD0, NULL);
        if (gSd == NULL) {
            UART_write(uart, "DI:FAIL1\r\n", 10);  // SD_open failed
            gInitFailed = 1;
            gStat = STA_NOINIT;
            return gStat;
        }
        UART_write(uart, "DI:OPENED\r\n", 11);  // SD opened
    }

    // Only initialize if status says we need to
    if (gStat & STA_NOINIT) {
        UART_write(uart, "DI:INIT\r\n", 9);  // SD_initialize starting

        // Try SD_initialize - just once, no retries (retries cause state corruption)
        UART_write(uart, "DI:TRY\r\n", 8);
        int initResult = SD_initialize(gSd);
        UART_write(uart, "DI:RET\r\n", 8);

        if (initResult != SD_STATUS_SUCCESS) {
            UART_write(uart, "DI:FAIL2\r\n", 10);  // SD_initialize failed
            SD_close(gSd);
            gSd = NULL;
            gInitFailed = 1;  // Mark as failed to prevent repeated attempts
            gStat = STA_NOINIT;
            return gStat;
        }
        UART_write(uart, "DI:INIT+\r\n", 10);  // SD_initialize success
    }

    gStat = 0;
    UART_write(uart, "DI+\r\n", 5);  // Disk Initialize complete
    return gStat;
}

DRESULT disk_read(BYTE pdrv, BYTE *buff, LBA_t sector, UINT count)
{
    UART_write(uart, "DR\r\n", 4);  // Disk Read starting
    if (pdrv != 0 || (gStat & STA_NOINIT) || gSd == NULL) return RES_NOTRDY;
    if (count == 0) return RES_PARERR;

    int result = SD_read(gSd, buff, (int_fast32_t)sector, (uint_fast32_t)count);
    UART_write(uart, "DR+\r\n", 5);  // Disk Read done
    return (result == SD_STATUS_SUCCESS) ? RES_OK : RES_ERROR;
}

#if FF_FS_READONLY == 0
DRESULT disk_write(BYTE pdrv, const BYTE *buff, LBA_t sector, UINT count)
{
    UART_write(uart, "DW\r\n", 4);  // Disk Write starting
    if (pdrv != 0 || (gStat & STA_NOINIT) || gSd == NULL) return RES_NOTRDY;
    if (count == 0) return RES_PARERR;

    int result = SD_write(gSd, buff, (int_fast32_t)sector, (uint_fast32_t)count);
    UART_write(uart, "DW+\r\n", 5);  // Disk Write done
    return (result == SD_STATUS_SUCCESS) ? RES_OK : RES_ERROR;
}
#endif

DRESULT disk_ioctl(BYTE pdrv, BYTE cmd, void *buff)
{
    if (pdrv != 0) return RES_PARERR;
    if (gSd == NULL || (gStat & STA_NOINIT)) return RES_NOTRDY;

    switch (cmd) {
    case CTRL_SYNC:
        return RES_OK;

    case GET_SECTOR_COUNT: {
        uint_fast32_t n = SD_getNumSectors(gSd);
        if (n == 0) return RES_ERROR;
        *(LBA_t *)buff = (LBA_t)n;
        return RES_OK;
    }

    case GET_SECTOR_SIZE: {
        uint_fast32_t sz = SD_getSectorSize(gSd);
        if (sz == 0) return RES_ERROR;
        *(WORD *)buff = (WORD)sz;
        return RES_OK;
    }

    case GET_BLOCK_SIZE:
        *(DWORD *)buff = 1;
        return RES_OK;

    default:
        return RES_PARERR;
    }
}

DWORD get_fattime(void)
{
    DWORD year = (2026 - 1980);
    DWORD mon  = 1;
    DWORD day  = 1;
    return (year << 25) | (mon << 21) | (day << 16);
}

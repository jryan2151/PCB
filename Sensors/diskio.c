#include <stdint.h>
#include <stdbool.h>

#include "diskio.h"
#include <ti/drivers/SD.h>
#include "Board.h"

/* One logical drive: pdrv = 0 */
static SD_Handle gSd = NULL;
static DSTATUS   gStat = STA_NOINIT;

DSTATUS disk_status(BYTE pdrv)
{
    if (pdrv != 0) return STA_NOINIT;
    return gStat;
}

DSTATUS disk_initialize(BYTE pdrv)
{
    if (pdrv != 0) return STA_NOINIT;

    SD_init();

    /* NOTE: If Board_SD0 doesn't exist, replace with CONFIG_SD0 */
    gSd = SD_open(Board_SD0, NULL);
    if (gSd == NULL) {
        gStat = STA_NOINIT;
        return gStat;
    }

    if (SD_initialize(gSd) != SD_STATUS_SUCCESS) {
        SD_close(gSd);
        gSd = NULL;
        gStat = STA_NOINIT;
        return gStat;
    }

    gStat &= (DSTATUS)~STA_NOINIT;
    return gStat;
}

DRESULT disk_read(BYTE pdrv, BYTE *buff, LBA_t sector, UINT count)
{
    if (pdrv != 0 || (gStat & STA_NOINIT) || gSd == NULL) return RES_NOTRDY;
    if (count == 0) return RES_PARERR;

    return (SD_read(gSd, buff, (int_fast32_t)sector, (uint_fast32_t)count) == SD_STATUS_SUCCESS)
           ? RES_OK : RES_ERROR;
}

#if FF_FS_READONLY == 0
DRESULT disk_write(BYTE pdrv, const BYTE *buff, LBA_t sector, UINT count)
{
    if (pdrv != 0 || (gStat & STA_NOINIT) || gSd == NULL) return RES_NOTRDY;
    if (count == 0) return RES_PARERR;

    return (SD_write(gSd, buff, (int_fast32_t)sector, (uint_fast32_t)count) == SD_STATUS_SUCCESS)
           ? RES_OK : RES_ERROR;
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

/* Needed unless you set FF_FS_NORTC = 1 in ffconf.h */
DWORD get_fattime(void)
{
    /* 2026-01-01 00:00:00 */
    DWORD year = (2026 - 1980);
    DWORD mon  = 1;
    DWORD day  = 1;
    return (year << 25) | (mon << 21) | (day << 16);
}

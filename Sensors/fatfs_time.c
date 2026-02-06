#include <stdint.h>

/*
 * FAT timestamp format (32-bit):
 * bits31:25 = year since 1980 (0..127)
 * bits24:21 = month (1..12)
 * bits20:16 = day (1..31)
 * bits15:11 = hour (0..23)
 * bits10:5  = minute (0..59)
 * bits4:0   = seconds/2 (0..29)
 */
int32_t fatfs_getFatTime(void)
{
    uint32_t year  = 2026 - 1980;
    uint32_t month = 2;
    uint32_t day   = 5;
    uint32_t hour  = 12;
    uint32_t min   = 0;
    uint32_t sec2  = 0;

    uint32_t t = (year  << 25) |
                 (month << 21) |
                 (day   << 16) |
                 (hour  << 11) |
                 (min   << 5)  |
                 (sec2);

    return (int32_t)t;
}

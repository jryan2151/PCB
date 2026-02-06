/*
 *  SDFatFS board configuration for CC2640R2_LAUNCHXL.
 *
 *  The SDFatFS driver wraps the existing SD driver (Board_SD0)
 *  and provides FatFS filesystem mounting. SDFatFS_open(0, 0)
 *  internally calls SD_open(0, NULL) which maps to Board_SD0.
 */

#include <ti/drivers/SDFatFS.h>

SDFatFS_Object sdfatfsObjects[1];

const SDFatFS_Config SDFatFS_config[1] = {
    {
        .object = &sdfatfsObjects[0]
    },
};

const uint_least8_t SDFatFS_count = 1;

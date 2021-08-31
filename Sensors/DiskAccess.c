#include "DiskAccess.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct SDCard card;

// read when there's nothing left to read and write when out of space errors
// change function names to match sdraw

int da_initialize() {
    SD_init();
    return DISK_SUCCESS;
}

int da_load() {
    int delimiter = 0;
    //int result = 0;

    card.sdHandle = SD_open(Board_SD0, NULL);
    if (card.sdHandle == NULL) return DISK_NULL_HANDLE;


    int_fast8_t status = SD_initialize(card.sdHandle);
    if (status != SD_STATUS_SUCCESS) return DISK_FAILED_INIT;

    card.sector_size = SD_getSectorSize(card.sdHandle);
    card.num_sectors = SD_getNumSectors(card.sdHandle) - 1;
    card.txn_buffer = (char *) malloc(card.sector_size * sizeof(char));
    card.total_size = 0;//card.sector_size * card.num_sectors; // potential for integer overflow... oops

    status = SD_read(card.sdHandle, card.txn_buffer, 0, 1);
    if (status != SD_STATUS_SUCCESS) {
        return DISK_FAILED_READ;
    }


    int i = 0;
    while (i < card.sector_size) {
        if (card.txn_buffer[i] == ':') {
            delimiter = i;
            break;
        }
        ++i;
    }

    if (delimiter) {
        card.write_pos = atoi(card.txn_buffer);
        card.read_pos = atoi(card.txn_buffer + delimiter + 1);
    }
    else {
        card.write_pos = 0;
        card.read_pos = 0;
    }

    card.cur_sector_num = -1;
    card.dirty = 0;

    return DISK_SUCCESS;
}

int da_clear() {
    card.write_pos = 0;
    card.read_pos = 0;
    memset(card.txn_buffer, 0, card.sector_size);
    return DISK_SUCCESS;
}

int da_close() {
    int_fast8_t result;

    if (card.dirty) {
        result = SD_write(card.sdHandle, card.txn_buffer, card.cur_sector_num, 1);
        if (result != SD_STATUS_SUCCESS) return -1;
    }
    memset(card.txn_buffer, 0, card.sector_size);
    System_sprintf(card.txn_buffer, "%d:%d", card.write_pos, card.read_pos);
    result = SD_write(card.sdHandle, card.txn_buffer, 0, 1);
    if (result != SD_STATUS_SUCCESS) return DISK_FAILED_WRITE;

    free(card.txn_buffer);
    SD_close(card.sdHandle);

    return DISK_SUCCESS;
}

int da_get_sector(int sector) {
    int_fast8_t result;
    if (card.sdHandle == NULL) return DISK_NULL_HANDLE;
    sector = sector % card.num_sectors;

    if (card.dirty != 0) {
        result = SD_write(card.sdHandle, card.txn_buffer, sector, 1);
        if (result != SD_STATUS_SUCCESS) return DISK_FAILED_WRITE;
    }

    /*System_sprintf(card.txn_buffer, "%d:%d", card.write_pos, card.read_pos);
    result = SD_write(card.sdHandle, card.txn_buffer, 0, 1);
    if (result != SD_STATUS_SUCCESS) return DISK_FAILED_WRITE;*/

    result = SD_read(card.sdHandle, card.txn_buffer, sector + 1, 1);
    if (result != SD_STATUS_SUCCESS) return DISK_FAILED_READ;
    card.cur_sector_num = sector;

    return DISK_SUCCESS;
}

int da_write(char* buffer, int size) {
    if (card.sdHandle == NULL) return DISK_NULL_HANDLE;
    int result = 0;
    //if (size > card.total_size - da_get_data_size()) return -1;
    int totalWritten = 0;
    while (size > 0) {
        if (card.write_pos / card.sector_size != card.cur_sector_num) {
            result = da_get_sector(card.write_pos / card.sector_size);
            if (result < 0) return result;
            //result = TXN_MISS;
        }
        int nwrite = (size > card.sector_size - (card.write_pos % card.sector_size)) ? card.sector_size - (card.write_pos % card.sector_size) : size;
        memcpy(card.txn_buffer + (card.write_pos % card.sector_size), buffer + totalWritten, nwrite);

        card.dirty = 1;
        card.write_pos += nwrite;
        totalWritten += nwrite;
        size -= nwrite;
    }
    return DISK_SUCCESS;
    //return result;
}

int da_read(char* buffer, int size) {
    if (card.sdHandle == NULL) return DISK_NULL_HANDLE;
    int result = 0;
    //if (size > da_get_data_size()) return -1;
    int totalRead = 0;
    while (size > 0) {
        if (card.read_pos / card.sector_size != card.cur_sector_num) {
            result = da_get_sector(card.read_pos / card.sector_size);
            if (result < 0) return result;
        }

        int nread = (size > card.sector_size - (card.read_pos % card.sector_size)) ? card.sector_size - (card.read_pos % card.sector_size) : size;
        memcpy(buffer + totalRead, card.txn_buffer + (card.read_pos % card.sector_size), nread);

        card.read_pos += nread;
        totalRead += nread;
        size -= nread;
    }

    return DISK_SUCCESS;
}

int da_get_data_size() {
    int size = card.write_pos - card.read_pos;
    if (size < 0) size = card.total_size - size;
    return size;
}

int da_get_read_pos() {
    return card.read_pos;
}

int da_get_write_pos() {
    return card.write_pos;
}

int da_get_sector_size() {
    return card.sector_size;
}

int da_get_num_sectors(){
    return card.num_sectors;
}

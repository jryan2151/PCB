/*
 * Serializer.c
 *
 *  Created on: Apr 16, 2022
 *      Author: jacek
 */

#include "Serializer.h"

static struct SensorData sensorData;
static uint8_t index = 0;

int serializer_isFull() {
    return index == 0;
}

void serializer_setTimestamp(unsigned short timestamp) {
    sensorData.timestamp = timestamp;
}

void serializer_addImpedance(float impedance) {
    sensorData.impedanceValues[index] = impedance;
    index = (index + 1) % NUM_SENSORS;
}

int serializer_serialize(char* buffer) {
    memcpy(buffer, &sensorData.timestamp, sizeof(uint16_t));
    memcpy(buffer + sizeof(uint16_t), sensorData.impedanceValues, sizeof(float) * NUM_SENSORS);
    return sizeof(uint16_t) + sizeof(float) * NUM_SENSORS;
}

int serializer_serializeReadable(char* buffer) {
    uint16_t offset = 0;
    offset += System_sprintf(buffer, "%u", sensorData.timestamp);

    for (uint8_t i = 0; i < NUM_SENSORS; i++) {
        uint16_t base = sensorData.impedanceValues[i];
        uint16_t decimal = sensorData.impedanceValues[i] * 100 - base * 100;

        offset += System_sprintf(buffer + offset, ",%u.%u", base, decimal);
    }

    offset += System_sprintf(buffer + offset, "\n\0");

    return offset;
}

void serializer_clear() {
    index = 0;
}


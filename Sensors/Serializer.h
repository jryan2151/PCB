/*
 * Serializer.h
 *
 *  Created on: Apr 16, 2022
 *      Author: jacek
 */

#ifndef SENSORS_SERIALIZER_H_
#define SENSORS_SERIALIZER_H_

#include <stdint.h>
#include <xdc/runtime/System.h>

struct SensorData {
    uint16_t timestamp;
    float impedanceValues[16];
};

int serializer_isFull();
void serializer_setTimestamp(uint16_t);
void serializer_addImpedance(float);
void serializer_serialize(char*);
void serializer_serializeReadable(char*);

#endif /* SENSORS_SERIALIZER_H_ */

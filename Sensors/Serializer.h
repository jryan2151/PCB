/*
 * Serializer.h
 *
 *  Created on: Apr 16, 2022
 *      Author: jacek
 */

#ifndef SENSORS_SERIALIZER_H_
#define SENSORS_SERIALIZER_H_

#define NUM_SENSORS 16

#include <stdint.h>
#include <xdc/runtime/System.h>

struct SensorData {
    unsigned short timestamp;
    float impedanceValues[NUM_SENSORS];
};

int serializer_isFull();
void serializer_setTimestamp(unsigned short);
void serializer_addImpedance(float);
int serializer_serialize(char*);
int serializer_serializeReadable(char*);
void serializer_clear();

#endif /* SENSORS_SERIALIZER_H_ */

/*
 * Created By : Jared Brinkman
 * Date: 7/22/2022
 *
 * ImpedanceCalc.h
 *
 */

#ifndef SENSORS_IMPEDANCECALC_H_
#define SENSORS_IMPEDANCECALC_H_

#include <stdint.h>

float ImpedanceCalc(uint16_t tapNumber, uint16_t adc, int tapsArray [255]);

#endif

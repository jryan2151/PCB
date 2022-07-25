/*
 * Created by Jared Brinkman
 * Date: 7/22/2022
 *
 * This file will change for every board that is calibrated.
 * Will hold 255 Impedance equations
 */

#include "ImpedanceCalc.h"

float ImpedanceCalc(uint16_t tapNumber, uint16_t adc, int tapsArray [255]) {
    float imp = 0;
    if (tapsArray[tapNumber] == tapsArray[1]){
        imp = fabs((-189.4 * adc + 518778)/(adc + -929.0));
    }
    else if (tapsArray[tapNumber] == tapsArray[2]){
        imp = fabs((-206.0 * adc + 764491)/(adc + -919.3));
    }
    else if (tapsArray[tapNumber] == tapsArray[3]){
        imp = fabs((-213.7 * adc + 1407631)/(adc + -918.7));
    }
    else if (tapsArray[tapNumber] == tapsArray[4]){
        imp = fabs((-221.1 * adc + 2427576)/(adc + -917.6));
    }
    else if (tapsArray[tapNumber] == tapsArray[5]){
        imp = fabs((-307.9 * adc + 4850328)/(adc + -916.3));
    }
    else if (tapsArray[tapNumber] == tapsArray[6]){
        imp = fabs((-66.6 * adc + 6980902)/(adc + -922.7));
    }
    return imp;
}

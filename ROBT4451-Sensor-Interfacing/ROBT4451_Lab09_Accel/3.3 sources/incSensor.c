/*
 * incSensor.c
 *
 *  Created on: May 16, 2021
 *      Author: a01160214
 */

#include "math.h"

#define PI 3.14159265359
#define WINDOW_SIZE 10 // number of data to average

#define COEFF1 0.0004884 // 2 * 1 / (2^12 - 1) => can be approximated as divide by 2^11
#define COEFF2 0.0002442 // 1 / (2^12 - 1) => can be approximated as divide by 2^12

double incResults[WINDOW_SIZE];
char index = 0;

double incAveResult;

char isAvailable = 0; // set when first 20 data is collected

// convert D to angle
double dout2Ang(int dout[2])
{
    // x, y acceleration to angle of inclination
    double ang = atan2(COEFF1 * dout[0] - 1, COEFF2 * dout[1]) * 180 / PI;

    // save it for averaging
    incResults[index++] = ang;

    if (index >= WINDOW_SIZE)
    {
        isAvailable = 1;
    }

    index %= WINDOW_SIZE;

    dout2AngAve();

    return ang;
}

void dout2AngAve()
{
    unsigned int i;
    double result = 0;

    if (isAvailable)
    {
        for(i = 0; i < WINDOW_SIZE; i ++)
        {
            result += incResults[i];
        }

        result /= WINDOW_SIZE;
    }
    else
    {
        for(i = 0; i < index; i ++)
        {
            result += incResults[i];
        }

        result /= index;
    }

    incAveResult = result;
}

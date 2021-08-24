/*
 * waveformGenerator.h
 *
 *  Created on: Apr 12, 2021
 *      Author: a01160214
 */

#ifndef WAVEFORMGENERATOR_H_
#define WAVEFORMGENERATOR_H_

void triangularWaveAllDac(void);
void triangularWaveDac(double amp, double freq, int nSamples);
void triWave(double freq, int nSamples);
void sinusoidWaveDac(double amp, double freq, int nSamples);


#endif /* WAVEFORMGENERATOR_H_ */

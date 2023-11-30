#ifndef SENSOR_HANDLER_H
#define SENSOR_HANDLER_H

#include "setupSensors.h"
#include "relayHandler.h"
#include "ntpHandler.h"

extern float brightnessMean;

void initGarden();
void printValues();
void brightnessMeanCalc();
void sensorHandler();

#endif
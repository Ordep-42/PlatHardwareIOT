#ifndef SENSOR_HANDLER_H
#define SENSOR_HANDLER_H

#include "setupSensors.h"
#include "relayHandler.h"
#include "ntphandler.h"

extern float brightnessMean;

void initGarden();
void printValues();
void sensorHandler();

#endif
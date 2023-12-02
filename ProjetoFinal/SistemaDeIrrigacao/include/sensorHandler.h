#ifndef SENSOR_HANDLER_H
#define SENSOR_HANDLER_H

#include <Arduino.h>
#include "setupSensors.h"
#include "relayHandler.h"
#include "ntpHandler.h"

extern float brightnessMean;

void initGarden();
void printValuesToSerial();
void brightnessMeanCalc();
void sensorHandler();

#endif
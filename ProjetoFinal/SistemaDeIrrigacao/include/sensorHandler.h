#ifndef SENSOR_HANDLER_H
#define SENSOR_HANDLER_H

#include <Arduino.h>
#include "setupSensors.h"
#include "relayHandler.h"

void initGarden();
void printValuesToSerial();
void brightnessMeanCalc();
void sensorHandler();

#endif

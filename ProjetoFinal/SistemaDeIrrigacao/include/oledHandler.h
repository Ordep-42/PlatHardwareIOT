#ifndef OLEDHANDLER_H
#define OLEDHANDLER_H

#include "setupOled.h"
#include "setupSensors.h"

extern unsigned long lastChange;
extern int displayState;

void printMoistureToOled();
void printBrightnessToOled();
void printTemperatureToOled();
void printHumidityToOled();
void updateOled();

#endif

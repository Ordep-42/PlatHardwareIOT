#ifndef OLEDHANDLER_H
#define OLEDHANDLER_H

#include "setupOled.h"
#include "ntpHandler.h"
#include "setupSensors.h"

#define SCREEN_TIME 3000

extern unsigned long lastChange;
extern int displayState;

void printTimeToOled(int x, int y, int size);
void printMoistureToOled();
void printBrightnessToOled();
void printTemperatureToOled();
void printHumidityToOled();
void updateOled();
void oledHandler();

#endif
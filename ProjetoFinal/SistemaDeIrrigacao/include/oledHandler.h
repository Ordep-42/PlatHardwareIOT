#ifndef OLEDHANDLER_H
#define OLEDHANDLER_H

#include "setupOled.h"
#include "ntpHandler.h"

void printTimeToOled(int x, int y, int size);
void printMoistureToOled(int x, int y, int size);
void printBrightnessToOled(int x, int y, int size);
void printTemperatureToOled(int x, int y, int size);
void printHumidityToOled(int x, int y, int size);
void printBombaStatusToOled(int x, int y, int size);
void oledHandler();

#endif
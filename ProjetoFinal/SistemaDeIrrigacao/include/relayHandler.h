#ifndef RELAYHANDLER_H
#define RELAYHANDLER_H

#include <Arduino.h>

#define BOMBAPIN 2

extern int bombaStatus;

void initRelay();
void turnOnBomba();
void turnOffBomba();

#endif
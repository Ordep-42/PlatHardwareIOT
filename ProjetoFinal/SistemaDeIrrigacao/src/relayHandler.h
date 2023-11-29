#ifndef RELAYHANDLER_H
#define RELAYHANDLER_H

#include <Arduino.h>

#define BOMBAPIN 2

void initRelay();
void turnOnBomba();
void turnOffBomba();

#endif
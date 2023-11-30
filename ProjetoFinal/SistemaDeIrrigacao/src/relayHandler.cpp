#include "relayHandler.h"

int bombaStatus = 0;

void initRelay() {
    pinMode(BOMBAPIN, OUTPUT);
}

void turnOnBomba() {
    digitalWrite(BOMBAPIN, HIGH);
    bombaStatus = 1;
}

void turnOffBomba() {
    digitalWrite(BOMBAPIN, LOW);
    bombaStatus = 0;
}

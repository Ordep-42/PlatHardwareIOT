#include "relayHandler.h"

void initRelay() {
    pinMode(BOMBAPIN, OUTPUT);
}

void turnOnBomba() {
    digitalWrite(BOMBAPIN, HIGH);
}

void turnOffBomba() {
    digitalWrite(BOMBAPIN, LOW);
}

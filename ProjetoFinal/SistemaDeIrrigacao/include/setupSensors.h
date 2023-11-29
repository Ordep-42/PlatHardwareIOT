#ifndef SETUPSENSORS_H
#define SETUPSENSORS_H
#include "config.h"

#define DHTPIN 32
#define DHTTYPE DHT11
#define HIGROMETROPIN 35
#define BOMBAPIN 2
#define LDRPIN 34

float readDHTTemperature();
float readDHTHumidity();
float readBrightness();
float readMoisture();

#endif
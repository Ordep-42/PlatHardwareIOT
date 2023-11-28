#ifndef SETUPSENSORS_H
#define SETUPSENSORS_H
#include "config.h"

#define DHTPIN 32
#define DHTTYPE DHT11
#define HIGROMETRO 35
#define BOMBA 2
#define LDR 34

float readTemperature();
float readHumidity();
float readBrightness();
float readMoisture();

#endif
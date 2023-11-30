#ifndef SETUPSENSORS_H
#define SETUPSENSORS_H

#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include "funcs.h"

#define DHTPIN 32
#define DHTTYPE DHT11
#define HIGROMETROPIN 35
#define LDRPIN 34

float readDHTTemperature();
float readDHTHumidity();
float readBrightness();
float readMoisture();
void initSensors();

#endif
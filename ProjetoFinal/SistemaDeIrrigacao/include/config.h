#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <PubSubClient.h>

#include "wifiHandler.h"
#include "setupSensors.h"

WiFiClient wifi_client;
PubSubClient mqtt_client(wifi_client);

const char* wifi_ssid = "NPITI-IoT";
const char* wifi_password = "NPITI-IoT";
int wifi_timeout = 100000;

const char* mqtt_broker = "io.adafruit.com";
const int mqtt_port = 1883;
int mqtt_timeout = 10000;

const char* mqtt_usernameAdafruitIO = "Ordep_1";
const char* mqtt_keyAdafruitIO = "aio_hhAc04dNXjouL70bVWgoBxB6p2b7";

#endif
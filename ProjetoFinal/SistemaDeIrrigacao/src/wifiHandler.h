#ifndef WIFIHANDLER_H
#define WIFIHANDLER_H

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>

extern WiFiClient wifi_client;

extern const char* wifi_ssid;
extern const char* wifi_password;
extern int wifi_timeout;

void initWiFi();
void connectWiFi();

#endif
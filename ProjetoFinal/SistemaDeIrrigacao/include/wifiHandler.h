#ifndef WIFIHANDLER_H
#define WIFIHANDLER_H

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>

#include "secureKeys.h"

extern WiFiClient wifi_client;

extern int wifi_timeout;

void initWiFi();
void connectWiFi();
void printConnectedWiFiStatus();
void printDisconnectedWiFiStatus();
void printWiFiScanStatus(int networksFound);
void printDiscoveredWiFiNetworks(int networksFound);
void scanAvailableWiFiNetworks();

#endif
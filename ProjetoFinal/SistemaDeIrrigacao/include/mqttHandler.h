#ifndef MQTTHANDLER_H
#define MQTTHANDLER_H

#include <PubSubClient.h>
#include "wifiHandler.h"

#define dataRate 30000

extern PubSubClient mqtt_client;

extern const char* mqtt_broker;
extern const int mqtt_port;
extern int mqtt_timeout;

extern const char* ClientID;
extern const char* mqtt_usernameAdafruitIO;
extern const char* mqtt_keyAdafruitIO;

void initMQTT();
void connectMQTT();
void printConnectedMQTTStatus();
void printDisconnectedMQTTStatus();
void handleMQTTConnection();
void publishData(float higroVal, float LDRVal, float tempVal, float humVal, int bombaStatus);

#endif
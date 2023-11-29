#ifndef MQTTHANDLER_H
#define MQTTHANDLER_H

#include <PubSubClient.h>
#include "wifiHandler.h"

extern PubSubClient mqtt_client;

extern const char* mqtt_broker;
extern const int mqtt_port;
extern int mqtt_timeout;

extern const char* mqtt_usernameAdafruitIO;
extern const char* mqtt_keyAdafruitIO;

#endif
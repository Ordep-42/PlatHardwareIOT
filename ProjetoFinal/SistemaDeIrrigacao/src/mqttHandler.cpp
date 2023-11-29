#include "mqttHandler.h"

PubSubClient mqtt_client(wifi_client);

const char* mqtt_broker = "io.adafruit.com";
const int mqtt_port = 1883;
int mqtt_timeout = 10000;

const char* mqtt_usernameAdafruitIO = "Ordep_1";
const char* mqtt_keyAdafruitIO = "aio_hhAc04dNXjouL70bVWgoBxB6p2b7";



#include "mqttHandler.h"

PubSubClient mqtt_client(wifi_client);

const char* mqtt_broker = "io.adafruit.com";
const int mqtt_port = 1883;
int mqtt_timeout = 10000;

const char* ClientID = "AutoGarden";
const char* mqtt_usernameAdafruitIO = "Ordep_1";
const char* mqtt_keyAdafruitIO = "aio_hhAc04dNXjouL70bVWgoBxB6p2b7";

void initMQTT() {
    Serial.println("Inicializando MQTT...");
    mqtt_client.setServer(mqtt_broker, mqtt_port);
    connectMQTT();
}

void connectMQTT() {
    unsigned long tempoInicial = millis();
    while (!mqtt_client.connected() && (millis() - tempoInicial < mqtt_timeout)) {
        if (WiFi.status() != WL_CONNECTED) {
            connectWiFi();
        }
        Serial.print("Conectando ao MQTT Broker..");

        if (mqtt_client.connect(ClientID, mqtt_usernameAdafruitIO, mqtt_keyAdafruitIO)) {
            printConnectedMQTTStatus();
        } else {
            printDisconnectedMQTTStatus();
        }
    }
}

void printConnectedMQTTStatus() {
    Serial.println("Conectado ao broker MQTT!");
}

void printDisconnectedMQTTStatus() {
    Serial.println("Conexão com o broker MQTT falhou!");
}

void handleMQTTConnection() {
    if (!mqtt_client.connected()) {
        connectMQTT();
    }
    mqtt_client.loop();
}

void publishData(float higroVal, float LDRVal, float tempVal, float humVal, int bombaStatus) {
    if (mqtt_client.connected()) {
        mqtt_client.publish("Ordep_1/feeds/higrometro", String(higroVal).c_str());
        mqtt_client.publish("Ordep_1/feeds/LDR", String(LDRVal).c_str());
        mqtt_client.publish("Ordep_1/feeds/temperatura", String(tempVal).c_str());
        mqtt_client.publish("Ordep_1/feeds/umidade-do-ar", String(humVal).c_str());
        mqtt_client.publish("Ordep_1/feeds/bomba", String(bombaStatus).c_str());
        Serial.println("Dados publicados");
    }
}
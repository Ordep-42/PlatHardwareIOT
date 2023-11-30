#include "config.h"

float higroVal;
float LDRVal;
float tempVal;
float humVal;

void connectMQTT() {
  unsigned long tempoInicial = millis();
  while (!mqtt_client.connected() && (millis() - tempoInicial < mqtt_timeout)) {
    if (WiFi.status() != WL_CONNECTED) {
      connectWiFi();
    }
    Serial.print("Conectando ao MQTT Broker..");

    if (mqtt_client.connect("ESP32Client", mqtt_usernameAdafruitIO, mqtt_keyAdafruitIO)) {
      Serial.println();
      Serial.print("Conectado ao broker MQTT!");
    } else {
      Serial.println();
      Serial.print("Conexão com o broker MQTT falhou!");
      delay(500);
    }
  }
  Serial.println();
}

void setup()
{
  Serial.begin(921600);
  initGarden();
  initWiFi();
  initMQTT();
}

void loop()
{
  if (mqtt_client.connected()) {
    sensorHandler();
    printValues();
    mqtt_client.publish("Ordep_1/feeds/LDR", String(LDRVal).c_str());
    mqtt_client.publish("Ordep_1/feeds/higrometro", String(higroVal).c_str());
    mqtt_client.publish("Ordep_1/feeds/temperatura", String(tempVal).c_str());
    mqtt_client.publish("Ordep_1/feeds/umidade-do-ar", String(humVal).c_str());
    //mqtt_client.publish("Ordep_1/feeds/bomba", String(bombaVal).c_str());
    Serial.println("Publicou o dadopassou");
    delay(60000);
    mqtt_client.loop();
  }
}
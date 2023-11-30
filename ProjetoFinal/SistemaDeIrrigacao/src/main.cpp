#include "config.h"

float higroVal;
float LDRVal;
float tempVal;
float humVal;

void readValues()
{
  higroVal = readMoisture();
  LDRVal = readBrightness();
  tempVal = readDHTTemperature();
  humVal = readDHTHumidity();
}

void printValues(){
  Serial.println("---------------------");
  Serial.print("LDR: ");
  Serial.print(LDRVal);
  Serial.println("%");
  Serial.print("Higrômetro: ");
  Serial.print(higroVal);
  Serial.println("%");
  Serial.print(F("Temperature: "));
  Serial.print(tempVal);
  Serial.println(F("°C"));
  Serial.print(F("Humidity: "));
  Serial.print(humVal);
  Serial.println(F("%"));
}

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
  initSensors();
  initRelay();
  initWiFi();
  initMQTT();
}

void loop()
{
  if (mqtt_client.connected()) {
    readValues(); 
    if (higroVal <= 30)
    {
      turnOnBomba();
    }
    else if (higroVal > 70)
    {
      turnOffBomba();
    }
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
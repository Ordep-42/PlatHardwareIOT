#include "config.h"

int higroVal = 0;
int higroValMapped = 0;
int LDRVal = 0;
int LDRValMapped = 0;
int bombaVal = 0;
sensors_event_t eventTemp;
sensors_event_t eventHum;
float tempVal;
float humVal;

DHT_Unified dht(DHTPIN, DHTTYPE);

void readValues()
{
  higroVal = analogRead(HIGROMETRO);
  higroValMapped = map(higroVal, 2900, 1400, 0, 100);

  if (higroValMapped < 0)
  {
    higroValMapped = 0;
  }
  else if (higroValMapped > 100)
  {
    higroValMapped = 100;
  }

  LDRVal = analogRead(LDR);
  LDRValMapped = map(LDRVal, 4095, 500, 0, 100);
  if (LDRValMapped > 100)
  {
    LDRValMapped = 100;
  }
  //Ler temperatura
  dht.temperature().getEvent(&eventTemp);
  tempVal = eventTemp.temperature;
  dht.humidity().getEvent(&eventHum);
  humVal = eventHum.relative_humidity;
}

void printValues(){
Serial.println("---------------------");
  Serial.print("LDR: ");
  Serial.print(LDRValMapped);
  Serial.println("%");
  Serial.print("Higrômetro: ");
  Serial.print(higroValMapped);
  Serial.println("%");
  Serial.print(F("Temperature: "));
  Serial.print(tempVal);
  Serial.println(F("°C"));
  Serial.print(F("Humidity: "));
  Serial.print(humVal);
  Serial.println(F("%"));
}

void connectWiFi() {
  Serial.print("Conectando à rede WiFi .. ");

  unsigned long tempoInicial = millis();
  while (WiFi.status() != WL_CONNECTED && (millis() - tempoInicial < wifi_timeout)) {
    Serial.print(".");
    delay(100);
  }
  Serial.println();

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Conexão com WiFi falhou!");
  } else {
    Serial.print("Conectado com o IP: ");
    Serial.println(WiFi.localIP());
  }
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
      mqtt_client.subscribe("Ordep_1/feeds/bomba");
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
  pinMode(LDR, INPUT);
  pinMode(HIGROMETRO, INPUT);
  pinMode(BOMBA, OUTPUT);
  dht.begin();
  WiFi.mode(WIFI_STA);
  WiFi.begin(wifi_ssid, wifi_password);
  connectWiFi();
  mqtt_client.setServer(mqtt_broker, mqtt_port);
}

void loop()
{
  if (!mqtt_client.connected()) { // Se MQTT não estiver conectado
    connectMQTT();
  }

  if (mqtt_client.connected()) {
    readValues(); 
    if (higroValMapped <= 30)
    {
      bombaVal = 1;
    }
    else if (higroValMapped > 70)
    {
      bombaVal = 0;
    }
    digitalWrite(BOMBA, bombaVal);
    printValues();
    mqtt_client.publish("Ordep_1/feeds/LDR", String(LDRValMapped).c_str());
    mqtt_client.publish("Ordep_1/feeds/higrometro", String(higroValMapped).c_str());
    mqtt_client.publish("Ordep_1/feeds/temperatura", String(tempVal).c_str());
    mqtt_client.publish("Ordep_1/feeds/umidade-do-ar", String(humVal).c_str());
    mqtt_client.publish("Ordep_1/feeds/bomba", String(bombaVal).c_str());
    Serial.println("Publicou o dadopassou");
    delay(60000);
    mqtt_client.loop();
  }
}
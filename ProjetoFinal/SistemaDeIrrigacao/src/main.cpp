#include "config.h"

void setup()
{
  Serial.begin(921600);
  initGarden();
  initWiFi();
  initMQTT();
}

void loop()
{
  sensorHandler();
  handleMQTTConnection();
  publishData(readMoisture(), readBrightness(), readDHTTemperature(), readDHTHumidity(), bombaStatus);
  delay(30000);
}
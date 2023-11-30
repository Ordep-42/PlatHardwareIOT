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
  printValuesToSerial();
  handleMQTTConnection();
  publishData(readMoisture(), readBrightness(), readDHTTemperature(), readDHTHumidity(), bombaStatus);
  delay(dataRate);
}
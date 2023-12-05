#include "config.h"

void setup()
{
  Serial.begin(115200);
  initWiFi();
  initGarden();
  initMQTT();
}

void loop()
{
  //sensorHandler();
  printValuesToSerial();
  handleMQTTConnection();
  publishData(readMoisture(), readBrightness(), readDHTTemperature(), readDHTHumidity(), bombaStatus);
  delay(dataRate);
}
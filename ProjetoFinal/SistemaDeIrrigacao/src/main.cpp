#include "config.h"

void sensorTask();

Task t1(WateringRate, TASK_FOREVER, &sensorTask);
Scheduler runner;

void sensorTask()
{
  sensorHandler();
  t1.delay(WATERINGDELAY);
  turnOffBomba();
}

void setup()
{
  Serial.begin(115200);
  initWiFi();
  initGarden();
  initMQTT();
  runner.init();
  runner.addTask(t1);
  t1.enable();
}

void loop()
{

  runner.execute();

  printValuesToSerial();
  handleMQTTConnection();
  publishData(readMoisture(), readBrightness(), readDHTTemperature(), readDHTHumidity(), bombaStatus);
  delay(dataRate);
}
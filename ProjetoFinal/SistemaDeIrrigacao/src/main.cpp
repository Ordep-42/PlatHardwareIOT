#include "config.h"

void sensorTask();

Task t1(WateringRate, TASK_FOREVER, &sensorTask);
Task t2(1, TASK_FOREVER, &oledHandler);
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
  runner.addTask(t2);
  t1.enable();
  t2.enable();
}

void loop()
{

  runner.execute();

  printValuesToSerial();
  handleMQTTConnection();
  publishData(readMoisture(), readBrightness(), readDHTTemperature(), readDHTHumidity(), bombaStatus);
  delay(dataRate);
}
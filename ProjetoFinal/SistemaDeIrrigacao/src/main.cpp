#include "config.h"

void sensorTask();
void oledTask();

Task t1(WateringRate, TASK_FOREVER, &sensorTask);
Task t2(1, TASK_FOREVER, &oledTask);
Scheduler runner;

void oledTask()
{
  oledHandler();
}

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
  //initMQTT();
  runner.init();
  runner.addTask(t1);
  runner.addTask(t2);
  t1.enable();
  t2.enable();
  initOLED();
  Serial.println("Sistema inicializado!");
}

void loop()
{
  Serial.println("Looping...");
  //runner.execute();
  printValuesToSerial();
  oledHandler();
  //handleMQTTConnection();
  //publishData(readMoisture(), readBrightness(), readDHTTemperature(), readDHTHumidity(), bombaStatus);
  //delay(dataRate);
  delay(1000);
}
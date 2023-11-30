#include "ntpHandler.h"

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

void initNTP()
{
  Serial.println("Inicializando NTP...");
  timeClient.begin();
  timeClient.setTimeOffset(-(3*3600));
  timeClient.update();
  Serial.println("NTP inicializado!");
}

int getHour()
{
  while (!timeClient.update())
  {
    timeClient.forceUpdate();
  }
  return timeClient.getHours();
}
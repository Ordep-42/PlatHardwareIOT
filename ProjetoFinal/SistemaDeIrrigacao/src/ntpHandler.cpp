#include "ntphandler.h"

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

String formattedDate;
String dayStamp;
String timeStamp;

void initNTP()
{
  Serial.println("Initializing NTP...");
  timeClient.begin();
  timeClient.setTimeOffset(-(3*3600));
  timeClient.update();
  Serial.println("NTP initialized!");
}

int getHour()
{
  while (!timeClient.update())
  {
    timeClient.forceUpdate();
  }
  return timeClient.getHours();
}
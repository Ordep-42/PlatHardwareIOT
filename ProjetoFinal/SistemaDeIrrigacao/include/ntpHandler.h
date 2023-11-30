#ifndef NTP_HANDLER_H
#define NTP_HANDLER_H

#include <NTPClient.h>
#include <WiFiUdp.h>

#include "wifiHandler.h"

extern String formattedDate;
extern String dayStamp;
extern String timeStamp;

void initNTP();
int getHour();
int getMinute();

#endif
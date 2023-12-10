#include "oledHandler.h"

unsigned long lastChange = 0;
int displayState = 0;

void printTimeToOled(int x, int y, int size)
{
  printToOLED(String(getHour()) + ":" + String(getMinute()), x, y, size);
}

void printMoistureToOled() {
  String data = String(readMoisture());
  drawBitmap(moistureLogo, LOGO_WIDTH, LOGO_HEIGHT, (SCREEN_WIDTH - 50 - LOGO_WIDTH ) / 2, 0);
  printToOLED(data, (SCREEN_WIDTH - 50 - sizeof(data)*12) / 2, SCREEN_HEIGHT - (7*2), 2);
}

void printBrightnessToOled() {
  String data = String(readBrightness());
  drawBitmap(brightnessLogo, LOGO_WIDTH, LOGO_HEIGHT, (SCREEN_WIDTH - 50 - LOGO_WIDTH ) / 2, 0);
  printToOLED(data, (SCREEN_WIDTH - 50 - sizeof(data)*12) / 2, SCREEN_HEIGHT - (7*2), 2);
}

void printTemperatureToOled() {
  String data = String(readDHTTemperature());
  drawBitmap(temperatureLogo, LOGO_WIDTH, LOGO_HEIGHT, (SCREEN_WIDTH - 50 - LOGO_WIDTH ) / 2, 0);
  printToOLED(data, (SCREEN_WIDTH - 50 - sizeof(data)*12) / 2, SCREEN_HEIGHT - (7*2), 2);
}

void printHumidityToOled() {
  String data = String(readDHTHumidity());
  drawBitmap(humidityLogo, LOGO_WIDTH, LOGO_HEIGHT, (SCREEN_WIDTH - 50 - LOGO_WIDTH ) / 2, 0);
  printToOLED(data, (SCREEN_WIDTH - 50 - sizeof(data)*12) / 2, SCREEN_HEIGHT - (7*2), 2);
}

void updateOled() {
  if (millis() - lastChange >= SCREEN_TIME) {
    lastChange = millis();
    displayState = (displayState + 1) % 4;
    
    switch (displayState) {
      case 0:
        display.clearDisplay();
        printHumidityToOled();
        break;
      case 1:
        display.clearDisplay();
        printTemperatureToOled();
        break;
      case 2:
        display.clearDisplay();
        printBrightnessToOled();
        break;
      case 3:
        display.clearDisplay();
        printMoistureToOled();
        break;
    }
  }
}

void oledHandler() {
  printTimeToOled(SCREEN_WIDTH - 50, 0, 2);
  updateOled();
}
#include "oledHandler.h"

void printTimeToOled(int x, int y, int size)
{
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(x, y);
  display.print("Hora: ");
  display.print(getHour());
  display.print(":");
  display.print(getMinute());
  display.display();
}
#include "setupOled.h"

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void initOLED()
{
	Serial.println("Inicializando Display");
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
  {
    Serial.println(F("SSD1306 allocation failed"));
  }
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor((128 - 9*12) / 2, SCREEN_HEIGHT - (7*2));
  display.println("PIPI POPO");
  display.display();
  drawBitmap();
}

void drawBitmap()
{
  display.drawBitmap((display.width()  - LOGO_WIDTH ) / 2, 0, logo, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();
  delay(LOGO_TIME);
}

void printToOLED(String text, int x, int y, int size) {
	display.setTextSize(size);
	display.setTextColor(WHITE);
	display.setCursor(x, y);
	display.println(text);
	display.display();
}
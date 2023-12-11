#include "setupOled.h"

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void initOLED()
{
	Serial.println("Inicializando Display");
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
  {
    Serial.println(F("Alocação do display falhou!"));
  }
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor((128 - 9*12) / 2, SCREEN_HEIGHT - (7*2));
  display.println("PIPI POPO");
  display.display();
  drawBitmap(logo, LOGO_WIDTH, LOGO_HEIGHT, (SCREEN_WIDTH  - LOGO_WIDTH ) / 2, 0);
  delay(LOGO_TIME);
  display.clearDisplay();
  display.display();
}

void drawBitmap(const unsigned char *bitmap, int width, int height, int x, int y)
{
  Serial.println("Drawing bitmap");
  display.drawBitmap(x, y, bitmap, width, height, 1);
  display.display();
}

void printToOLED(String text, int x, int y, int size) {
  Serial.println("Printing to OLED");
	display.setTextSize(size);
	display.setCursor(x, y);
	display.println(text);
	display.display();
}
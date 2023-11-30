#ifndef SETUPOLED_H
#define SETUPOLED_H

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

#include "bitmap.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

#define LOGO_WIDTH 48
#define LOGO_HEIGHT 48
#define LOGO_TIME 2000

extern Adafruit_SSD1306 display;

void initOLED();
void drawBitmap();
void printToOLED(String text, int x, int y, int size);

#endif
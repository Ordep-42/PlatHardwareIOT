#include "oledHandler.h"

void printTimeToOled(int x, int y, int size)
{
  printToOLED(String(getHour()) + ":" + String(getMinute()), x, y, size);
}

void printMoistureToOled(int x, int y, int size) {
  // Fazer o bitmap pra icone de umidade do solo e implementar aqui
}

void printBrightnessToOled(int x, int y, int size) {
  // Fazer o bitmap pra icone de luminosidade e implementar aqui
}

void printTemperatureToOled(int x, int y, int size) {
  // Fazer o bitmap pra icone de temperatura e implementar aqui
}

void printHumidityToOled(int x, int y, int size) {
  // Fazer o bitmap pra icone de umidade e implementar aqui
}

void printBombaStatusToOled(int x, int y, int size) {
  // Fazer o bitmap pra icone de bomba ligada e desligada e implementar aqui
}

void oledHandler() {
  printTimeToOled(103, 0, 1);
  // Mudar cada tela a cada x minutos
}
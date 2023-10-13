#include <SoftwareSerial.h>

SoftwareSerial ArduinoMaster(10, 11);

char cmd = "";
char old_cmd;

void setup() {
  ArduinoMaster.begin(9600);
}

void loop() {
  old_cmd = cmd;

  if (ArduinoMaster.available()) {
    cmd = ArduinoMaster.read();
  }

  if (cmd != old_cmd) {
    ArduinoMaster.write(cmd);
  }
}
#include <SoftwareSerial.h>

SoftwareSerial ArduinoSlave(10, 11);

char cmd = "";
char old_cmd;
char answer = "";
char old_answer;

void setup() {
  Serial.begin(9600);
  Serial.println("ENTER Commands:");
  ArduinoSlave.begin(9600);
}

void loop() {
  old_cmd = cmd;
  old_answer = answer;

  if (Serial.available()) {
    cmd = Serial.read();
  }
  if (ArduinoSlave.available()) {
    answer = ArduinoSlave.read();
  }

  if (cmd != old_cmd) {
    Serial.print("Master sent: ");
    Serial.println(cmd);
    ArduinoSlave.write(cmd);
  }
  if (answer != old_answer) {
    Serial.print("Slave received: ");
    Serial.println(answer);
  }
}
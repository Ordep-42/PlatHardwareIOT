#include <SoftwareSerial.h>

#define LEDPin 12;

SoftwareSerial ArduinoMaster(10, 11);

String msg = ""; 

int ledVal = 0;
int sensorVal = 0, oldSensorVal = 0;

void setup() {
  Serial.begin(9600);
  ArduinoMaster.begin(9600);
  pinMode(12, OUTPUT);
}

void loop() {
  readMasterPort();
  convertMsgToCmd();

  if (sensorVal != oldSensorVal) {
    Serial.print("Master sent: ");
    Serial.println(sensorVal);

    ledVal = map(sensorVal, 511, 0, 0, 255);
    if (ledVal < 0){
      ledVal = 0;
    }

    Serial.print("LED Value: ");
    Serial.println(ledVal);
    ArduinoMaster.print(ledVal);
    analogWrite(12
  , ledVal);

    oldSensorVal = sensorVal;
  }
}

void readMasterPort() {
  while (ArduinoMaster.available()) {
    delay(10);
    if (ArduinoMaster.available() > 0) {
      char c = ArduinoMaster.read();
      msg += c;
    }
  }
  ArduinoMaster.flush();
}

void convertMsgToCmd() {
  if (msg.length() > 0) {
    Serial.print("message length: ");
    Serial.println(msg.length());

    char carray[6];
    msg.toCharArray(carray, sizeof(carray));
    sensorVal = atoi(carray);
    msg = "";
  }
}
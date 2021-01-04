#include "morselib.h"

const int ledPin = 13;
Morse morse(ledPin);

void setup() {
  // initialize serial:
  Serial.begin(115200);
}

void loop() {
  while (Serial.available()) {
    String msg = Serial.readStringUntil('\n');
    morse.send(msg);   
    Serial.println(msg);
  }
}

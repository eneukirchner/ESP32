/*
  Reading a serial ASCII-encoded string.

*/

const int tdelay = 500; // ms time hi / lo
const int ledPin = 13;

void setup() {
  // initialize serial:
  Serial.begin(115200);
  // make the pins outputs:
  pinMode(ledPin, OUTPUT);
}


// Blink ledPin n times
void blink(int n)
{
  while (n-- > 0) {
    digitalWrite(ledPin, HIGH);
    delay(tdelay);
    digitalWrite(ledPin, LOW);
    delay(tdelay);  
  }
}

void loop() {
  // if there's any serial available, read it:
  while (Serial.available() > 0) {

    // look for the next valid integer in the incoming serial stream:
    int led = Serial.parseInt();
    
    // look for the newline. That's the end of your sentence:
    if (Serial.read() == '\n') {
      // constrain the values to 0 - 255 and invert
      // if you're using a common-cathode LED, just use "constrain(color, 0, 255);"
      blink(led);
      
      // print the three numbers in one string as hexadecimal:
      Serial.println(led, HEX);
    }
  }
}

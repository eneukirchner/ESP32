// run led blink in separate thread

#include <pthread.h>
// LED pins
const int led = 2;

pthread_t pt;
int t = 1000; // ms

void* blink(void* p){
  for(;;) {
    digitalWrite(led, HIGH);
    delay(t);
    digitalWrite(led, LOW);
    delay(t);
  } 
}

void setup() {
  Serial.begin(115200); 
  Serial.println("t = " + String(t));
  pinMode(led, OUTPUT);
  pthread_create(&pt, NULL, blink, NULL);
}

void loop() {
  while (Serial.available()) {
    String str = Serial.readStringUntil('\n');
    t = str.toInt();  
    Serial.println("t = " + String(t));
  }
}

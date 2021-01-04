#define LED_PIN    LED_BUILTIN

volatile int ledStatus = 0;
hw_timer_t *timer = NULL;
int t = 1000;

void IRAM_ATTR onTimerMehrfach() {
  ledStatus = !ledStatus;
  digitalWrite(LED_PIN, ledStatus); 
}
 
void setup() { 
  Serial.begin(115200); 
  pinMode(LED_PIN, OUTPUT);   
  
  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, &onTimerMehrfach, true);
  timerAlarmWrite(timer, t * 1000, true);  // alle 1 Sekunden
  timerAlarmEnable(timer);
}
 
void loop() { 
  Serial.println("Period = " + String(t) + " ms>");
  if (Serial.available()) {
    t = Serial.parseInt();
    timerAlarmWrite(timer, t * 1000,  true);
  }
  
  delay(1000);
}

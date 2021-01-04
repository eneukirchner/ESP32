/* Frequency counter test 
   Connect Pin 14 -> 27 with jumper
*/

#define OUTPIN 14
#define FREQ 100000

#define INPIN    27

hw_timer_t * timer = NULL;
volatile SemaphoreHandle_t timerSemaphore;
portMUX_TYPE buttonMux = portMUX_INITIALIZER_UNLOCKED;

volatile int pulseCounter = 0;
volatile int t0 = 0;

void IRAM_ATTR onTimer(){
  xSemaphoreGiveFromISR(timerSemaphore, NULL);
}

void IRAM_ATTR onButton() {
    portENTER_CRITICAL_ISR(&buttonMux);
    pulseCounter++;
    portEXIT_CRITICAL_ISR(&buttonMux);
}

void setup() {
  Serial.begin(115200);
  pinMode(INPIN, INPUT);
  attachInterrupt(INPIN, onButton, FALLING);
  
  timerSemaphore = xSemaphoreCreateBinary();
  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, 1000000, true);
  timerAlarmEnable(timer);

  ledcSetup(0, FREQ, 8); // channel, frequency, resolution
  ledcAttachPin(OUTPIN, 0); // pin, channel
  ledcWrite(0, 128);  // duty cycle 50%
}

void loop() {
  // If Timer has fired
  if (xSemaphoreTake(timerSemaphore, 0) == pdTRUE){
    portENTER_CRITICAL(&buttonMux);
    int cnt = pulseCounter;
    pulseCounter = 0;
    portEXIT_CRITICAL(&buttonMux);
    Serial.println(cnt);
  }
  
}

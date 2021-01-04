/* Frequency counter */

// Stop button is attached to PIN 13
#define BTN    12
#define DEBOUNCE_T 50

hw_timer_t * timer = NULL;
volatile SemaphoreHandle_t timerSemaphore;
portMUX_TYPE buttonMux = portMUX_INITIALIZER_UNLOCKED;

volatile int pulseCounter = 0;
volatile int t0 = 0;

void IRAM_ATTR onTimer(){
  xSemaphoreGiveFromISR(timerSemaphore, NULL);
}

void IRAM_ATTR onButton() {
  if ((millis() - t0) > DEBOUNCE_T) {
    portENTER_CRITICAL_ISR(&buttonMux);
    pulseCounter++;
    portEXIT_CRITICAL_ISR(&buttonMux);
    t0 = millis();
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(BTN, INPUT_PULLUP);
  attachInterrupt(BTN, onButton, FALLING);
  
  timerSemaphore = xSemaphoreCreateBinary();
  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, 5000000, true);
  timerAlarmEnable(timer);
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

const int LED_PIN = 11;
int lightLevel = 0;
int lightIncrement = 1;


void setup() {
  pinMode(LED_PIN, OUTPUT);
  
  cli();
  
  TCCR0A = 0;// set entire TCCR2A register to 0
  TCCR0B = 0;// same for TCCR2B
  TCNT0  = 0;//initialize counter value to 0
  // set compare match register for 2khz increments
  OCR0A = 124;// = (16*10^6) / (2000*64) - 1 (must be <256)
  // turn on CTC mode
  TCCR0A |= (1 << WGM01);
  // Set CS01 and CS00 bits for 64 prescaler
  TCCR0B |= (1 << CS01) | (1 << CS00);   
  // enable timer compare interrupt
  TIMSK0 |= (1 << OCIE0A);
  
  sei();
}

ISR(TIMER0_COMPA_vect) {
  int newLevel = lightLevel + lightIncrement;
  
  if (newLevel == 256 || newLevel == 0) {
    lightIncrement *= -1;
  }
  
  lightLevel += lightIncrement;
  analogWrite(LED_PIN, lightLevel);
}

void loop() {
}

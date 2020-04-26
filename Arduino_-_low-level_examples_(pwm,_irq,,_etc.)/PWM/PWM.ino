const int LED_PIN = 11;
int lightLevel = 0;
int lightIncrement = 1;


void setup() {
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  int newLevel = lightLevel + lightIncrement;
  
  if (newLevel == 256 || newLevel == 0) {
    lightIncrement *= -1;
  }
  
  lightLevel += lightIncrement;
  analogWrite(LED_PIN, lightLevel);
  delay(100);
}


int LED_PIN = 11;
int POT_PIN = A0;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(POT_PIN, INPUT);
}

void loop() {
  int rotation, brightness;
  
  rotation = analogRead(POT_PIN);
  brightness = map(rotation, 0, 1023, 0, 255);
  analogWrite(LED_PIN, brightness);
}

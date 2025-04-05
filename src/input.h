#ifndef INPUT_H
#define INPUT_H

#define BUTTON_PIN 5
bool isPaused = false;

void setupInput() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void handleButton() {
  static bool lastButtonState = HIGH;
  bool currentState = digitalRead(BUTTON_PIN);

  if (currentState == LOW && lastButtonState == HIGH) {
    delay(50); // debounce
    isPaused = !isPaused;
    Serial.println(isPaused ? "Paused" : "Resumed");
  }
  lastButtonState = currentState;
}

#endif

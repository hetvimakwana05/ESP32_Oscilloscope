#include "display.h"
#include "input.h"
#include "bluetooth.h"
#include "waveform.h"

void setup() {
  Serial.begin(115200);
  setupBluetooth();
  setupDisplay();
  setupInput();
}

void loop() {
  handleButton();      // Pause/Resume toggle
  if (isPaused) return;
  updateWaveform();    // ADC read, display, and BT send
}

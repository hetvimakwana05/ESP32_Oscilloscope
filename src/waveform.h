#ifndef WAVEFORM_H
#define WAVEFORM_H

#include "display.h"
#include "bluetooth.h"

#define ADC_PIN 4
int prevY[screenWidth];
int x = 0;

void updateWaveform() {
  int adcValue = analogRead(ADC_PIN);
  float voltage = adcValue * (3.3 / 4095.0);

  Serial.print("ADC: ");
  Serial.print(adcValue);
  Serial.print(" | Voltage: ");
  Serial.println(voltage);
  sendBTData(adcValue, voltage);

  int y = map(adcValue, 0, 4095, screenHeight / 2, 0);
  tft.drawPixel(x, prevY[x], ST77XX_BLACK);
  tft.drawPixel(x, y, ST77XX_GREEN);
  prevY[x] = y;

  x = (x + 1) % screenWidth;
}

#endif

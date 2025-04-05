#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include "BluetoothSerial.h"
BluetoothSerial SerialBT;

void setupBluetooth() {
  SerialBT.begin("ESP32_Scope");
}

void sendBTData(int adcValue, float voltage) {
  SerialBT.print("ADC: ");
  SerialBT.print(adcValue);
  SerialBT.print(" | Voltage: ");
  SerialBT.println(voltage);
}

#endif

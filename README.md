# 📟 ESP32 Digital Portable Oscilloscope

A low-cost, real-time digital oscilloscope built using the ESP32 and a 240x320 TFT screen. Ideal for students, hobbyists, and engineers needing a compact and wireless signal analyzer.

## 🔧 Features

- Real-time waveform display
- AC/DC signal selection using toggle switch
- 1x/10x gain resolution switching
- Pause/Resume with a button
- Bluetooth streaming of ADC and voltage data
- 8x8 visual grid for accurate waveform plotting

## 🛠️ Hardware Components

- ESP32 Dev Board
- ST7789 TFT 240x320 display
- Push buttons (for control)
- Toggle switches (AC/DC & Gain)
- Voltage divider + optional capacitor
- Breadboard or PCB

## 🚀 How to Use

1. Connect the components as per the schematic
2. Open `src/oscilloscope.ino` in Arduino IDE
3. Select **ESP32 WROOM DA Module**
4. Install required libraries:
   - Adafruit_GFX
   - Adafruit_ST7789
   - BluetoothSerial
5. Upload the code to ESP32
6. View signal on the TFT and via Bluetooth


## 📡 Bluetooth Output

Use a mobile app like **Serial Bluetooth Terminal** to view:

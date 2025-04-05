//with successful runstop button
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>
#include <math.h>
#include "BluetoothSerial.h"

#define TFT_CS     14   
#define TFT_RST    15   
#define TFT_DC     32   
#define TFT_SCK    18  
#define TFT_MOSI   23  
#define ADC_PIN    4     // ADC input from signal source
#define BUTTON_PIN 5     // Push button to pause/resume

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);
BluetoothSerial SerialBT;

const int screenWidth = 240;
const int screenHeight = 320;
const int midY = screenHeight / 2;  // Center Y position (0V)

int prevY[screenWidth];  // Store previous Y values for clearing
bool isPaused = false;   // Pause flag

void setup() {
    Serial.begin(115200);
    SerialBT.begin("ESP32_Scope"); // Bluetooth device name
    pinMode(BUTTON_PIN, INPUT_PULLUP); // Button with internal pull-up resistor
    tft.init(240, 320);
    tft.setRotation(0);

    drawFullScreenGUI();
    memset(prevY, midY, sizeof(prevY)); // Initialize previous Y positions
}

void loop() {
    // Check if button is pressed (with debouncing)
    static bool lastButtonState = HIGH;
    bool buttonState = digitalRead(BUTTON_PIN);

    if (buttonState == LOW && lastButtonState == HIGH) {
        delay(50); // Debounce delay
        isPaused = !isPaused;  // Toggle pause state
        Serial.println(isPaused ? "Paused" : "Resumed");
    }
    lastButtonState = buttonState;

    if (isPaused) return;  // Stop updating display if paused

    static int x = 0;

    int adcValue = analogRead(ADC_PIN);
    float voltage = adcValue * (3.3 / 4095.0);

    Serial.print("ADC: "); Serial.print(adcValue);
    Serial.print(" | Voltage: "); Serial.println(voltage);
    SerialBT.print("ADC: "); SerialBT.print(adcValue);
    SerialBT.print(" | Voltage: "); SerialBT.println(voltage);

    int y = map(adcValue, 0, 4095, screenHeight / 2, 0);
    tft.drawPixel(x, prevY[x], ST77XX_BLACK); // Erase previous pixel
    tft.drawPixel(x, y, ST77XX_GREEN);
    prevY[x] = y;

    x++;
    if (x >= screenWidth) {  
        x = 0;
    }

    delayMicroseconds(50);
}

void drawFullScreenGUI() {
    tft.fillScreen(ST77XX_BLACK);
    drawGrid();
    tft.drawFastHLine(0, midY, screenWidth, ST77XX_WHITE);
    tft.drawFastVLine(screenWidth / 2, 0, screenHeight, ST77XX_WHITE);
    tft.setTextColor(ST77XX_WHITE);
    tft.setTextSize(2);
    tft.setCursor(10, 10);
    tft.print("Time (ms)");
    tft.setCursor(10, screenHeight - 30);
    tft.print("Voltage (V)");
}

void drawGrid() {
    int columnSpacing = screenWidth / 8;
    for (int i = 1; i < 8; i++) {
        int x = i * columnSpacing;
        tft.drawFastVLine(x, 0, screenHeight, ST77XX_BLUE);
    }

    int rowSpacing = screenHeight / 10;
    for (int i = 1; i < 10; i++) {
        int y = i * rowSpacing;
        tft.drawFastHLine(0, y, screenWidth, ST77XX_BLUE);
    }
}

#ifndef DISPLAY_H
#define DISPLAY_H

#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>

#define TFT_CS   14
#define TFT_RST  15
#define TFT_DC   32
#define TFT_SCK  18
#define TFT_MOSI 23

extern Adafruit_ST7789 tft;
const int screenWidth = 240;
const int screenHeight = 320;
const int midY = screenHeight / 2;

void drawGrid() {
  int col = screenWidth / 8;
  for (int i = 1; i < 8; i++)
    tft.drawFastVLine(i * col, 0, screenHeight, ST77XX_BLUE);

  int row = screenHeight / 10;
  for (int i = 1; i < 10; i++)
    tft.drawFastHLine(0, i * row, screenWidth, ST77XX_BLUE);
}

void drawFullScreenGUI() {
  tft.fillScreen(ST77XX_BLACK);
  drawGrid();
  tft.drawFastHLine(0, midY, screenWidth, ST77XX_WHITE);
  tft.drawFastVLine(screenWidth / 2, 0, screenHeight, ST77XX_WHITE);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(2);
  tft.setCursor(10, 10); tft.print("Time (ms)");
  tft.setCursor(10, screenHeight - 30); tft.print("Voltage (V)");
}

void setupDisplay() {
  tft.init(screenWidth, screenHeight);
  tft.setRotation(0);
  drawFullScreenGUI();
}

#endif

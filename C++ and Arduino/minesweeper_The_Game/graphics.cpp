#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include "graphics.h"
#include "option.h"
#include "menu.h"
#include "block.h"
#include "game.h"

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

// initializes the LCD screen and sets it to the correct orientation
void setupLCD() {
  tft.begin();
  tft.setRotation(3);
  tft.fillScreen(WHITE);
}

void drawMenuBackground() {
  tft.fillScreen(WHITE);
  for (int i = 0; i < 7; i++) {
    for (int j = 0; j < 10; j++) {
      tft.fillRect(i * 50, j * 25, 20, 15, RED);
      tft.fillRect(i * 50 + 25, j * 25, 20, 15, GREEN);
      tft.fillCircle(i * 50 + 25, j * 25, 5, WHITE);
      tft.drawCircle(i * 50 + 25, j * 25, 5, BLACK);
    }
  }
}

void drawMenuOption(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t radius, uint16_t colour) {
  tft.fillRoundRect(x, y, width, height, radius, colour);
}

void drawText(uint16_t x, uint16_t y, uint8_t textSize, uint16_t textColour, const char* text) {
  tft.setCursor(x, y);
  tft.setTextSize(textSize);
  tft.setTextColor(textColour);
  tft.println(text);
}

void drawTitle() {
  tft.fillRoundRect(10, 20, 300, 50, 10, PINK);
  drawText(35, 30, 4, WHITE, "Minesweeper");
}

void drawInstructions() {
  drawMenuBackground();
  tft.fillRoundRect(10, 20, 300, 200, 10, PINK);
  drawText(70, 30, 4, WHITE, "CONTROLS");
  drawText(30, 80, 1, WHITE, "Use the joystick to move the cursor");
  drawText(30, 100, 1, WHITE, "Press the joystick to reveal block underneath");
  drawText(30, 120, 1, WHITE, "Press the pushbutton to add or remove flags");
  drawText(30, 140, 1, WHITE, "Press the reset button for a new game");
  drawText(30, 180, 1, WHITE, "To return to the home screen, press the ");
  drawText(30, 200, 1, WHITE, "joystick");
}

void gameStartup() {
  tft.fillScreen(WHITE);
  drawText(20, 100, 2, BLACK, "Let's sweep some mines!");
}

void drawGameBackground() {
  tft.fillScreen(WHITE);
}

void drawBlock(uint16_t x, uint16_t y, uint16_t width, uint16_t height) {
  tft.drawRect(x, y, width, height, BLACK);
  tft.fillRect(x + 2, y + 2, width - 3, height - 3, BLUE);
}

void drawBlockWithMine(uint16_t x, uint16_t y, uint16_t width, uint16_t height) {
  tft.drawRect(x, y, width, height, BLACK);
  tft.fillRect(x + 1, y + 1, width - 2, height - 2, BLUE);
  tft.fillCircle(x + 10, y + 5, 3, BLACK);
  tft.fillRect(x + 5, y + 8, 12, 8, BLACK);
}

void drawRevealedBlock(uint16_t x, uint16_t y, uint16_t width, uint16_t height) {
  tft.drawRect(x, y, width, height, BLACK);
  tft.fillRect(x + 1, y + 1, width - 2, height - 2, LIGHTBLUE);
}

void drawNumber(uint16_t x, uint16_t y, uint16_t value) {
  tft.setTextSize(2);
  tft.setTextColor(BLACK);
  tft.setCursor(x + 5, y + 3);
  tft.print(value);
}

void drawCursor(uint16_t x, uint16_t y) {
  x = 20 * x + 10;
  y = 20 * y + 10;
  tft.fillCircle(x, y, 5, BLACK);
  tft.fillCircle(x, y, 7, YELLOW); //face color
  tft.fillCircle(x, y + 1, 3, RED); //smile
  tft.fillCircle(x, y - 2,  4, YELLOW); //smile
  tft.drawCircle(x, y, 7, RED); //face border
  tft.fillCircle(x - 3, y - 2, 1, RED); //eye color
  tft.fillCircle(x + 2, y - 2, 1, RED); //eye color
}

void drawFlag(int x, int y) {
	tft.fillTriangle(x + 10, y + 3, x + 15, y + 8, x + 10, y + 13, RED);
	tft.fillTriangle(x + 10, y + 13, x + 15, y + 16, x + 6, y + 16, BLACK);
}

void victory() {
  tft.fillScreen(WHITE);
  drawText(20, 80, 3, ORANGE, "Congratulations!");
  drawText(90, 120, 3, ORANGE, "You WIN!");
}

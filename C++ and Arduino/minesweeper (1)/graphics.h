#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

#define TFT_DC 9
#define TFT_CS 10

#define DISPLAY_WIDTH  320
#define DISPLAY_HEIGHT 240

#define BLACK 0x0000
#define WHITE 0xFFFF
#define ORANGE 0xFC40
#define BLUE 0x64BD
#define LIGHTBLUE 0xB71C
#define RED 0xF800
#define GREEN 0x0C03
#define YELLOW 0xFFE0
#define PINK 0xFD32

void setupLCD();
void drawMenuBackground();
void drawMenuOption(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t radius, uint16_t colour);
void drawText(uint16_t x, uint16_t y, uint8_t textSize, uint16_t textColour, const char* text);
void drawTitle();
void drawInstructions();
void gameStartup();
void drawGameBackground();
void drawBlock(uint16_t x, uint16_t y, uint16_t width, uint16_t height);
void drawBlockWithMine(uint16_t x, uint16_t y, uint16_t width, uint16_t height);
void drawRevealedBlock(uint16_t x, uint16_t y, uint16_t width, uint16_t height);
void drawNumber(uint16_t x, uint16_t y, uint16_t value);
void drawCursor(uint16_t x, uint16_t y);
void drawFlag(int x, int y);
void victory();

#endif

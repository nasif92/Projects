#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include "graphics.h"
#include "option.h"
#include "menu.h"
#include "block.h"
#include "game.h"

Option::Option(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t w, uint16_t h, uint16_t r, const char* n) {
  coordinateX = x0;
  coordinateY = y0;
  textX = x1;
  textY = y1;
  width = w;
  height = h;
  radius = r;
  name = n;
}

void Option::createOption() {
  drawMenuOption(coordinateX, coordinateY, width, height, radius, BLACK);
  drawText(textX, textY, 2, WHITE, name);
}

void Option::unhighlight() {
  highlighted = false;
  createOption();
}

void Option::highlight() {
  highlighted = true;
  drawMenuOption(coordinateX, coordinateY, width, height, radius, PINK);
  drawText(textX, textY, 2, WHITE, name);
}

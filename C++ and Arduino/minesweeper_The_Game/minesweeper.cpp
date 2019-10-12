#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include "graphics.h"
#include "option.h"
#include "menu.h"
#include "block.h"
#include "game.h"


void setup() {
  init();

  Serial.begin(9600);

  pinMode(JOY_SELECT, INPUT_PULLUP);
  pinMode(BUTTON, INPUT_PULLUP);

  setupLCD();
}

int main() {
  setup();

  startupMainMenu();

  Serial.end();
  
  return 0;
}

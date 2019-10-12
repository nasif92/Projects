#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include "graphics.h"
#include "option.h"
#include "menu.h"
#include "block.h"
#include "game.h"

void createMenu(Option *options) {
  drawMenuBackground();
  drawTitle();
  options->highlight();
  (options + 1)->createOption();
}

bool indexInArray(int index, uint16_t maxIndex, int delta) {
  index += delta;
  if(index >= 0 && index <= maxIndex) {
    return true;
  }
  return false;
}

void startupMainMenu() {
  Option newGame(70, 120, 115, 130, 180, 40, 15, "New Game");
  Option controls(70, 180, 115, 190, 180, 40, 15, "Controls");
  Option options[] = {newGame, controls};

  createMenu(options);

  Option *optionIndex = options;
  uint16_t maxIndex = sizeof(options) / sizeof(options[0]) - 1;

  while(true) {
    int vertical = analogRead(JOY_VERT_ANALOG);
    bool joySelect = digitalRead(JOY_SELECT);

    if(abs(vertical - JOY_CENTRE) > JOY_DEADZONE) {
      int delta = (vertical - JOY_CENTRE) / JOY_DEADZONE;
      optionIndex->unhighlight();
      if(indexInArray(optionIndex - options, maxIndex, delta)) {
        optionIndex += delta;
      }
      optionIndex->highlight();
      delay(250);
    }

    if(joySelect == LOW) {
      joySelect = HIGH;
      if(optionIndex->getName() == "New Game") {
        gameStartup();
        delay(1500);
        initializeGame(COLUMNS_OF_BLOCK, ROWS_OF_BLOCK);
        while(true) {
          moveCursor();
        }
      }
      if(optionIndex->getName() == "Controls") {
        drawInstructions();
        delay(250);
        while(joySelect == HIGH) {
          joySelect = digitalRead(JOY_SELECT);
        }
        optionIndex = options;
        createMenu(optionIndex);
      }
    }
  }
}

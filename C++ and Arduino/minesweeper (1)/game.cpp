#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include "graphics.h"
#include "option.h"
#include "menu.h"
#include "block.h"
#include "game.h"

// create a two dimensional array of block objects
Block block[COLUMNS_OF_BLOCK][ROWS_OF_BLOCK];
// mines are generated after a block is revealed
bool minesGenerated = false;
// the x and y position of the cursor
int posX = 7;
int posY = 7;

// draws the grid and initializes the column and row index of the blocks
void initializeGame(uint8_t column, uint8_t row) {
  drawGameBackground();
  for(int i = 0; i < column; i++) {
    for(int j = 0; j < row; j++) {
      block[i][j].setPosition(i, j);
      block[i][j].createBlock();
    }
  }
  drawCursor(posX, posY);
}

// checks if the block is within the grid. This avoids indexing out of the block array
bool withinGrid(int column, int row) {
  if(column >= 0 && column < COLUMNS_OF_BLOCK && row >= 0 && row < ROWS_OF_BLOCK) {
    return true;
  }
  else {
    return false;
  }
}

// increases the value of a block for every mine that is adjacent to it
void increaseMineValues(int x, int y) {
  for(int i = -1; i < 2; i++) {
    for(int j = -1; j < 2; j++) {
      int adjX = x + i;
      int adjY = y + j;

      if(withinGrid(adjX, adjY)) {
        block[adjX][adjY].increaseMineValue();
      }
    }
  }
}

// this function reveals all the adjacent blocks to the selected block if the selected block has no mines adjacent to it
// using recursion, if adjacent blocks also have no the mines adjacent to it, this function is applied to that block as well.
void expand(int x, int y) {
  for(int i = -1; i < 2; i++) {
    for(int j = -1; j < 2; j++) {
      int adjX = x + i;
      int adjY = y + j;

      if(withinGrid(adjX, adjY)) {
        if(block[adjX][adjY].getMineValue() == 0 && !block[adjX][adjY].isRevealed()) {
          block[adjX][adjY].revealBlock();
          expand(adjX, adjY);
        }
        block[adjX][adjY].revealBlock();
      }
    }
  }
}

// gets a random number between 0 and the max parameter - 1 using the analog pin on the Arduino
uint8_t getRandomNumber(uint8_t max) {
  uint8_t randomNumber = analogRead(A4) % max;
  return randomNumber;
}

bool isAdjacent(int x, int y) {
  if(abs(x - posX) <= 1 && abs(y - posY) <= 1) {
    return true;
  } else {
    return false;
  }
}

// randomizes the location of the mines of the grid
void randomizeMines(uint8_t numberOfMines) {
  uint8_t gridMines = 0;
  while(gridMines != numberOfMines) {
    uint8_t i = getRandomNumber(COLUMNS_OF_BLOCK);
    uint8_t j = getRandomNumber(ROWS_OF_BLOCK);

    // checks if the block already contains a mine
    if(!block[i][j].isMine() && !isAdjacent(i, j)) {
      block[i][j].createMine();
      increaseMineValues(i, j);
      gridMines++;
    }
  }
}

// reveals all mines if a block that contains a mine is selected
void gameOver(int column, int row) {
  for(int i = 0; i < column; i++) {
    for(int j = 0; j < row; j++) {
      if(block[i][j].isMine()) {
        block[i][j].showMine();
      }
    }
  }
}

void moveCursor() {
  int vertical = analogRead(JOY_VERT_ANALOG);
  int horizontal = analogRead(JOY_HORIZ_ANALOG);
  bool joySelect = digitalRead(JOY_SELECT);
  bool buttonSelect = digitalRead(BUTTON);
  // change this variable to change the number of mines in the game
  int mines = 30;

  // draws the previous block the cursor was on
  if(abs(vertical - JOY_CENTRE) > JOY_DEADZONE) {
    int delta = (vertical - JOY_CENTRE)/JOY_DEADZONE;
    block[posX][posY].reDrawBlock();
    posY += delta;
    posY = constrain(posY, 0, ROWS_OF_BLOCK-1);
    drawCursor(posX, posY);
    delay(250);
  }

  // draws the previous block the cursor was on
  if(abs(horizontal - JOY_CENTRE) > JOY_DEADZONE) {
    int delta = (horizontal - JOY_CENTRE)/JOY_DEADZONE;
    block[posX][posY].reDrawBlock();
    posX -= delta;
    posX = constrain(posX, 0, COLUMNS_OF_BLOCK-1);
    drawCursor(posX, posY);
    delay(250);
  }

  if(joySelect == LOW) {
    // randmizes the location of the mines after first block selection
    if(!minesGenerated) {
      randomizeMines(mines);
      minesGenerated = true;
    }

    if(!block[posX][posY].isFlag()) {
      block[posX][posY].revealBlock();

      if(block[posX][posY].isMine()) {
        gameOver(COLUMNS_OF_BLOCK, ROWS_OF_BLOCK);
        while(true) {}
      }

      if(block[posX][posY].getMineValue() == 0) {
        expand(posX, posY);
        drawCursor(posX, posY);
      }
      delay(500);
    }
  }

  if(buttonSelect == LOW) {
    block[posX][posY].addFlag();
    delay(500);
  }

  // checks if all the blocks that do not contain a mine are revealed
  if(block[posX][posY].getNumRevealed() == COLUMNS_OF_BLOCK * ROWS_OF_BLOCK - mines) {
    victory();
    while(true) {}
  }
}

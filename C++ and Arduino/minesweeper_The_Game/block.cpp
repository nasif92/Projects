#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include "graphics.h"
#include "option.h"
#include "menu.h"
#include "block.h"
#include "game.h"

Block::Block() {

}

uint8_t Block::numRevealed = 0;

void Block::createBlock() {
  drawBlock(20 * columnIndex, 20 * rowIndex, 20, 20);
  if(containsFlag) {
    drawFlag(20 * columnIndex, 20 * rowIndex);
  }
}

void Block::createMine() {
  containsMine = true;
}

void Block::showMineValue() {
  drawRevealedBlock(20 * columnIndex, 20 * rowIndex, 20, 20);
  if(mineValue > 0) {
    drawNumber(20 * columnIndex, 20 * rowIndex, mineValue);
  }
}

void Block::showMine() {
  drawBlockWithMine(20 * columnIndex, 20 * rowIndex, 20, 20);
}

void Block::increaseMineValue() {
  mineValue++;
}

void Block::reDrawBlock() {
  if(revealed && containsMine) {
    showMine();
  }
  else if (revealed) {
    showMineValue();
  }
  else {
    createBlock();
  }
}

void Block::revealBlock() {
  if(!revealed) {
    numRevealed++;
  }
  revealed = true;
  reDrawBlock();
}

void Block::addFlag() {
  if(!containsFlag && !revealed) {
    containsFlag = true;
    drawFlag(20 * columnIndex, 20 * rowIndex);
  } else {
    containsFlag = false;
    drawCursor(columnIndex, rowIndex);
  }
}

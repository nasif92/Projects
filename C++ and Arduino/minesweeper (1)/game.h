#ifndef GAME_H
#define GAME_H

#define BUTTON 3

#define ROWS_OF_BLOCK 12
#define COLUMNS_OF_BLOCK 16

void initializeGame(uint8_t column, uint8_t row);
bool withinGrid(int column, int row);
void increaseMineValues(int x, int y);
void expand(int x, int y);
uint8_t getRandomNumber(uint8_t max);
bool isAdjacent(int x, int y);
void randomizeMines(uint8_t numberOfMines);
void moveCursor();
void startupMenu();

#endif

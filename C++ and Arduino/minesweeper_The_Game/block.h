#ifndef BLOCK_H
#define BLOCK_H

class Block {
  private:
    uint8_t rowIndex;
    uint8_t columnIndex;
    uint8_t mineValue;
    static uint8_t numRevealed;
    bool containsMine;
    bool containsFlag;
    bool revealed;

  public:
    Block();

    uint8_t getRowIndex() { return rowIndex; }
    uint8_t getColumnIndex() { return columnIndex; }
    uint8_t getMineValue() { return mineValue; }
    uint8_t getNumRevealed() { return numRevealed; }
    bool isRevealed() { return revealed; }
    bool isMine() { return containsMine; }
    bool isFlag() { return containsFlag; }

    void setPosition(uint16_t i, uint16_t j) { columnIndex = i; rowIndex = j; }
    void createBlock();
    void createMine();
    void showMineValue();
    void showMine();
    void increaseMineValue();
    void reDrawBlock();
    void revealBlock();
    void addFlag();
};

#endif

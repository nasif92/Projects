#ifndef MENU_H
#define MENU_H

#define JOY_VERT_ANALOG A1
#define JOY_HORIZ_ANALOG A0
#define JOY_SELECT 2

#define JOY_CENTRE   512
#define JOY_DEADZONE 256

void createMenu(Option *options, uint16_t maxIndex);
bool indexInArray(int index, uint16_t maxIndex, int delta);
void startupMainMenu();

#endif

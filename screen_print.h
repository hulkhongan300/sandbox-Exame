#ifndef SCREEN_PRINT_H
#define SCREEN_PRINT_H

#include "raylib.h"

// Prints status overlay, title, box count, and controls to the Raylib window screen
void PrintToScreen(int boxCount);

// Prints custom text onto the screen with drop shadow for clarity
void PrintCustomText(const char *text, int posX, int posY, int fontSize, Color color);

// Checks if screenshot key (P, F12, or PrintScreen) was pressed and saves screenshot
void CheckPrintScreen(void);

#endif // SCREEN_PRINT_H

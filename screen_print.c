#include "screen_print.h"

void PrintToScreen(int boxCount) {
    // Semi-transparent HUD background panel for clean readability over moving boxes
    DrawRectangle(12, 12, 330, 84, (Color){ 10, 10, 15, 200 });
    DrawRectangleLines(12, 12, 330, 84, (Color){ 80, 120, 200, 255 });

    // Print text directly to the Raylib window screen
    DrawText("RAYLIB BOX SIMULATION", 24, 20, 18, RAYWHITE);
    DrawText(TextFormat("Boxes Count: %d", boxCount), 24, 44, 16, LIME);
    DrawText(TextFormat("FPS: %d  |  [R] Reset  |  [P] Screenshot", GetFPS()), 24, 68, 13, LIGHTGRAY);
}

void PrintCustomText(const char *text, int posX, int posY, int fontSize, Color color) {
    if (!text) return;
    // Drop shadow for readability
    DrawText(text, posX + 1, posY + 1, fontSize, BLACK);
    DrawText(text, posX, posY, fontSize, color);
}

void CheckPrintScreen(void) {
    if (IsKeyPressed(KEY_P) || IsKeyPressed(KEY_F12) || IsKeyPressed(KEY_PRINT_SCREEN)) {
        TakeScreenshot("screenshot.png");
    }
}

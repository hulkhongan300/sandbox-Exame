#include "raylib.h"
#include "screen_print.h"
#include <math.h>
#include <stdbool.h>
#include <time.h>

#define NUM_BOXES 100
#define BOX_SIZE  25.0f

typedef struct {
    Vector2 pos;
    Vector2 vel;   // pixels per second
    Color   color;
} Box;

static float RandomSpeed(void) { return (float)GetRandomValue(120, 300); }

// Start the four boxes in a tight 2x2 block at the center, each flying
// toward its own corner at a random speed.
// Place every box at a random free spot with a random direction and speed.
static void ResetBoxes(Box boxes[]) {
    const Color palette[] = {
        LIGHTGRAY, GRAY, DARKGRAY,
        YELLOW, GOLD, ORANGE,
        PINK, RED, MAROON,
        GREEN, LIME, DARKGREEN,
        SKYBLUE, BLUE, DARKBLUE,
        PURPLE, VIOLET, DARKPURPLE,
        BEIGE, BROWN, DARKBROWN,
        WHITE, BLACK, MAGENTA, RAYWHITE
    };
    const int paletteSize = sizeof(palette) / sizeof(palette[0]);

    int maxX = GetScreenWidth()  - (int)BOX_SIZE;
    int maxY = GetScreenHeight() - (int)BOX_SIZE;
    if (maxX < 0) maxX = 0;
    if (maxY < 0) maxY = 0;

    for (int i = 0; i < NUM_BOXES; i++) {
        // try up to 200 random spots that don't overlap boxes already placed
        for (int attempt = 0; attempt < 200; attempt++) {
            boxes[i].pos.x = (float)GetRandomValue(0, maxX);
            boxes[i].pos.y = (float)GetRandomValue(0, maxY);

            Rectangle r = { boxes[i].pos.x, boxes[i].pos.y, BOX_SIZE, BOX_SIZE };
            bool freeSpot = true;
            for (int j = 0; j < i; j++) {
                Rectangle o = { boxes[j].pos.x, boxes[j].pos.y, BOX_SIZE, BOX_SIZE };
                if (CheckCollisionRecs(r, o)) { freeSpot = false; break; }
            }
            if (freeSpot) break;
        }

        float sx = GetRandomValue(0, 1) ? 1.0f : -1.0f;
        float sy = GetRandomValue(0, 1) ? 1.0f : -1.0f;
        boxes[i].vel   = (Vector2){ sx * RandomSpeed(), sy * RandomSpeed() };
        boxes[i].color = palette[i % paletteSize];   // cycles through the palette
    }
}

// Returns true if the two boxes were overlapping.
static bool CollideBoxes(Box *a, Box *b) {
    Rectangle ra = { a->pos.x, a->pos.y, BOX_SIZE, BOX_SIZE };
    Rectangle rb = { b->pos.x, b->pos.y, BOX_SIZE, BOX_SIZE };
    if (!CheckCollisionRecs(ra, rb)) return false;

    // the overlapping area tells us which side they hit on
    Rectangle o = GetCollisionRec(ra, rb);

    if (o.width < o.height) {
        // side hit: push apart on x, swap x velocities
        float n = (a->pos.x < b->pos.x) ? 1.0f : -1.0f;   // direction a -> b
        a->pos.x -= n * o.width / 2.0f;
        b->pos.x += n * o.width / 2.0f;
        if ((a->vel.x - b->vel.x) * n > 0) {              // only if approaching
            float t = a->vel.x; a->vel.x = b->vel.x; b->vel.x = t;
        }
    } else {
        // top/bottom hit: push apart on y, swap y velocities
        float n = (a->pos.y < b->pos.y) ? 1.0f : -1.0f;
        a->pos.y -= n * o.height / 2.0f;
        b->pos.y += n * o.height / 2.0f;
        if ((a->vel.y - b->vel.y) * n > 0) {
            float t = a->vel.y; a->vel.y = b->vel.y; b->vel.y = t;
        }
    }
    return true;
}

int main(void) {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(800, 600, "hello from raylib");
    SetRandomSeed((unsigned int)time(NULL));

    Box boxes[NUM_BOXES];
    ResetBoxes(boxes);
    Color bg = RAYWHITE;

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        int w = GetScreenWidth();
        int h = GetScreenHeight();

        if (IsKeyPressed(KEY_R)) {
            ResetBoxes(boxes);
            bg = RAYWHITE;
        }

        CheckPrintScreen();

        // 1) move
        for (int i = 0; i < NUM_BOXES; i++) {
            boxes[i].pos.x += boxes[i].vel.x * dt;
            boxes[i].pos.y += boxes[i].vel.y * dt;
        }

        // 2) box vs box (every pair once)
        for (int i = 0; i < NUM_BOXES; i++)
            for (int j = i + 1; j < NUM_BOXES; j++)
                CollideBoxes(&boxes[i], &boxes[j]);


        // 3) box vs walls
        for (int i = 0; i < NUM_BOXES; i++) {
            Box *b = &boxes[i];
            if (b->pos.x + BOX_SIZE >= w) { b->pos.x = w - BOX_SIZE; b->vel.x = -fabsf(b->vel.x);}
            else if (b->pos.x <= 0)       { b->pos.x = 0;            b->vel.x =  fabsf(b->vel.x);}
            if (b->pos.y + BOX_SIZE >= h) { b->pos.y = h - BOX_SIZE; b->vel.y = -fabsf(b->vel.y);}
            else if (b->pos.y <= 0)       { b->pos.y = 0;            b->vel.y =  fabsf(b->vel.y);}
        }

        // 4) draw
        BeginDrawing();
        ClearBackground(bg);
        for (int i = 0; i < NUM_BOXES; i++)
            DrawRectangle((int)boxes[i].pos.x, (int)boxes[i].pos.y,
                          (int)BOX_SIZE, (int)BOX_SIZE, boxes[i].color);

        PrintToScreen(NUM_BOXES);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

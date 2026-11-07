#define NOB_IMPLEMENTATION
#define NOB_STRIP_PREFIX
#include "nob.h"



// gcc main.c -o main \
//   -I raylib/build-wayland/include \
//   -L raylib/build-wayland/raylib \
//   -lraylib -lGL -lm -lpthread -ldl -lrt \
//   -lwayland-client -lwayland-cursor -lwayland-egl -lxkbcommon

static Cmd cmd = {0};
static void compile(void){
  cmd_append(&cmd, "gcc", "main.c", "screen_print.c");
  cmd_append(&cmd, "-o", "main");
  cmd_append(&cmd, "-I", "raylib/build-wayland/include");
  cmd_append(&cmd, "-L", "raylib/build-wayland/raylib");
  cmd_append(&cmd, "-lraylib", "-lGL", "-lm", "-lpthread", "-ldl", "-lrt");
  cmd_append(&cmd, "-lwayland-client", "-lwayland-cursor", "-lwayland-egl", "-lxkbcommon");
}

int main(int argc, char** argv){
    NOB_GO_REBUILD_URSELF(argc, argv);
    compile();
    if(!cmd_run(&cmd)) return 1;
    return 0;
}

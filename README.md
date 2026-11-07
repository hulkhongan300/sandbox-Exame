sudo cmake --install raylib/build-wayland
make clean
make PLATFORM=PLATFORM_DESKTOP GLFW_LINUX_ENABLE_WAYLAND=TRUE GLFW_LINUX_ENABLE_X11=FALSE


gcc main.c screen_print.c -o main \
  -I raylib/build-wayland/include \
  -L raylib/build-wayland/raylib \
  -lraylib -lGL -lm -lpthread -ldl -lrt \
  -lwayland-client -lwayland-cursor -lwayland-egl -lxkbcommon

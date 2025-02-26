#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <glad/glad.h>
#include <SDL.h>
#include <SDL_opengl.h>
#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_sdl2.h>

namespace Gui {
    bool initialize();
    void update();
    void finish();
    bool is_focused();

    extern SDL_Window* window;
    extern bool done;
    extern int current_item;
}
#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace Gui {
    void initialize();
    void update();
    void finish();
    bool is_focused();
    extern  GLFWwindow* window;
}
#include <stdio.h>
#include <string>
#include <chrono>
#include <thread>

#include "input/input.hpp"
#include "config/config.hpp"
#include "gui/gui.hpp"

int main() {

    // create a new thread to input event loop
    std::thread input_thread(Input::initialize);

    Config::initialize();
    Gui::initialize();
    
    while (true) {
        Gui::update();
        Autoclick::update();
    }

    Gui::finish();

    input_thread.join();
    
    return 0;
}
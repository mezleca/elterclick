#include <stdio.h>
#include <string>
#include <chrono>
#include <thread>

#include "input/input.hpp"
#include "config/config.hpp"

int main() {

    // create a new thread to input event loop
    std::thread input_thread(Input::initialize);

    // config yep
    Config::initialize();
    
    while (true) {
        Autoclick::update();
    }

    input_thread.join();
    
    return 0;
}
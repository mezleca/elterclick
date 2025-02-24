#include <stdio.h>
#include <string>
#include <chrono>
#include <thread>

#include "input/input.hpp"

int main() {

    // xorg and shit initialization
    Input::initialize();
    
    while (true) {

        if (Input::is_pressing_key(Input::KeyList::MOUSE5)) {
            printf("Pressing mouse5\n");
            continue;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    Input::free_input();
    
    return 0;
}
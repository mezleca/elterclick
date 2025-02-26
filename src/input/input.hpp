#pragma once

#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <chrono>
#include <thread>
#include <string>
#include <string.h>
#include <unordered_set>
#include <X11/Xlib.h>

enum KeyList {
    INVALID = -1,
    NOT_SET, // uuh, surely it starts with index 1 right
    LEFT = 1,
    MIDDLE,
    RIGHT,
    MOUSE4 = 8,
    MOUSE5
};

namespace Autoclick {
    void update();
}

namespace Input {
    void initialize();
    void click(KeyList vKey);
    bool is_pressing_key(KeyList vKey);

    std::string to_string(KeyList vKey);

    extern std::unordered_set<KeyList> keys;
    extern Display* XDisplay;
}
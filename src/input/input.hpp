#pragma once

#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <chrono>
#include <thread>
#include <string>
#include <string.h>
#include <dirent.h>
#include <unordered_set>
#include <X11/Xlib.h>
#include <libevdev-1.0/libevdev/libevdev.h>

enum KeyList {
    INVALID = -1,
    LEFT = 1,
    MIDDLE,
    RIGHT,
    MOUSE4 = 8,
    MOUSE5
};

namespace Input {

    void initialize();
    void click(KeyList vKey);
    void free_input();
    void update_event();
    bool is_pressing_key(KeyList vKey);
    std::string mouse_lookup();

    extern std::unordered_set<KeyList> keys;
    extern Display* XDisplay;
    extern libevdev *dev;
    extern int xi_op_code;
}
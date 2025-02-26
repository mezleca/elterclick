#pragma once

#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <fcntl.h>
#include <json/json.h>

#include "../input/input.hpp"

struct KeyData {
    KeyList trigger = KeyList::MOUSE5;
    KeyList target = KeyList::LEFT;
    int cps = 12;
};

struct ConfigData {
    std::vector<KeyData> keys;    
    bool randomized = false;
} inline config;

namespace Config {
    void initialize();
    bool save();
}
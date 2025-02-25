#include <stdio.h>
#include <string>
#include <chrono>
#include <thread>

#include "input/input.hpp"
#include "config/config.hpp"

int main() {

    using clock = std::chrono::steady_clock;
    using duration = std::chrono::milliseconds;

    // xorg and shit initialization
    Input::initialize();

    // config yep
    Config::initialize();
    
    // start auto click logic 
    // @TODO: move this to somewhere else
    // @TODO: a way to make 2 keys at time work
    while (true) {

        // next event
        Input::update_event();
        
        auto start = clock::now();

        // check if theres something being pressed
        if (config.keys.empty()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            continue;
        }

        for (const KeyData& key : config.keys) {
            
            if (!Input::is_pressing_key(key.trigger)) {
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
                continue;
            }

            Input::click(key.target);

            auto target_delay = 1000 / key.cps;

            if (config.randomized) {
                target_delay += rand() % (key.cps / 2);
            }

            auto elapsed = std::chrono::duration_cast<duration>(clock::now() - start).count();
            int delay = static_cast<int>(target_delay - elapsed - 5);

            std::this_thread::sleep_for(std::chrono::milliseconds(
                static_cast<int>(delay)
            ));
        }
    }

    Input::free_input();
    
    return 0;
}
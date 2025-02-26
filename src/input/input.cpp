#include "input.hpp"
#include <X11/extensions/XInput2.h>
#include <X11/extensions/XTest.h>
#include <fcntl.h>
#include <src/config/config.hpp>
#include <src/gui/gui.hpp>

namespace Input {

    Display* XDisplay = NULL;
    std::unordered_set<KeyList> keys;

    void initialize() {
        
        // could pass NULL but yeah
        std::string name = std::getenv("DISPLAY");
        XDisplay = XOpenDisplay(name.c_str());

        if (XDisplay == NULL) {
            printf("failed to get display\n");
            return;
        }

        int event_code, error, xi_op_code;

        if (!XQueryExtension(XDisplay, "XInputExtension", &xi_op_code, &event_code, &error)) {
            fprintf(stderr, "xinput not available\n");
            return;
        }

        // capture from the root window instead of a normal window
        Window root_window = DefaultRootWindow(XDisplay);

        // create mask buffer
        XIEventMask mask;

        // set the mask shit
        mask.deviceid = XIAllMasterDevices;
        mask.mask_len = XIMaskLen(XI_LASTEVENT);
        mask.mask = static_cast<unsigned char *>(calloc(mask.mask_len, sizeof(char)));

        // apply mask and select events
        XISetMask(mask.mask, XI_RawButtonPress);
        XISetMask(mask.mask, XI_RawButtonRelease);
        XISelectEvents(XDisplay, root_window, &mask, 1);

        XSync(XDisplay, 0);
        free(mask.mask);

        while(!Gui::done) {
            
            if (XPending(XDisplay) == 0) {
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
                continue;
            }
    
            // get current event
            XEvent event;
            XNextEvent(XDisplay, &event);
    
            if (event.type == GenericEvent && event.xcookie.extension == xi_op_code) {
    
                if (XGetEventData(XDisplay, &event.xcookie)) {
    
                    XIRawEvent* raw_event = (XIRawEvent*)event.xcookie.data;
    
                    // erm what the sigma
                    if (raw_event->detail > KeyList::MOUSE5) {
                        printf("yep: %i\n", raw_event->type);
                        continue;
                    }

                    KeyList key_value = (KeyList)raw_event->detail;
                    
                    if (raw_event->evtype == XI_RawButtonPress) {
                        keys.insert(key_value);
                    }
                    else if (raw_event->evtype == XI_RawButtonRelease) {
                        keys.erase(key_value);
                    }
                }
                
                XFreeEventData(XDisplay, &event.xcookie);
            }
        }

        XCloseDisplay(XDisplay);
    }

    void click(KeyList vKey) {

        if (XDisplay == NULL) {
            printf("failed to get display\n");
            return;
        }

        XTestFakeButtonEvent(XDisplay, (int)vKey, true, CurrentTime);
        XFlush(XDisplay);
        XTestFakeButtonEvent(XDisplay, (int)vKey, false, CurrentTime);
        XFlush(XDisplay);
    }

    bool is_pressing_key(KeyList vKey) {

        // check if the key map includes the vKey (pressed)
        if (keys.find(vKey) != keys.end()) {
            return true;
        }

        return false;
    }
}

namespace Autoclick {

    void update() {

        using clock = std::chrono::steady_clock;
        using duration = std::chrono::milliseconds;    
     
        auto start = clock::now();

        // only simulate input if the window is not focused
        if (Gui::is_focused()) {
            return;
        }

        // if the user is not pressing anything, sleep for 10ms
        if (config.keys.empty()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            return;
        }

        // loop through all keys and simulate input it needed
        for (const KeyData& key : config.keys) {
            
            if (!Input::is_pressing_key(key.trigger)) {
                continue;
            }

            Input::click(key.target);

            auto target_delay = 1000 / key.cps;

            // @TODO: variation percentage
            if (config.randomized) {
                int variation = target_delay * 0.30;
                target_delay += rand() % variation;
            }

            auto elapsed = std::chrono::duration_cast<duration>(clock::now() - start).count();
            int delay = static_cast<int>(target_delay - elapsed);

            std::this_thread::sleep_for(std::chrono::milliseconds(
                static_cast<int>(delay)
            ));
        }
    }
}
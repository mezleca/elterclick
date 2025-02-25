#include "config.hpp"
#include <regex>
#include <json/json.h>

std::string default_config_content =
R"({
    "keys": [
        {
            "trigger": 9,
            "target": 1,
            "cps": 14
        }
    ],
    "randomized": false
}
)";

namespace Config {

    void initialize() {
        
        std::ifstream config_file("config.json");
        KeyData default_key;

        // check if the config file exists, if not create a placeholder one
        if (!config_file.is_open()) {

            printf("creating new config\n");

            std::ofstream new_config("./config.json");
            new_config << default_config_content;
            config.keys.push_back(default_key);
        }

        Json::Value root;
        Json::CharReaderBuilder builder;
        builder["collectComments"] = false;
        std::string errs;

        bool ok = Json::parseFromStream(builder, config_file, &root, &errs);

        if (!ok) {
            printf("failed to parse config file\nmake sure the json file is valid\n");
            return;
        }

        // make sure randomized exists
        if (!root["randomized"].empty()) {
            config.randomized = root["randomized"].asBool();
        }

        const Json::Value& keys = root["keys"];

        // make sure is a valid array
        if (!keys.isArray()) {
            printf("failed to get keys array\nusing the default one\n");
            config.keys.push_back(default_key);
            return;
        }

        // add the keys to the config struct
        for (unsigned int i = 0; i < keys.size(); i++) {
            
            const Json::Value key = keys[i];

            if (!key.isMember("trigger") || !key.isMember("target")) {
                printf("invalid schema for key %i\n", i);
                continue;
            }

            int trigger_keycode = key["trigger"].asInt();
            int target_keycode  = key["target"].asInt();

            if (trigger_keycode > KeyList::MOUSE5 || target_keycode > KeyList::MOUSE5) {
                printf("Invalid keycode for key %i\n", i);
                continue;
            }
            
            printf("[%i] trigger: %i | target: %i\n", i, trigger_keycode, target_keycode);

            config.keys.push_back({
                trigger: (KeyList)trigger_keycode,
                target: (KeyList)target_keycode
            });
        }

        printf("intialized config\n");
    }
}
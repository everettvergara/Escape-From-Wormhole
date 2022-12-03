#include <iostream>
#include <string>
#include "game/engine/config.hpp"
#include "game/worm/demo.hpp"

// TODO: Palette, should have an implementation of for_each and increment.

auto main(int argc, char *argv[]) -> int {

    using namespace g80::game::engine;
    using namespace g80::game::worm;


    // Retrieve configuration from file 
    std::string title{"Escape from the Wormhole"};
    config c{title};

    // Initialize SDL
    video::init();
    
    // Game / Demo Proper 
    demo worm;
    worm.create_window(c); 
    worm.run(c.get_MSPF());
    
    // DeInitialize SDL
    video::quit();

    return 0;
}


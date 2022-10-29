#include <iostream>
#include <SDL.h>
#include "video/config.hpp"
#include "video/video.hpp"

auto main(int argc, char *argv[]) -> int {

    using namespace g80::video;

    video::init();
    
    video worm(config{"Escape From Wormhole Demo"});

    video::quit();

    return 0;
}
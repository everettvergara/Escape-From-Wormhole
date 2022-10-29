#include <iostream>
#include <SDL.h>
#include "video/config.hpp"
#include "video/video.hpp"

auto main(int argc, char *argv[]) -> int {

    using namespace g80::video;

    video::init();
    
    config cfg{"Escape From Wormhole Demo"};
    video worm;

    video::quit();

    return 0;
}
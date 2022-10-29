#include <iostream>
#include <SDL.h>
#include "video/config.hpp"
#include "video/video.hpp"

auto main(int argc, char *argv[]) -> int {

    using namespace g80::video;

    video::init();
    
    config cfg{
        .title{"Escape From Wormhole"},
        .x{SDL_WINDOWPOS_CENTERED},
        .y{SDL_WINDOWPOS_CENTERED},
        .w{1280},
        .h{720},
        .flags{SDL_WINDOW_SHOWN},
        .FPS{60}};

    video worm;

    video::quit();

    return 0;
}
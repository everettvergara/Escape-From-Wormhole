#include <iostream>

#include "VideoConfig.h"
#include "Demo.hpp"
#include "Bezier.hpp"

using namespace g80;

auto set_default_video_config() -> VideoConfig;

auto main(int argc, const char *argv[]) -> int {
    VideoConfig video_config = set_default_video_config();
    Demo demo;
    demo.create_window(video_config);
    demo.run();

}

auto set_default_video_config() -> VideoConfig {
    VideoConfig vconfig {
        "Bezier Curves",
        // {SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600},
        {SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720},
        // {SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080},
        // {SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 2560, 1600},
        SDL_WINDOW_SHOWN,
        60
    }; 
    return vconfig;
}

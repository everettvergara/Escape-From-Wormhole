#include <iostream>

#include "VideoConfig.h"
#include "Demo.hpp"
#include "TrigCache.hpp"

using namespace g80;

auto set_default_video_config() -> VideoConfig;
auto main(int argc, const char *argv[]) -> int {

    //SinCacheF sinef(SinCacheF (360));
    //TrigCache<float> sinef(std::move(TrigCache<float>(360)));
    // SinCache sined(SinCache(360));



    // VideoConfig video_config = set_default_video_config();
    // Demo demo(30000, 800.0f);
    // demo.create_window(video_config);
    // demo.preprocess_states();
    // demo.run();
}

auto set_default_video_config() -> VideoConfig {
    VideoConfig vconfig {
        "Escape from The Wormhole",
        // {SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600},
        {SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720},
        // {SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080},
        // {SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 2560, 1600},
        SDL_WINDOW_SHOWN,
        5000
    }; 
    return vconfig;
}


// tODO: Remove two - phase construction of motion
#include "Demo/CircleMotionDemo.hpp"
#include "Demo/LineMotionDemo.hpp"
#include "Palette.hpp"

using namespace g80;

auto set_default_video_config() -> VideoConfig;
auto main(int argc, const char *argv[]) -> int {

    VideoConfig video_config = set_default_video_config();
    CircleMotionDemo demo;

    demo.create_window(video_config);
    demo.preprocess_states(); 
    demo.run(); 
}

auto set_default_video_config() -> VideoConfig { 
    VideoConfig video_config { 
        "Escape from The Wormhole",
        {SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720},
        SDL_WINDOW_SHOWN,
        30
    }; 
    return video_config;
}


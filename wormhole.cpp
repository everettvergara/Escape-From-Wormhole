
#include "LineMotionDemo.hpp"


using namespace g80;

auto set_default_video_config() -> VideoConfig;

auto main(int argc, const char *argv[]) -> int {

    // LineMotion<float> line_motion({10.0f, 10.0f}, {1000.0f, 500.0f}, 10, 1);
 
    VideoConfig video_config = set_default_video_config();
    LineMotionDemo demo;

    demo.create_window(video_config);
    demo.preprocess_states();
    demo.run();
}

auto set_default_video_config() -> VideoConfig { 
    VideoConfig video_config { 
        "Escape from The Wormhole",
        {SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720},
        SDL_WINDOW_SHOWN,
        60
    }; 
    return video_config;
}


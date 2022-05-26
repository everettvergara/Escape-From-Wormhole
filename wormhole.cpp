
#include <iostream>
#include "QuadBezierMotionDemo.hpp"
#include "PriorityList.hpp"

// 3d in 2d graphics

// TODO: Add Ellipse in Video
// TODO: Add Rectangle in Video
// TODO: Add Fade effect in Video
// TODO: Add fill in video
// TODO: Add fill  

using namespace g80;

auto set_default_video_config() -> VideoConfig;
auto main(int argc, const char *argv[]) -> int {

    PriorityList pl(100, 1000);

    // VideoConfig video_config = set_default_video_config();
    // QuadBezierMotionDemo demo;

    // demo.create_window(video_config);
    // demo.preprocess_states(); 
    // demo.run(); 
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


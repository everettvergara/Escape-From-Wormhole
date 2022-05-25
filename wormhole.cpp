
#include <iostream>
// tODO: Remove two - phase construction of motion
#include "Demo/LissajousMotionDemo.hpp"
#include "Palette.hpp"

// Lissajous Motion
// QuadBezier Motion
// Cubic Motion 
// Catmulrom Motion

// 3d in 2d graphics

// TODO: Add Ellipse in Video
// TODO: Add Rectangle in Video
// TODO: Add Fade effect in Video
// TODO: Add fill in video
// TODO: Add fill  

using namespace g80;

auto set_default_video_config() -> VideoConfig;
auto main(int argc, const char *argv[]) -> int {

    VideoConfig video_config = set_default_video_config();
    LissajousMotionDemo demo;

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


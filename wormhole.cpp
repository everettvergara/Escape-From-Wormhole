
#include <iostream>
// tODO: Remove two - phase construction of motion
#include "Demo/CircleWithAccelMotionDemo.hpp"
#include "Demo/LineMotionDemo.hpp"
#include "Palette.hpp"
#include "LCMRND.hpp"

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
    CircleWithAccelMotionDemo demo;

    demo.create_window(video_config);
    demo.preprocess_states(); 
    demo.run(); 
}

auto set_default_video_config() -> VideoConfig { 
    VideoConfig video_config { 
        "Escape from The Wormhole",
        {SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720},
        SDL_WINDOW_SHOWN,
        120
    }; 
    return video_config;
}


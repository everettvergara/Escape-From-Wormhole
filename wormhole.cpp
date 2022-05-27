
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

    PriorityList pl(3, 5);
    pl.debug();
    pl.add(0, 0);
    pl.add(0, 2);
    pl.add(0, 4);
    
    auto group = 0;
    auto cur = pl.get_next_after(group);
    while (cur != pl.get_tail_group_ix(group)) {
        std::cout << cur << "\n";
    }
    
// //    pl.add(0, 0);


//     // pl.add(0, 4);

//     pl.debug();
    
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
        60
    }; 
    return video_config;
}



#include "CircleDemo.hpp"
#include "Palette.hpp"

// TODO: Fix Palette Bug;
using namespace g80;

auto set_default_video_config() -> VideoConfig;

auto main(int argc, const char *argv[]) -> int {


    VideoConfig video_config = set_default_video_config();
    CircleDemo demo;

    demo.create_window(video_config);

    Palette pal;

    pal[0] = 255;

    // pal.add_gradients(
    //     demo.get_surface()->format, 
    //     {
    //         {0, SDL_MapRGBA(demo.get_surface()->format, 0, 0, 0, 0)},
    //         {3, SDL_MapRGBA(demo.get_surface()->format, 100, 100, 100, 100)},
    //         {10, SDL_MapRGBA(demo.get_surface()->format, 200, 200, 200, 200)},

    //     });    
    
    // Uint8 r,g,b,a;
    // SDL_GetRGBA(pal[0], demo.get_surface()->format, &r, &g, &b, &a);
    // SDL_Log("0: r:%d, g:%d, b:%d, a:%d", r, g, b, a);
    
    // SDL_GetRGBA(pal[1], demo.get_surface()->format, &r, &g, &b, &a);
    // SDL_Log("1: r:%d, g:%d, b:%d, a:%d", r, g, b, a);
    
    // SDL_GetRGBA(pal[2], demo.get_surface()->format, &r, &g, &b, &a);
    // SDL_Log("2: r:%d, g:%d, b:%d, a:%d", r, g, b, a);
    
    // SDL_GetRGBA(pal[3], demo.get_surface()->format, &r, &g, &b, &a);
    // SDL_Log("3: r:%d, g:%d, b:%d, a:%d", r, g, b, a);
    
    // SDL_GetRGBA(pal[4], demo.get_surface()->format, &r, &g, &b, &a);
    // SDL_Log("4: r:%d, g:%d, b:%d, a:%d", r, g, b, a);

    // SDL_GetRGBA(pal[5], demo.get_surface()->format, &r, &g, &b, &a);
    // SDL_Log("5: r:%d, g:%d, b:%d, a:%d", r, g, b, a);

    // SDL_GetRGBA(pal[10], demo.get_surface()->format, &r, &g, &b, &a);
    // SDL_Log("5: r:%d, g:%d, b:%d, a:%d", r, g, b, a);

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


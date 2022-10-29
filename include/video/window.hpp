#pragma once

#include <SDL.h>
#include "sys/common.hpp"
#include "base_point.hpp"
#include "config.hpp"

namespace g80::video {

    class window {

    // Constructors, Destructors and Assignments
    private:
        SDL_Window *window_;
        Uint16 MSPF_;

    public:
        // Add throw if 0
        window(const config &c) : 
            window_(SDL_CreateWindow(c.title.c_str(), c.x, c.y, c.w, c.h, c.flags))
        {
            
        }
    };

    bool video::is_init_{false};
}
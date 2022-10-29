#pragma once

#include <SDL.h>
#include <string>
#include "sys/common.hpp"

namespace g80::video {

    struct config {
        std::string title;
        int x, y, w, h;
        Uint32 flags;
        Uint16 FPS{60};

        config(config &&r) :
            title{std::move(r.title)}, 
            x{r.x}, y{r.y}, w{r.w}, h{r.h},
            flags{r.flags}, FPS{r.FPS} {
        }
    };


}
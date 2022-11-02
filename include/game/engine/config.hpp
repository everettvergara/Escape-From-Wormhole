#pragma once

#include <SDL.h>
#include <string>
#include "sys/common.hpp"

namespace g80::game::engine {

    struct config {
        std::string title;
        int x, y, w, h;
        Uint32 back_rgba;
        Uint32 flags;
        Uint16 FPS;
        Uint16 MSPF;

        config(std::string title, int x = SDL_WINDOWPOS_CENTERED, int y = SDL_WINDOWPOS_CENTERED, int w = 1280, int h = 720, Uint32 back_rgba = 0, Uint32 flags = SDL_WINDOW_SHOWN, Uint16 FPS = 60) :
            title{std::move(title)}, 
            x{x}, y{y}, w{w}, h{h},
            flags{flags}, FPS{FPS}, 
            MSPF{static_cast<Uint16>(static_cast<Uint16>(1000) / FPS)} {
        }

        // config(config &&r) :
        //     title{std::move(r.title)}, 
        //     x{r.x}, y{r.y}, w{r.w}, h{r.h},
        //     flags{r.flags}, FPS{r.FPS}, MSPF{r.MSPF} {
        // }
    };


}
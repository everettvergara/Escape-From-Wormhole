#pragma once

#include <SDL.h>
#include "game/gfx/common.hpp"

namespace g80::game::gfx {

    using namespace g80::sys;

    class gfx {
    private:
        SDL_Surface *s_;
    public:
        gfx(SDL_Surface *s) : s_(s) {}
        auto set_surface(SDL_Surface *s) -> void {s_ = s;}
    };

}
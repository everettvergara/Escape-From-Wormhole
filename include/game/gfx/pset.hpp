#pragma once

#include <SDL.h>
#include "game/gfx/common.hpp"


namespace g80::game::gfx {

    using namespace g80::sys;

    inline auto pset(SDL_Surface *s, const point &p, const uint_type rgba) -> void {
        *((static_cast<uint_type *>(s->pixels) + p.x) + (p.y * s->w)) = rgba;
    }
    
    inline auto pset(SDL_Surface *s, const uint_type x, const uint_type y, const uint_type rgba) -> void {
        *((static_cast<uint_type *>(s->pixels) + x) + (y * s->w)) = rgba;
    }

}
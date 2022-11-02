#pragma once

#include <SDL.h>
#include "game/gfx/common.hpp"

namespace g80::game::gfx {

    using namespace g80::sys;

    inline auto pset(SDL_Surface *s, const int_type x, const int_type y, const uint_type rgba) -> void {
        RETURN_IF_NOT_WITHIN_BOUNDS(x, y, s->w, s->h);
        *((static_cast<uint_type *>(s->pixels) + x) + (y * s->w)) = rgba;
    }


}
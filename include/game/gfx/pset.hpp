#pragma once

#include <SDL.h>
#include "game/gfx/common.hpp"
#include "game/gfx/gfx.hpp"

namespace g80::game::gfx {

    using namespace g80::sys;

    class pset : public gfx {
    public:
        auto draw(const uint_type x, const uint_type y, const uint_type rgba) -> void {
            if(!is_point_within_bounds(x, y)) [[unlikely]] return;
            *((static_cast<uint_type *>(get_surface()->pixels) + x) + (y * get_surface()->w)) = rgba;
        }
    };


}
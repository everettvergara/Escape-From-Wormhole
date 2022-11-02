#pragma once

#include <SDL.h>
#include "sys/common.hpp"
#include "game/gfx/base_point.hpp"

namespace g80::game::gfx {

    using g80::sys::int_type;
    using g80::sys::uint_type;
    using point = base_point<int_type>;

    inline auto within_bounds(const int_type x, const int_type y, const uint_type w, const uint_type h) -> bool {
        if(x < 0 || y < 0 || x >= w || y >= h) return false;
        return true;
    }
}
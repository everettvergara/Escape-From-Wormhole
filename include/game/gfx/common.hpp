#pragma once

#include <SDL.h>
#include "sys/common.hpp"
#include "game/gfx/base_point.hpp"

namespace g80::game::gfx {

    using g80::sys::int_type;
    using g80::sys::fp_type;
    using point = base_point<int_type>;

    inline auto is_point_within_bounds(const int_type x, const int_type y, const int_type w, const int_type h) -> bool {
        if(x < 0 || y < 0 || x >= w || y >= h) return false; 
        return true;
    }


}
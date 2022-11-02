#pragma once

#include <SDL.h>
#include "sys/common.hpp"
#include "game/gfx/base_point.hpp"

namespace g80::game::gfx {

    using g80::sys::uint_type;
    using point = base_point<uint_type>;
    inline auto pixel_ix(const uint_type x, const uint_type y, const uint_type w) -> uint_type {return y * w + x;}
}
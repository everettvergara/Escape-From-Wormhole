#pragma once

#include <SDL.h>
#include "game/engine/base_point.hpp"

namespace g80::game::engine {
    using int_type  = Sint32;
    using uint_type = Uint32;
    using fp_type   = float;
    using point = base_point<int_type>;

}
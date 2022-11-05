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
        inline auto set_surface(SDL_Surface *s) -> void {s_ = s;}
        inline auto get_surface() const -> SDL_Surface * {return s_;}
        inline auto is_point_within_bounds(const int_type x, const int_type y) const -> bool {
            if(x < 0 || y < 0 || x >= s_->w || y >= s_->h) return false; 
            return true;
        }
    };

}
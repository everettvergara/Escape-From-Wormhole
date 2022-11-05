#pragma once

#include <iostream>
#include <SDL.h>
#include "game/gfx/common.hpp"

namespace g80::game::gfx {

    using namespace g80::sys;

    class gfx {
    private:
        SDL_Surface *s_{nullptr};
        int_type wb_, hb_;
    public:
        inline auto set_surface(SDL_Surface *s) -> void {s_ = s; wb_ = s_->w - 1; hb_ = s_->h - 1;}
        inline auto get_surface() const -> SDL_Surface * {return s_;}
        inline auto get_wb() const -> int_type {return wb_;}
        inline auto get_hb() const -> int_type {return hb_;}
        inline auto is_point_within_bounds(const int_type x, const int_type y) const -> bool {
            if(x < 0 || y < 0 || x >= s_->w || y >= s_->h) return false; 
            return true;
        }
    };

}
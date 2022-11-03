#pragma once

#include <tuple>
#include <SDL.h>
#include "game/gfx/common.hpp"

namespace g80::game::gfx {

    enum SCREEN_PLANE{TOP_LEFT = 0, TOP = 1, TOP_RIGHT = 2, LEFT = 3, ON_SCREEN = 4, RIGHT = 5, BOTTOM_LEFT = 6, BOTTOM = 7, BOTTOM_RIGHT = 8};

    auto get_screen_plane(SDL_Surface *s, const int_type x, const int_type y) -> SCREEN_PLANE {
        if(x >= 0) [[likely]] {
            if(x < s->w) [[likely]] {
                if(y >= 0) [[likely]] {
                    if(y < s->h) [[likely]] return ON_SCREEN;
                    else return BOTTOM;
                } else return TOP;
            } else {
                if(y < 0) return TOP_RIGHT;
                else if(y >= s->h) return BOTTOM_RIGHT;
                else return RIGHT;
            }
        } else {
            if(y < 0) return TOP_LEFT;
            else if(y >= s->h) return BOTTOM_LEFT;
            else return LEFT;
        }
    }

    auto get_point_on_xintercept(int_type x, int_type y, int_type w, fp_type m) -> std::tuple<int_type, int_type> {
        if(w == 0) return {x, y};
        fp_type b = y - m * x;
        return {(y - b) / m, y};
    }

    auto line_recalc_points(SDL_Surface *s, int_type &x1, int_type &y1, int_type &x2, int_type &y2) -> void {
    
        int_type h = y2 - y1;
        int_type w = x2 - x1;
        fp_type m = static_cast<fp_type>(1.0) * h / w;

    }

    auto line(SDL_Surface *s, const int_type x1, const int_type y1, const int_type x2, const int_type y2, const Uint32 rgba) -> void {
    
    }

}
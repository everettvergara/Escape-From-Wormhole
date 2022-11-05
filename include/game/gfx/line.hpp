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

    auto line_recalc_points(SDL_Surface *s, int_type &x1, int_type &y1, int_type &x2, int_type &y2) -> void {
    
        fp_type h = y2 - y1;
        fp_type w = x2 - x1;
        // fp_type m = h / w;

        auto get_x_at_y_equals = [&](const int_type x, const int_type y, const int_type y_equals) -> int_type {
            if(w == 0) return x;
            fp_type m = h / w;
            fp_type b = y - m * x;
            return static_cast<int_type>((y - b) / m);
        };

        auto get_y_at_x_equals = [&](const int_type x, const int_type y, const int_type x_equals) -> int_type {
        
        };

    }

    auto line(SDL_Surface *s, int_type x1, int_type y1, int_type x2, int_type y2, const Uint32 rgba) -> void {
        bool is_p1_within_bounds = is_point_within_bounds(x1, y1, s->w, s->h);
        bool is_p2_within_bounds = is_point_within_bounds(x2, y2, s->w, s->h);





    }

}
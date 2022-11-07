#pragma once

#include <cstdint>
#include <unordered_set>
#include <SDL.h>
#include <chrono>
#include "game/gfx/common.hpp"

namespace g80::game::gfx {



    auto line(SDL_Surface *s, int_type x1, int_type y1, int_type x2, int_type y2, const Uint32 rgba) -> void {
        auto sp1 = get_screen_plane(s, x1, y1);
        auto sp2 = get_screen_plane(s, x2, y2);
        if(sp1 != ON_SCREEN || sp2 != ON_SCREEN) [[unlikely]] 
             if(!recalc_line_points(s, x1, y1, x2, y2, sp1, sp2)) return;

        int_type dx = x2 - x1;
        int_type dy = y2 - y1;
        int_type adx = dx < 0 ? -dx : dx;
        int_type ady = dy < 0 ? -dy : dy;
        int_type sdx = dx < 0 ? -1 : 1;
        int_type sdy = dy < 0 ? -s->w : s->w;

        Uint32 *pixel_buffer = static_cast<Uint32 *>(s->pixels) + y1 * s->w + x1;
        auto draw_line = [&](int_type abs_g, int_type abs_l, int_type sig_g, int_type sig_l) -> void {
            for (int_type i = 0, t = abs_l; i <= abs_g; ++i, t += abs_l) {
                *pixel_buffer = rgba;
                if (t >= abs_g) {
                    pixel_buffer += sig_l;
                    t -= abs_g;
                }
                pixel_buffer += sig_g;
            }
        };

        if (adx >= ady) draw_line(adx, ady, sdx, sdy);
        else draw_line(ady, adx, sdy, sdx);
    }
}
#pragma once

#include <cstdint>
#include <unordered_set>
#include <SDL.h>
#include <chrono>
#include "game/gfx/common.hpp"

namespace g80::game::gfx {

    enum SCREEN_PLANE{TOP_LEFT = 0, TOP = 1, TOP_RIGHT = 2, LEFT = 3, ON_SCREEN = 4, RIGHT = 5, BOTTOM_LEFT = 6, BOTTOM = 7, BOTTOM_RIGHT = 8};

    auto get_screen_plane(const SDL_Surface *s, const int_type x, const int_type y) -> SCREEN_PLANE {
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

    // It is assumed that recalculation is required if this function is called
    // Either point1(x1, y1) or point2 (x2, y2) is/are not ON_SCREEN
    auto recalc_line_points(const SDL_Surface *s, int_type &x1, int_type &y1, int_type &x2, int_type &y2, const SCREEN_PLANE sp1, const SCREEN_PLANE sp2) -> bool {
        fp_type h = y2 - y1;
        fp_type w = x2 - x1;

        // Call only if it's beyond ON_SCREEN
        // ∴ the condition if(y == y_equals) return x is not applicable;
        auto get_x_at_y_equals = [&](const int_type x, const int_type y, const int_type y_equals) -> int_type {
            if(w == 0) return x;
            fp_type m = h / w;
            fp_type b = y - (m * x);
            return static_cast<int_type>((y_equals - b) / m);
        };

        // Call only if it's beyond ON_SCREEN
        // ∴ the condition if(w == 0) is not applicable;
        auto get_y_at_x_equals = [&](const int_type x, const int_type y, const int_type x_equals) -> int_type {
            if(h == 0) return y;
            fp_type m = h / w;
            fp_type b = y - (m * x);
            return static_cast<int_type>(m * x_equals + b);
        };

        // Call only if one of the points is out of bounds
        // ∴ the condition screen_plane == ON_SCREEN is not applicable 
        auto recalc_point_at_bound = [&](int_type &x, int_type &y, SCREEN_PLANE screen_plane) -> void {
            auto is_x_at_top = [&]() -> bool {auto tx = get_x_at_y_equals(x, y, 0); 
                                                if(is_point_within_bounds(tx, 0, s->w, s->h)) {x = tx; y = 0; return true;} return false;};
            auto is_x_at_bottom = [&]() -> bool {auto tx = get_x_at_y_equals(x, y, s->h - 1); 
                                                if(is_point_within_bounds(tx, s->h - 1, s->w, s->h)) {x = tx; y = s->h - 1; return true;} return false;};
            auto get_x_at_top = [&]() -> void {x = get_x_at_y_equals(x, y, 0); y = 0;};
            auto get_x_at_bottom = [&]() -> void {x = get_x_at_y_equals(x, y, s->h - 1); y = s->h - 1;};
            auto get_y_at_left = [&]() -> void {y = get_y_at_x_equals(x, y, 0); x = 0;};
            auto get_y_at_right = [&]() -> void {y = get_y_at_x_equals(x, y, s->w - 1); x = s->w - 1;};
            auto check_top_left = [&]() -> void {if(is_x_at_top()) return; get_y_at_left(); return;};
            auto check_top_right = [&]() -> void {if(is_x_at_top()) return; get_y_at_right(); return;};
            auto check_bottom_left = [&]() -> void {if(is_x_at_bottom()) return; get_y_at_left(); return;};
            auto check_bottom_right = [&]() -> void {if(is_x_at_bottom()) return; get_y_at_right(); return;};

            switch(screen_plane) {
                case TOP_LEFT: check_top_left(); break;
                case TOP: get_x_at_top(); break;
                case TOP_RIGHT: check_top_right(); break;
                case BOTTOM_LEFT: check_bottom_left(); break;
                case BOTTOM_RIGHT: check_bottom_right(); break;
                case BOTTOM: get_x_at_bottom(); break;
                case LEFT: get_y_at_left(); break;
                case RIGHT: get_y_at_right(); break;
                default: break;
            }
        };

        if(sp1 != ON_SCREEN) {
            recalc_point_at_bound(x1, y1, sp1);
            if(get_screen_plane(s, x1, y1) != ON_SCREEN) return false;
        }

        if(sp2 != ON_SCREEN) {
            recalc_point_at_bound(x2, y2, sp2);
            if(get_screen_plane(s, x2, y2) != ON_SCREEN) return false;
        }

        return true;
    }

    auto line(SDL_Surface *s, int_type x1, int_type y1, int_type x2, int_type y2, const Uint32 rgba) -> void {
        auto start = std::chrono::high_resolution_clock::now();
        auto sp1 = get_screen_plane(s, x1, y1);
        auto sp2 = get_screen_plane(s, x2, y2);
        if(sp1 != ON_SCREEN || sp2 != ON_SCREEN) [[unlikely]] 
             if(!recalc_line_points(s, x1, y1, x2, y2, sp1, sp2)) return;
        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        std::cout << "elapsed: " << elapsed << "\n";

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
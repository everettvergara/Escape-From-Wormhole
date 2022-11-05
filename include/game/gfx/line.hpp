#pragma once

#include <cstdint>
#include <unordered_set>
#include <SDL.h>
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


    // Return true if can be plotted
    // Return false if cannot be plotted
    auto line_recalc_points(const SDL_Surface *s, const int_type wb, const int_type hb, int_type &x1, int_type &y1, int_type &x2, int_type &y2) -> bool {
        constexpr auto plane_hash = [&](SCREEN_PLANE l, SCREEN_PLANE r) -> uint8_t { return (l << 4) + r;};
        static std::unordered_set<uint8_t> cannot_be_plotted {
            plane_hash(TOP_LEFT, TOP_LEFT), plane_hash(TOP_LEFT, TOP), plane_hash(TOP_LEFT, TOP_RIGHT), plane_hash(TOP_LEFT, LEFT), plane_hash(TOP_LEFT, BOTTOM_LEFT),
            plane_hash(TOP, TOP), plane_hash(TOP, TOP_LEFT), plane_hash(TOP, TOP_RIGHT), 
            plane_hash(TOP_RIGHT, TOP_RIGHT), plane_hash(TOP_RIGHT, TOP), plane_hash(TOP_RIGHT, TOP_LEFT), plane_hash(TOP_RIGHT, RIGHT), plane_hash(TOP_RIGHT, BOTTOM_RIGHT),
            plane_hash(LEFT, LEFT), plane_hash(LEFT, TOP_LEFT), plane_hash(LEFT, BOTTOM_LEFT),
            plane_hash(RIGHT, RIGHT), plane_hash(RIGHT, TOP_RIGHT), plane_hash(RIGHT, BOTTOM_RIGHT),
            plane_hash(BOTTOM_LEFT, BOTTOM_LEFT), plane_hash(BOTTOM_LEFT, TOP), plane_hash(BOTTOM_LEFT, LEFT), plane_hash(BOTTOM_LEFT, BOTTOM), plane_hash(BOTTOM_LEFT, BOTTOM_RIGHT),
            plane_hash(BOTTOM, BOTTOM), plane_hash(BOTTOM, BOTTOM_LEFT), plane_hash(BOTTOM, BOTTOM_RIGHT),
            plane_hash(BOTTOM_RIGHT, BOTTOM_RIGHT), plane_hash(BOTTOM_RIGHT, BOTTOM_LEFT), plane_hash(BOTTOM_RIGHT, BOTTOM), plane_hash(BOTTOM_RIGHT, TOP_RIGHT), plane_hash(BOTTOM_RIGHT, RIGHT),
        };

        auto sp1 = get_screen_plane(s, x1, y1);
        auto sp2 = get_screen_plane(s, x2, y2);
        if((sp1 & sp2 & ON_SCREEN) == ON_SCREEN) [[likely]] return true;
        else if(cannot_be_plotted.find(plane_hash(sp1, sp2)) != cannot_be_plotted.end()) return false;

        // If recalculation is required
        fp_type h = y2 - y1;
        fp_type w = x2 - x1;


        // Call only if it's beyond ON_SCREEN
        // ∴ the condition if(y == y_equals) return x is not applicable;
        auto get_x_at_y_equals = [&](const int_type x, const int_type y, const int_type y_equals) -> int_type {
            if(w == 0) return x;
            fp_type m = h / w;
            fp_type b = y - m * x;
            return static_cast<int_type>((y - b) / m);
        };

        // Call only if it's beyond ON_SCREEN
        // ∴ the condition if(w == 0) is not applicable;
        auto get_y_at_x_equals = [&](const int_type x, const int_type y, const int_type x_equals) -> int_type {
            if(h == 0) return y;
            fp_type m = h / w;
            fp_type b = y - m * x;
            return static_cast<int_type>(m * x_equals + b);
        };

        // Call only if one of the points is out of bounds
        // ∴ the condition screen_plane == ON_SCREEN is not applicable 
        // If the two points are out of bounds do not call.
        auto recalc_point_at_bound = [&](int_type &x, int_type &y, SCREEN_PLANE screen_plane) -> void {

            auto get_y_at_left = [&]() -> void {y = get_y_at_x_equals(x, y, 0); x = 0;};
            auto get_y_at_right = [&]() -> void {y = get_y_at_x_equals(x, y, wb); x = wb;};

            switch(screen_plane) {
                [[likely]] case ON_SCREEN:
                    break;
                case TOP_LEFT:
                    if(auto tx = get_x_at_y_equals(x, y, 0); is_point_within_bounds(tx, 0, s->w, s->h)) {x = tx; y = 0;}
                    else get_y_at_left();
                    break;
                case TOP:
                    x = get_x_at_y_equals(x, y, 0); y = 0;
                    break;
                case TOP_RIGHT:
                    if(auto tx = get_x_at_y_equals(x, y, 0); is_point_within_bounds(tx, 0, s->w, s->h)) {x = tx; y = 0;}
                    else get_y_at_right();
                    break;
                case BOTTOM_LEFT:
                    if(auto tx = get_x_at_y_equals(x, y, hb); is_point_within_bounds(tx, hb, s->w, s->h)) {x = tx; y = hb;}
                    else get_y_at_left();
                    break;
                case BOTTOM_RIGHT:
                    if(auto tx = get_x_at_y_equals(x, y, hb); is_point_within_bounds(tx, hb, s->w, s->h)) {x = tx; y = hb;}
                    else get_y_at_right();
                    break;
                case BOTTOM:
                    x = get_x_at_y_equals(x, y, hb); y = hb;
                    break;
                case LEFT:
                    get_y_at_left();
                    break;
                case RIGHT:
                    get_y_at_right();
                    break;
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
        // bool is_p1_within_bounds = is_point_within_bounds(x1, y1, s->w, s->h);
        // bool is_p2_within_bounds = is_point_within_bounds(x2, y2, s->w, s->h);





    }

}
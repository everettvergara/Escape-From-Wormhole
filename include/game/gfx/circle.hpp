#pragma once

#include "game/engine/surface.hpp" 

namespace g80::game::gfx {

    using namespace g80::game::engine;
    
    class circle {
    
    private:
        surface *s_;

    public:
        circle(surface *s);
        auto draw(const point &p, const int_type r, Uint32 rgba) -> void;
    };

    circle::circle(surface *s) : s_(s) {
    }

    auto circle::draw(const point &p, const int_type r, Uint32 rgba) -> void {
        auto center = static_cast<Uint32 *>(s_->get_handle()->pixels) + p.y * s_->get_w() + p.x;

        int_type x = r, y = 0;
        int_type bx = x * s_->get_w(), by = 0;

        Sint32 dx = 1 - (r << 1);
        Sint32 dy = 1;
        Sint32 re = 0;

        while (x >= y) {
            *(center + x - by) = rgba;  // Upper Right: Bottom, 
            *(center + y - bx) = rgba;  // Upper Right: Top, y++, x--
            *(center - y - bx) = rgba;  // Upper Left: Top 
            *(center - x - by) = rgba;  // Upper Left: Bottom,
            *(center - x + by) = rgba;  // Bottom Left: Top
            *(center - y + bx) = rgba;  // Bottom Left: Bottom 
            *(center + y + bx) = rgba;  // Bottom Right: Bottom 
            *(center + x + by) = rgba;  // Bottom Right: Top

            ++y;
            re += dy;
            dy += 2;
            if ((re << 1) + dx > 0) {
                --x;
                bx -= s_->get_w();
                re += dx;
                dx += 2;
            }
            by += s_->get_w();
        }
    }
}
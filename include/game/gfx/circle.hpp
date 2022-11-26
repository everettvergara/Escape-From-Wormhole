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

        int_type slow = 0;
        int_type fast_adder = r * s_->get_w();

        int_type dx = 1 - (r << 1);
        int_type dy = 1;
        int_type re = 0;
        int_type slow_adder = 0;

        // center -= fast_adder;

        while (slow <= fast_adder) {
            *(center - fast_adder + slow_adder) = rgba;     // Q1: bottom

            re += dy;
            dy += 2;
            if ((re << 1) + dx > 0) {
                slow += s_->get_w();
                re += dx;
                dx += 2;
                ++slow_adder;
            }
            fast_adder -= s_->get_w();
        }
    }
} 


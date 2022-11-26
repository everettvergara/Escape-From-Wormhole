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


        int_type fast_adder_from_0 = 0;
        int_type slow_adder_from_0 = r * s_->get_w();

        int_type fast_adder_from_r = r * s_->get_w();
        int_type slow_adder_from_r = 0;


        int_type dx = 1 - (r << 1);
        int_type dy = 1;
        int_type re = 0;

        while (slow_adder_from_0 >= fast_adder_from_0) {
            *(center + fast_adder_from_r - slow_adder_from_r) = rgba;     // Q1: bottom

            re += dy;
            dy += 2;
            if ((re << 1) + dx > 0) {
                re += dx;
                dx += 2;
                --slow_adder_from_0;
            }
            fast_adder_from_0 += s_->get_w();
        }
    }
} 


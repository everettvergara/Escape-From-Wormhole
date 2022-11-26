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
        int_type fast_adder_by_y_inc = 0;
        int_type fast_adder_by_x_inc = 0;
        int_type slow_adder_by_x_dec = r;
        int_type slow_adder_by_y_dec = r * s_->get_w();
        int_type dx = 1 - (r << 1);
        int_type dy = 1;
        int_type re = 0;
        while(slow_adder_by_x_dec > fast_adder_by_x_inc) {
            *(center - fast_adder_by_y_inc + slow_adder_by_x_dec) = rgba;     // Q1: bottom
            *(center + fast_adder_by_x_inc - slow_adder_by_y_dec) = rgba;     // Q1: top
            *(center - fast_adder_by_x_inc - slow_adder_by_y_dec) = rgba;     // Q2: top
            *(center - fast_adder_by_y_inc - slow_adder_by_x_dec) = rgba;     // Q2: bottom
            *(center + fast_adder_by_y_inc - slow_adder_by_x_dec) = rgba;     // Q3: top
            *(center - fast_adder_by_x_inc + slow_adder_by_y_dec) = rgba;     // Q3: bottom
            *(center + fast_adder_by_x_inc + slow_adder_by_y_dec) = rgba;     // Q4: bottom
            *(center + fast_adder_by_y_inc + slow_adder_by_x_dec) = rgba;     // Q4: top
            re += dy;
            dy += 2;
            if((re << 1) + dx > 0) {
                re += dx;
                dx += 2;
                slow_adder_by_x_dec -= 1;
                slow_adder_by_y_dec -= s_->get_w();
            }
            fast_adder_by_x_inc += 1;
            fast_adder_by_y_inc += s_->get_w();
        }
    }
} 


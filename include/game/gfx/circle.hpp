#pragma once

#include "game/engine/surface.hpp" 

namespace g80::game::gfx {

    using namespace g80::game::engine;
    
    class circle {
    
    private:
        surface *s_;

    public:
        circle(surface *s);
        auto draw(const point &p, const int_type r, const Uint32 rgba) -> void;
        auto draw(const point &p, const int_type r, const Uint32 rgba, const Uint32 mask) -> void;
    };

    circle::circle(surface *s) : s_(s) {
    }

    auto circle::draw(const point &p, const int_type r, const Uint32 rgba) -> void {
        auto center = static_cast<Uint32 *>(s_->get_handle()->pixels) + p.y * s_->get_w() + p.x;
        int_type fast_adder_by_y_inc = 0;
        int_type fast_adder_by_x_inc = 0;
        int_type slow_adder_by_x_dec = r;
        int_type slow_adder_by_y_dec = r * s_->get_w();
        int_type delta_x = 1 - (r << 1);
        int_type delta_y = 1;
        int_type radius_error = 0;
        while(slow_adder_by_x_dec > fast_adder_by_x_inc) {
            *(center - fast_adder_by_y_inc + slow_adder_by_x_dec) = rgba;     // Q1: bottom
            *(center + fast_adder_by_x_inc - slow_adder_by_y_dec) = rgba;     // Q1: top
            *(center - fast_adder_by_x_inc - slow_adder_by_y_dec) = rgba;     // Q2: top
            *(center - fast_adder_by_y_inc - slow_adder_by_x_dec) = rgba;     // Q2: bottom
            *(center + fast_adder_by_y_inc - slow_adder_by_x_dec) = rgba;     // Q3: top
            *(center - fast_adder_by_x_inc + slow_adder_by_y_dec) = rgba;     // Q3: bottom
            *(center + fast_adder_by_x_inc + slow_adder_by_y_dec) = rgba;     // Q4: bottom
            *(center + fast_adder_by_y_inc + slow_adder_by_x_dec) = rgba;     // Q4: top
            radius_error += delta_y;
            delta_y += 2;
            if((radius_error << 1) + delta_x > 0) {
                radius_error += delta_x;
                delta_x += 2;
                slow_adder_by_x_dec -= 1;
                slow_adder_by_y_dec -= s_->get_w();
            }
            fast_adder_by_x_inc += 1;
            fast_adder_by_y_inc += s_->get_w();
        }
    }

    auto circle::draw(const point &p, const int_type r, const Uint32 rgba, const Uint32 mask) -> void {
        auto center = static_cast<Uint32 *>(s_->get_handle()->pixels) + p.y * s_->get_w() + p.x;
        int_type fast_adder_by_y_inc = 0;
        int_type fast_adder_by_x_inc = 0;
        int_type slow_adder_by_x_dec = r;
        int_type slow_adder_by_y_dec = r * s_->get_w();
        int_type delta_x = 1 - (r << 1);
        int_type delta_y = 1;
        int_type radius_error = 0;
        int_type tctr = 0;
        auto tmask = mask;
        while(slow_adder_by_x_dec > fast_adder_by_x_inc) {
            if(tmask & 1) {
                *(center - fast_adder_by_y_inc + slow_adder_by_x_dec) = rgba;
                *(center + fast_adder_by_x_inc - slow_adder_by_y_dec) = rgba;     
                *(center - fast_adder_by_x_inc - slow_adder_by_y_dec) = rgba;
                *(center - fast_adder_by_y_inc - slow_adder_by_x_dec) = rgba;
                *(center + fast_adder_by_y_inc - slow_adder_by_x_dec) = rgba;
                *(center - fast_adder_by_x_inc + slow_adder_by_y_dec) = rgba;
                *(center + fast_adder_by_x_inc + slow_adder_by_y_dec) = rgba;
                *(center + fast_adder_by_y_inc + slow_adder_by_x_dec) = rgba;
            }
            radius_error += delta_y;
            delta_y += 2;
            if((radius_error << 1) + delta_x > 0) {
                radius_error += delta_x;
                delta_x += 2;
                slow_adder_by_x_dec -= 1;
                slow_adder_by_y_dec -= s_->get_w();
            }
            fast_adder_by_x_inc += 1;
            fast_adder_by_y_inc += s_->get_w();
            tmask >>= 1;
            tmask = (++tctr % 32 == 0) ? mask : tmask;
        }
    }


} 


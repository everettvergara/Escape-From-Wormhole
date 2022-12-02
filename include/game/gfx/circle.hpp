#pragma once

#include <array>
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
        fp_type oct_perimeter = static_cast<fp_type>(2.0 * M_PI * r / 8.0);
        static constexpr std::array<int, 8> tn {+1, -1, +1, -1, +1, -1, +1, -1};
        std::array<size_t, 8> tctr;

        tctr[0] = 0;                        
        tctr[1] = oct_perimeter * 2 - 1;
        tctr[2] = oct_perimeter * 2;
        tctr[3] = oct_perimeter * 4 - 1;
        tctr[4] = oct_perimeter * 4;
        tctr[5] = oct_perimeter * 6 - 1;
        tctr[6] = oct_perimeter * 6;
        tctr[7] = oct_perimeter * 8 - 1;

        while(slow_adder_by_x_dec > fast_adder_by_x_inc) {
            if(mask >> (tctr[0] % 32)) *(center - fast_adder_by_y_inc + slow_adder_by_x_dec) = rgba;  // bottom -> top
            if(mask >> (tctr[1] % 32)) *(center + fast_adder_by_x_inc - slow_adder_by_y_dec) = rgba;  // top -> bottom
            if(mask >> (tctr[2] % 32)) *(center - fast_adder_by_x_inc - slow_adder_by_y_dec) = rgba;  // top -> bottom
            if(mask >> (tctr[3] % 32)) *(center - fast_adder_by_y_inc - slow_adder_by_x_dec) = rgba;  // bottom -> top
            if(mask >> (tctr[4] % 32)) *(center + fast_adder_by_y_inc - slow_adder_by_x_dec) = rgba;
            if(mask >> (tctr[5] % 32)) *(center - fast_adder_by_x_inc + slow_adder_by_y_dec) = rgba;
            if(mask >> (tctr[6] % 32)) *(center + fast_adder_by_x_inc + slow_adder_by_y_dec) = rgba;
            if(mask >> (tctr[7] % 32)) *(center + fast_adder_by_y_inc + slow_adder_by_x_dec) = rgba;
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
            for(size_t i{0}; i < 8; ++i) tctr[i] += tn[i];
        }
    }

/*

    auto circle::draw(const point &p, const int_type r, const Uint32 rgba, const Uint32 mask) -> void {
        auto center = static_cast<Uint32 *>(s_->get_handle()->pixels) + p.y * s_->get_w() + p.x;
        int_type fast_adder_by_y_inc = 0;
        int_type fast_adder_by_x_inc = 0;
        int_type slow_adder_by_x_dec = r;
        int_type slow_adder_by_y_dec = r * s_->get_w();
        int_type delta_x = 1 - (r << 1);
        int_type delta_y = 1;
        int_type radius_error = 0;
        fp_type oct_perimeter = static_cast<fp_type>(2.0 * M_PI * r / 8.0); // 157.08
        std::array<Uint32, 8> tmask;
        std::array<size_t, 8> tctr;

        auto reverse = [](Uint32 mask) {
            Uint32 rev {0};
            auto ts {sizeof(Uint32) * 8};
            decltype(ts) ctr {0};
            while(mask > 0) {
                rev <<= 1;
                rev |= mask & 1;
                mask >>= 1;
                ++ctr;
            }
            rev <<= ts - ctr;
            return rev;
        };

        auto rev_mask = reverse(mask);
        for(size_t i{0}; i < 8; ++i) {
            tctr[i] = (static_cast<Uint32>(i * oct_perimeter) % 32);
            tmask[i] = mask >> tctr[i];
            if(i == 1 || i == 3) tmask[i] = reverse(tmask[i]); 
        }
        while(slow_adder_by_x_dec > fast_adder_by_x_inc) {
            if(tmask[0] & 1) *(center - fast_adder_by_y_inc + slow_adder_by_x_dec) = rgba;  // bottom -> top
            if(tmask[1] & 1) *(center + fast_adder_by_x_inc - slow_adder_by_y_dec) = rgba;  // top -> bottom
            if(tmask[2] & 1) *(center - fast_adder_by_x_inc - slow_adder_by_y_dec) = rgba;  // top -> bottom
            if(tmask[3] & 1) *(center - fast_adder_by_y_inc - slow_adder_by_x_dec) = rgba;  // bottom -> top
            // *(center + fast_adder_by_y_inc - slow_adder_by_x_dec) = rgba;
            // *(center - fast_adder_by_x_inc + slow_adder_by_y_dec) = rgba;
            // *(center + fast_adder_by_x_inc + slow_adder_by_y_dec) = rgba;
            // *(center + fast_adder_by_y_inc + slow_adder_by_x_dec) = rgba;
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
            for(size_t i{0}; i < 8; ++i) {
                tmask[i] >>= 1;
                if(i == 1 || i == 3) {
                    tmask[i] = (++tctr[i] % 32 == 0) ? rev_mask : tmask[i];
                } else {
                    tmask[i] = (++tctr[i] % 32 == 0) ? mask : tmask[i];
                }
            }            
        }
    }
*/
} 


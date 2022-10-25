#ifndef _QUADBEZIERANIM_HPP_
#define _QUADBEZIERANIM_HPP_

#include "Commons.hpp"

namespace g80 {
    
    class QuadBezierAnim {
    public:

        QuadBezierAnim(
            const SDL_PixelFormat *format,
            const Point &p1, const Point &p2, const Point &p3, 
            const RGBAColor rgba_color, 
            const Dim speed_max_, 
            const Dim tail_n = 10) : 

            p1_(p1), p2_(p2), p3_(p3), 
            d1_(p2_ - p1_), d2_(p3_ - p2_), 
            size_per_step_(1.0f / (speed_max_ - 1)),
            start_tail_(size_per_step_ * tail_n),
            s_{0.0f},
            st_{0.0f},
            bz_(p1_), 
            t_(p1_) {
                SDL_GetRGBA(rgba_color, format, &r_, &g_, &b_, &a_);
            }

        auto reset(
            const SDL_PixelFormat *format, 
            const Point &p1, const Point &p2, const Point &p3, 
            const RGBAColor rgba_color, 
            const Dim speed_max_, 
            const Dim tail_n = 10) {

            p1_ = {p1}; p2_ = {p2}; p3_ = {p3};
            d1_ = {p2_ - p1_}; d2_ = {p3_ - p2_}; 
            size_per_step_ = {1.0f / (speed_max_ - 1)};
            start_tail_ = {size_per_step_ * tail_n};
            s_ = {0.0f};
            st_ = {0.0f};
            bz_ = {p1_};
            t_ = {p1_};

            SDL_GetRGBA(rgba_color, format, &r_, &g_, &b_, &a_);
        }

        auto is_valid_current_point() -> bool {
            return s_ <= 1.0f;
        }

        auto is_valid_tail_point() -> bool {
            return st_ <= 1.0f;
        }

        auto next() -> Point & {
            Point d1 = d1_ * s_;
            Point d2 = d2_ * s_;
            Point c1 = p1_ + d1;
            Point c2 = p2_ + d2;
            Point dc = (c2 - c1) * s_;
            bz_ = c1 + dc;
            s_ += size_per_step_;
            return bz_;
        }

        auto get_current_point() -> Point & {
            return bz_;
        }

        auto get_tail_point() -> Point & {
            Point d1 = d1_ * st_;
            Point d2 = d2_ * st_;
            Point c1 = p1_ + d1;
            Point c2 = p2_ + d2;
            Point dc = (c2 - c1) * st_;
            t_ = c1 + dc;
            if (s_ >= start_tail_) st_ += size_per_step_;
            return t_;
        }

        auto get_color(const SDL_PixelFormat *format) -> RGBAColor {            
            return SDL_MapRGBA(format, r_ * s_, g_ * s_, b_ * s_, a_);
        }

        auto get_p1() -> Point & {
            return p1_;
        }

        auto get_p2() -> Point & {
            return p2_;
        }

        auto get_p3() -> Point & {
            return p3_;
        }

    private:
        Point p1_, p2_, p3_;
        Point d1_, d2_;
        float size_per_step_, start_tail_;
        float s_, st_;
        Point bz_, t_;
        Color r_, g_, b_, a_;
    };
}
#endif 

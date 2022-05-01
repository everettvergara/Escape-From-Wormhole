#ifndef _BEZIER_HPP_
#define _BEZIER_HPP_

#include "Commons.hpp"

namespace g80 {
    class QuadBezierAnim {
    public:
        QuadBezierAnim() {};
        QuadBezierAnim(const Point &p1, const Point &p2, const Point &p3, const RGBAColor color, const Dim smax, const float TAIL_N = 10.0f) : 
        p1_(p1), p2_(p2), p3_(p3), 
        d1_(p2_ - p1_), d2_(p3_ - p2_), bz_(p1_), t_{p1_},
        size_per_step_(1.0f / (smax - 1)),
        st_{0.0f * size_per_step_},
        TAIL_N_{TAIL_N},
        color_(color) { }

        auto reset(const Point &p1, const Point &p2, const Point &p3, const RGBAColor color, const Dim smax, const float TAIL_N = 10.0f) {
            p1_ = {p1}, p2_ = {p2}, p3_ = {p3},
            d1_ = {p2_ - p1_}, d2_ = {p3_ - p2_}, bz_ = {p1_}, t_ = {p1_},
            size_per_step_ = {1.0f / (smax - 1)},
            st_ = {0.0f * size_per_step_},
            TAIL_N_ = {TAIL_N},
            color_ = {color}, s_ = {0.0f};
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
            if (s_ >= size_per_step_ * TAIL_N_) st_ += size_per_step_;
            return t_;
        }

        auto get_color(const SDL_PixelFormat *format) -> RGBAColor {            
            Color r_, g_, b_, a_;
            SDL_GetRGBA(color_, format, &r_, &g_, &b_, &a_);
            RGBAColor color = SDL_MapRGBA(format, r_ * s_, g_ * s_, b_ * s_, 255);
            return color;
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
        Point p1_, p2_, p3_, d1_, d2_, bz_, t_;
        float s_{0.0f}, size_per_step_, st_, TAIL_N_;
        RGBAColor color_;
    };
}
#endif 
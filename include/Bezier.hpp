#ifndef _BEZIER_HPP_
#define _BEZIER_HPP_

#include "Commons.hpp"

namespace g80 {
    class QuadBezierAnim {
    public:
        QuadBezierAnim() {};
        QuadBezierAnim(const Point &p1, const Point &p2, const Point &p3, const Color color, const Dim smax) : 
        p1_(p1), p2_(p2), p3_(p3), 
        d1_(p2_ - p1_), d2_(p3_ - p2_), bz_(p1_),
        size_per_step_(1.0f / (smax - 1)),
        color_(color), smax_(smax) {}

        auto next() -> Point & {
            if (ctr_ > smax_) return bz_;
            Point d1 = d1_ * s_;
            Point d2 = d2_ * s_;
            Point c1 = p1_ + d1;
            Point c2 = p2_ + d2;
            Point dc = (c2 - c1) * s_;
            bz_ = c1 + dc;
            s_ += size_per_step_;
            ++ctr_;;
            return bz_;
        }

        auto get_current_point() -> Point & {
            return bz_;
        }

        auto get_color() -> Color & {
            return color_;
        }

    private:
        Point p1_, p2_, p3_, d1_, d2_, bz_;
        float s_{0.0f}, size_per_step_;
        Color color_;
        Dim ctr_{0}, smax_;
    };
}
#endif 
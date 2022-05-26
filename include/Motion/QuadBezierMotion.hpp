#ifndef QUAD_BEZIER_MOTION_HPP
#define QUAD_BEZIER_MOTION_HPP

#include "Point.hpp"
#include "LinearMath.hpp"

namespace g80 {

    template<typename T>
    class QuadBezierMotion {
    public:
        QuadBezierMotion() {}

        auto quad_bezier_set(
            const Point<T> &p1,
            const Point<T> &p2,
            const Point<T> &p3,
            const Sint32 sz_steps,
            const Sint32 sz_trail) -> void {

            p1_ = p1; p2_ = p2; p3_ = p3;
            d1 = p2_ - p1_;
            d2 = p3_ - p2_;

            head_ = {p1_};
            tail_ = {p1_};
            sz_steps_ = {sz_steps};
            head_step_ = {0};
            tail_step_ = {-sz_trail};
        }

        auto next() -> bool {
            if (tail_step_ == sz_steps_) return false;

            if (head_step_ < sz_steps_) {
                ++head_step_;
                auto cp1 = lerp_point_b_less_a(p1, d1, head_step_, max_steps);
                auto cp2 = lerp_point_b_less_a(p2, d2, head_step_, max_steps);
                head_ = lerp_point(cp1, cp2, head_step_, max_steps);
            }

            if (tail_step_++ >= 0) {
                auto cp1 = lerp_point_b_less_a(p1, d1, tail_step_, max_steps);
                auto cp2 = lerp_point_b_less_a(p2, d2, tail_step_, max_steps);
                tail_ = lerp_point(cp1, cp2, tail_step_, max_steps);
            }

            return true;
        }    
    private:
        Point<T> p1_, p2_, p3_;
        Point<T> d1_, d2_;
        Point<T> head_, tail_;
        T sz_steps_, tail_step_, head_step_;
    };
}

#endif 
#ifndef QUAD_BEZIER_MOTION_HPP
#define QUAD_BEZIER_MOTION_HPP

#include "Point.hpp"
#include "LinearMath.hpp"

namespace g80 {

    template<typename T>
    class QuadBezierMotion {
    public:
        QuadBezierMotion() {}

        auto operator>(const QuadBezierMotion &rhs) const -> bool {
            return tail_step_ > rhs.tail_step_;
        }

        auto quad_bezier_set(
            const Point<T> &p1,
            const Point<T> &p2,
            const Point<T> &p3,
            const Sint32 sz_steps,
            const Sint32 sz_trail) -> void {

            p1_ = p1; p2_ = p2; p3_ = p3;
            d1_ = p2_ - p1_;
            d2_ = p3_ - p2_;

            head_ = {p1_};
            tail_ = {p1_};
            sz_steps_ = {static_cast<T>(sz_steps)};
            head_step_ = {0};
            tail_step_ = {static_cast<T>(-sz_trail)};
        }

        auto next() -> bool {
            if (tail_step_ == sz_steps_) return false;

            if (head_step_ < sz_steps_) {
                ++head_step_;
                auto cp1 = lerp_point_b_less_a(p1_, d1_, head_step_, sz_steps_);
                auto cp2 = lerp_point_b_less_a(p2_, d2_, head_step_, sz_steps_);
                head_ = lerp_point(cp1, cp2, head_step_, sz_steps_);
            }

            if (tail_step_++ >= 0) {
                auto cp1 = lerp_point_b_less_a(p1_, d1_, tail_step_, sz_steps_);
                auto cp2 = lerp_point_b_less_a(p2_, d2_, tail_step_, sz_steps_);
                tail_ = lerp_point(cp1, cp2, tail_step_, sz_steps_);
            }

            return true;
        }   

        inline auto get_head() const -> const Point<T> & {return head_;}
        inline auto get_tail() const -> const Point<T> & {return tail_;}
        inline auto get_head_step() const -> Sint32 {return head_step_;}
        inline auto get_tail_step() const -> Sint32 {return tail_step_;}
        inline auto get_size_of_step() const -> Sint32 {return sz_steps_;}

    private:
        Point<T> p1_, p2_, p3_;
        Point<T> d1_, d2_;
        Point<T> head_, tail_;
        T sz_steps_, tail_step_, head_step_;
    };
}

#endif 
#ifndef QUAD_BEZIER_MOTION_HPP
#define QUAD_BEZIER_MOTION_HPP

#include "Point.hpp"

namespace g80 {

    template<typename T>
    class QuadBezierMotion {
    public:
        QuadBezierMotion() {}

        auto quad_bezier_set(
            const Point<T> &p1,
            const Point<T> &p2,
            const Point<T> &p3) -> void {

            p1_ = p1; p2_ = p2; p3_ = p3;


        }
    
    private:
        Point<T> p1_, p2_, p3_;
        Point<T> d1_, d2_;
        Point<T> head_, tail_;
        Point<T> inc_;
        Sint32 sz_steps_, tail_step_, head_step_;
    };
}

#endif 
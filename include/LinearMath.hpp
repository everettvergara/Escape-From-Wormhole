#ifndef LINEAR_MATH_HPP
#define LINEAR_MATH_HPP

#include "Point.hpp"

namespace g80 {
    template<typename T>
    inline auto lerp(const T a, const T b, const T t) -> T {
        static_assert(
            std::is_same<T, float>::value || 
            std::is_same<T, double>::value || 
            std::is_same<T, long double>::value,
            "Must be of floating-point type");
        return a + t * (b - a);
    }

    template<typename T>
    inline auto lerp_point(const Point<T> &a, const Point<T> &b, T t, T tmax) -> Point<T> {
        return a + (b - a) * t / tmax;
    }

    template<typename T>
    inline auto lerp_point_b_less_a(const Point<T> &a, const Point<T> &b_less_a, T t, T tmax) -> Point<T> {
        return a + b_less_a * t / tmax;
    }
}

#endif 
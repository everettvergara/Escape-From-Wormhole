#pragma once

#include <cstdint>
#include <cassert>
#include <tuple>
#include <iostream>


namespace g80::video {
    template<typename T>
    struct base_point {
        static_assert(
            std::is_same_v<T, int8_t> || std::is_same_v<T, uint8_t> || 
            std::is_same_v<T, int16_t> || std::is_same_v<T, uint16_t> || 
            std::is_same_v<T, int32_t> || std::is_same_v<T, uint32_t> || 
            std::is_same_v<T, int64_t> || std::is_same_v<T, uint64_t> || 
            std::is_same_v<T, float> || std::is_same_v<T, double> || 
            std::is_same_v<T, long double>, "Type not allowed as point"); 

        T x, y;

        base_point(T ix = static_cast<T>(0), T iy = static_cast<T>(0)) : x(ix), y(iy) {}
        template<typename U> operator base_point<U>() {return base_point<U>(static_cast<U>(x), static_cast<U>(y));}
        auto operator+=(const base_point<T> &r) -> base_point<T> & {x += r.x; y += r.y; return *this;}
        auto operator-=(const base_point<T> &r) -> base_point<T> & {x -= r.x; y -= r.y; return *this;}
        auto operator*=(const T s) -> base_point<T> & {x *= s; y *= s; return *this;}
        auto operator*=(const base_point<T> &r) -> base_point<T> & {x *= r.x; y *= r.y; return *this;}
        auto operator/=(const T s) -> base_point<T> & {x /= s; y /= s; return *this;}
        auto operator/=(const base_point<T> &r) -> base_point<T> & {x /= r.x; y /= r.y; return *this;}
        auto abs() -> base_point<T> {return base_point<T>(x < 0 ? -x : x, y < 0 ? -y : y);}
    };

    template<typename T> auto operator==(const base_point<T> &l, const base_point<T> &r) -> bool {return l.x == r.x && l.y == r.y;}
    template<typename T> auto operator!=(const base_point<T> &l, const base_point<T> &r) -> bool {return l.x != r.x || l.y != r.y;}
    template<typename T> auto operator>=(const base_point<T> &l, const base_point<T> &r) -> bool {return l.x >= r.x && l.y >= r.y;}
    template<typename T> auto operator>(const base_point<T> &l, const base_point<T> &r) -> bool {return l.x > r.x && l.y > r.y;}
    template<typename T> auto operator<=(const base_point<T> &l, const base_point<T> &r) -> bool {return l.x <= r.x && l.y <= r.y;}
    template<typename T> auto operator<(const base_point<T> &l, const base_point<T> &r) -> bool {return l.x < r.x && l.y < r.y;}
    template<typename T> auto operator+(base_point<T> l, const base_point<T> &r) -> base_point<T> {l += r; return l;}
    template<typename T> auto operator-(base_point<T> l, const base_point<T> &r) -> base_point<T> {l -= r; return l;}
    template<typename T> auto operator*(base_point<T> l, const T &s) -> base_point<T> {l *= s; return l;}
    template<typename T> auto operator*(base_point<T> l, const base_point<T> &r) -> base_point<T> {l *= r; return l;}
    template<typename T> auto operator/(base_point<T> l, const base_point<T> &r) -> base_point<T> {l /= r; return l;}
    template<typename T> auto operator/(base_point<T> l, const T &s) -> base_point<T> {l /= s; return l;}
    template<typename T> auto operator<<(std::ostream &os, const base_point<T> &r) -> std::ostream & {return os << "{" << r.x << "," << r.y;}
}
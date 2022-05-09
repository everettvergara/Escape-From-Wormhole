#ifndef _POINT_HPP_
#define _POINT_HPP_ 

#include <SDL.h>
#include <cassert>
#include <type_traits>

namespace g80 {
    template<typename T>
    struct Point {
        static_assert(
            std::is_same<T, Sint8>::value  || std::is_same<T, Uint8>::value ||
            std::is_same<T, Sint16>::value  || std::is_same<T, Uint16>::value ||
            std::is_same<T, Sint32>::value  || std::is_same<T, Uint32>::value ||
            std::is_same<T, Sint64>::value  || std::is_same<T, Uint64>::value ||
            std::is_same<T, float> ::value || std::is_same<T, double>::value || std::is_same<T, long double>::value, "Type not allowed as point");

        Point() {}
        Point(const T x, const T y) : x(x), y(y) {}        
        Point(const Point<T> &rhs) {x = rhs.x; y = rhs.y;}
        template<typename U> Point(const Point<U> &rhs) {x = rhs.x; y = rhs.y;}
        T x;
        T y;
        auto operator+=(const Point<T> &rhs) -> Point<T> & {x += rhs.x; y += rhs.y; return *this;}
        auto operator-=(const Point<T> &rhs) -> Point<T> & {x -= rhs.x; y -= rhs.y; return *this;}
        auto operator*=(const float rhs) -> Point<T> & {x *= rhs; y *= rhs; return *this;}
        auto operator/=(const float rhs) -> Point<T> & {x /= rhs; y /= rhs; return *this;}
        auto abs() -> Point<T> {Point<T> p; p.x = x < 0 ? -x : x; p.y = y < 0 ? -y : y; return p;}
    };
    
    // template<typename T, typename U> inline auto equals(Point<T> lhs, Point<U> &rhs) -> Point<T> {lhs.x = static_cast<T>(rhs.x); lhs.y = static_cast<T>(rhs.y); return lhs;}
    template<typename T> inline auto operator+(Point<T> lhs, const Point<T> &rhs) -> Point<T> {lhs += rhs; return lhs;}
    template<typename T> inline auto operator-(Point<T> lhs, const Point<T> &rhs) -> Point<T> {lhs -= rhs; return lhs;}
    template<typename T> inline auto operator*(Point<T> lhs, const float rhs) -> Point<T> {lhs *= rhs; return lhs;}
    template<typename T> inline auto operator/(Point<T> lhs, const float rhs) -> Point<T> {lhs /= rhs; return lhs;}
    template<typename T> inline auto operator==(const Point<T> &lhs, const Point<T> &rhs) -> bool {return lhs.x == rhs.x && lhs.y == rhs.y;}
    template<typename T> inline auto operator!=(const Point<T> &lhs, const Point<T> &rhs) -> bool {return lhs.x != rhs.x || lhs.y != rhs.y;}

}
#endif 
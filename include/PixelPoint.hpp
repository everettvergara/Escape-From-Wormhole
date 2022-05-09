#ifndef _PIXELPOINT<T>_HPP_
#define _PIXELPOINT<T>_HPP_ 

#include <SDL.h>

namespace g80 {
    template<typename T>
    struct PixelPoint {
        T x;
        T y;
        auto operator+=(const PixelPoint<T> &rhs) -> PixelPoint<T> & {x += rhs.x; y += rhs.y; return *this;}
        auto operator-=(const PixelPoint<T> &rhs) -> PixelPoint<T> & {x -= rhs.x; y -= rhs.y; return *this;}
        auto operator*=(const float rhs) -> PixelPoint<T> & {x *= rhs; y *= rhs; return *this;}
        auto operator/=(const float rhs) -> PixelPoint<T> & {x /= rhs; y /= rhs; return *this;}
        auto abs() -> PixelPoint<T> {PixelPoint<T> p; p.x = x < 0 ? -x : x; p.y = y < 0 ? -y : y; return p;}
    };
    
    template<typename T> inline auto operator+(PixelPoint<T> lhs, const PixelPoint<T> &rhs) -> PixelPoint<T> {lhs += rhs; return lhs;}
    template<typename T> inline auto operator-(PixelPoint<T> lhs, const PixelPoint<T> &rhs) -> PixelPoint<T> {lhs -= rhs; return lhs;}
    template<typename T> inline auto operator*(PixelPoint<T> lhs, const float rhs) -> PixelPoint<T> {lhs *= rhs; return lhs;}
    template<typename T> inline auto operator/(PixelPoint<T> lhs, const float rhs) -> PixelPoint<T> {lhs /= rhs; return lhs;}
    template<typename T> inline auto operator==(const PixelPoint<T> &lhs, const PixelPoint<T> &rhs) -> bool {return lhs.x == rhs.x && lhs.y == rhs.y;}
    template<typename T> inline auto operator!=(const PixelPoint<T> &lhs, const PixelPoint<T> &rhs) -> bool {return lhs.x != rhs.x || lhs.y != rhs.y;}
}
#endif 
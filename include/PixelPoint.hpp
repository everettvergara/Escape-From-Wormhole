#ifndef _PIXELPOINT_HPP_
#define _PIXELPOINT_HPP_ 

#include <SDL.h>

namespace g80 {
    struct PixelPoint {
        Sint32 x;
        Sint32 y;
        auto operator+=(const PixelPoint &rhs) -> PixelPoint & {x += rhs.x; y += rhs.y; return *this;}
        auto operator-=(const PixelPoint &rhs) -> PixelPoint & {x -= rhs.x; y -= rhs.y; return *this;}
        auto operator*=(const float rhs) -> PixelPoint & {x *= rhs; y *= rhs; return *this;}
        auto operator/=(const float rhs) -> PixelPoint & {x /= rhs; y /= rhs; return *this;}
        auto abs() -> PixelPoint {PixelPoint p; p.x = x < 0 ? -x : x; p.y = y < 0 ? -y : y; return p;}
    };

    inline auto operator+(PixelPoint lhs, const PixelPoint &rhs) -> PixelPoint {lhs += rhs; return lhs;}
    inline auto operator-(PixelPoint lhs, const PixelPoint &rhs) -> PixelPoint {lhs -= rhs; return lhs;}
    inline auto operator*(PixelPoint lhs, const float rhs) -> PixelPoint {lhs *= rhs; return lhs;}
    inline auto operator/(PixelPoint lhs, const float rhs) -> PixelPoint {lhs /= rhs; return lhs;}
    inline auto operator==(const PixelPoint &lhs, const PixelPoint &rhs) -> bool {return lhs.x == rhs.x && lhs.y == rhs.y;}
    inline auto operator!=(const PixelPoint &lhs, const PixelPoint &rhs) -> bool {return lhs.x != rhs.x || lhs.y != rhs.y;}
}
#endif 
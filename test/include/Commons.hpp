#ifndef _COMMONS_HPP_
#define _COMMONS_HPP_

#include <SDL.h>
#include "EmptyAllocator.hpp"

namespace g80 {

    using Dim = Sint32;
    using UDim = Uint32;
    struct Point {
        Dim x;
        Dim y;

        auto operator+=(const Point &rhs) -> Point & {x += rhs.x; y += rhs.y; return *this;}
        auto operator-=(const Point &rhs) -> Point & {x -= rhs.x; y -= rhs.y; return *this;}
        auto operator*=(const float rhs) -> Point & {x *= rhs; y *= rhs; return *this;}
        auto operator/=(const float rhs) -> Point & {x /= rhs; y /= rhs; return *this;}
    };

    inline auto operator+(Point lhs, const Point &rhs) -> Point {lhs += rhs; return lhs;}
    inline auto operator-(Point lhs, const Point &rhs) -> Point {lhs -= rhs; return lhs;}
    inline auto operator*(Point lhs, const float rhs) -> Point {lhs *= rhs; return lhs;}
    inline auto operator/(Point lhs, const float rhs) -> Point {lhs /= rhs; return lhs;}
    inline auto operator==(const Point &lhs, const Point &rhs) -> bool {return lhs.x == rhs.x && lhs.y == rhs.y;}
    inline auto operator!=(const Point &lhs, const Point &rhs) -> bool {return lhs.x != rhs.x || lhs.y != rhs.y;}
    
    using RGBAColor = Uint32;
    using Color = Uint8;
    using Floats = std::vector<float, EmptyAllocator<float>>; 
    
}

#endif
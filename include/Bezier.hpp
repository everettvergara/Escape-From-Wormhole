#ifndef _BEZIER_HPP_
#define _BEZIER_HPP_
#include <SDL.h>
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
    
    using Color = Uint32;

    class QuadBezierAnim {
    public:
        QuadBezierAnim(const Point &p1, const Point &p2, const Point &p3, const Dim smax) : 
        p1_(p1), p2_(p2), p3_(p3), 
        d1_(p2_ - p1_), d2_(p3_ - p2_), size_per_step_(1.0f / (smax - 1)) {}

        auto next() -> Point & {
            Point d1 = d1_ * s_;
            Point d2 = d2_ * s_;
            Point c1 = p1_ + d1;
            Point c2 = p2_ + d2;
            Point dc = (c2 - c1) * s_;
            bz_ = c1 + dc;
            s_ += size_per_step_;
            return bz_;
        }

    private:
        Point p1_, p2_, p3_, d1_, d2_, bz_;
        float s_{0.0f}, size_per_step_;
        
    };
}
#endif 
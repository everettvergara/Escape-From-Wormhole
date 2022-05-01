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
    };

    inline auto operator+(Point lhs, const Point &rhs) -> Point {lhs += rhs; return lhs;}
    inline auto operator-(Point lhs, const Point &rhs) -> Point {lhs -= rhs; return lhs;}
    inline auto operator==(const Point &lhs, const Point &rhs) -> bool {return lhs.x == rhs.x && lhs.y == rhs.y;}
    inline auto operator!=(const Point &lhs, const Point &rhs) -> bool {return lhs.x != rhs.x || lhs.y != rhs.y;}
    using Color = Uint32;

    class QuadBezier {
    public:
        QuadBezier(const Point &p1, const Point &p2, const Point &p3, const Dim smax) : 
        p1_(p1), p2_(p2), p3_(p3), smax_(smax), d1_(p2_ - p1_), d2_(p3_ - p2_) {}

        auto next() -> Point & {
            Point c1, c2;
            c1.x = p1_.x + d1_.x * s_ / smax_;
            c1.y = p1_.y + d1_.y * s_ / smax_;
            c2.x = p2_.x + d2_.x * s_ / smax_;
            c2.y = p2_.y + d2_.y * s_ / smax_;
            
            Point dc = c2 - c1;
            bz_.x = c1.x + dc.x * s_ / smax_;
            bz_.y = c1.x + dc.y * s_ / smax_;
            ++s_;
            return bz_;
        }

    private:
        Point p1_, p2_, p3_;
        Dim s_{0}, smax_;
        Point d1_, d2_, bz_;
        
    };
}
#endif 
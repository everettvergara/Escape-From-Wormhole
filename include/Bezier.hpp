#ifndef _BEZIER_HPP_
#define _BEZIER_HPP_
#include <SDL.h>
namespace g80 {

    using Dim = Sint32;
    using UDim = Uint32;
    struct Point {
        Dim x;
        Dim y;

        auto operator+(const Point &rhs) -> Point {
            Point p;
            p.x = x + rhs.x;
            p.y = y + rhs.y;
            return p;
        }
        auto operator-(const Point &rhs) -> Point {
            Point p;
            p.x = x - rhs.x;
            p.y = y - rhs.y;
            return p;
        }
        auto operator==(const Point &rhs) -> bool {
            return x == rhs.x && y == rhs.y;
        }
    };
    using Color = Uint32;

    class QuadBezier {
    public:
        QuadBezier(const Point &p1, const Point &p2, const Point &p3, const Dim smax) : 
        p1_(p1), p2_(p2), p3_(p3), smax_(smax), d1_(p2_ - p1_), d2_(p3_ - p2_) {}

        auto next() -> Point & {
            Point c1, c2;
            c1.x = p1.x + d1.x * s / smax;
            c1.y = p1.y + d1.y * s / smax;
            c2.x = p2.x + d2.x * s / smax;
            c2.y = p2.y + d2.y * s / smax;
            
            Point dc = c2 - c1;
            Point bz;
            bz.x = c1.x + dc.x * s / smax;
            bz.y = c1.x + dc.y * s / smax;
            ++s;
            return bz;
        }

    private:
        Point p1_, p2_, p3_;
        Dim s_{0}, smax_;
        Point d1_, d2_;
        
    }
}
#endif 
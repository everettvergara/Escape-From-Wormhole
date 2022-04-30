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

    // class Bezier {
    // public:
        

    // private:
    //     Point p1, p2, p3;
    //     Dim s, smax;
    // }
}
#endif 
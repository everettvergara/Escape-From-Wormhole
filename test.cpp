#include <iostream>
#include "base_point.hpp"

auto main() -> int {

    g80::video::base_point<int> point(10, 20);
    g80::video::base_point<int> point2 = std::move(point);
    return 0;
}
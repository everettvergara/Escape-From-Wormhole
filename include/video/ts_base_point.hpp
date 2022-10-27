#pragma once


#include <tuple>
#include <vector>
#include <cstdlib>
#include "tdd/scenario.hpp"
#include "tdd/script.hpp"
#include "base_point.hpp"

namespace g80::worm::tdd {

    using namespace g80::tdd;

    template<typename T>
    class ts_base_point : public scenario {
    private:

        static constexpr T N{100};
        static constexpr T O{std::is_signed_v<T> ? -N/4 : 0};
        std::vector<std::tuple<T, T>> xys_;

        auto init(const size_t t) -> bool {
            xys_.reserve(t);
            for(size_t i{0}; i < t; ++i) {
                T x{N % (N/2) - O}, y{N % (N/2) - O};
                xys_.emplace_back(std::tuple<T, T>(x, y));
                std::cout << "x: " << x << ", " << y << "\n";
            }
            return true;
        }

    public:

        ts_base_point(const wchar_t *name) : 
            scenario(name) {
            add_script(script(L"Initialization", std::bind(&ts_base_point::init, this)));
        }
    };
}


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

        std::vector<std::tuple<T, T>> xys_;

        auto init(const size_t t) -> void {
            
            xys_.reserve(t);
            for(size_t i{0}; i < t; ++i) {
                T x{100 % }, y;
                xys_.emplace_back(std::tuple<T, T>(x, y));
            }
        }

    public:

        ts_base_point(const wchar_t *name) : 
            scenario(name) {
            // add_script(script(L"Always True", std::bind(&ts_scenario::always_true, this)));
        }
    };
}
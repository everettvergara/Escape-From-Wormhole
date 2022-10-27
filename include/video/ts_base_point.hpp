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
        static constexpr T N{10};
        static constexpr T M{100};
        static constexpr T O{std::is_signed_v<T> ? M/2 : 0};
        std::vector<std::tuple<T, T>> xys_;

        auto init() -> bool {
            xys_.reserve(N);
            for(size_t i{0}; i < N; ++i) {
                T x{static_cast<T>(1.0f * rand() / RAND_MAX * M - O)};
                T y{static_cast<T>(1.0f * rand() / RAND_MAX * M - O)};
                xys_.emplace_back(std::tuple<T, T>(x, y));

            }
            return true;
        }

    public:

        ts_base_point(const wchar_t *name) : 
            scenario(name) {
            
            add_script(script(L"Initialization", std::bind(&ts_base_point<T>::init, this)));
        }
    };
}


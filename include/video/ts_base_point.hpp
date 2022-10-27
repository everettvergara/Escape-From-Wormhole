#pragma once


#include <tuple>
#include <vector>
#include <cstdlib>
#include <memory>
#include "tdd/scenario.hpp"
#include "tdd/script.hpp"
#include "base_point.hpp"

namespace g80::worm::tdd {

    using namespace g80::tdd;
    using namespace g80::video;

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

    private:

        std::vector<std::unique_ptr<base_point<T>>> points_;

        auto constructor() -> bool {
            auto check{0};
            for(const auto &xy : xys_) {
                const auto &p = points_.emplace_back(std::make_unique<base_point<T>>(std::get<0>(xy), std::get<1>(xy)));
                check += p->x == std::get<0>(xy) && p->y == std::get<1>(xy);
            }
            return check == N;
        }

        auto cast_conversion_int64() -> bool {
            auto check{0};
            
            for(auto &p : points_) {
                base_point<int64_t> p64 = static_cast<base_point<int64_t>>(*p);
                check += p64.x == static_cast<int64_t>(p->x) && p64.y == static_cast<int64_t>(p->y);
            }
            return check == N;
        }


    public:

        ts_base_point(const wchar_t *name) : 
            scenario(name) {
            
            add_script(script(L"Initialization", std::bind(&ts_base_point<T>::init, this)));
            add_script(script(L"Constructor base_point<T>(ix, iy)", std::bind(&ts_base_point<T>::constructor, this)));
            add_script(script(L"Type cast cast_conversion_int64", std::bind(&ts_base_point<T>::cast_conversion_int64, this)));
        }
    };
}


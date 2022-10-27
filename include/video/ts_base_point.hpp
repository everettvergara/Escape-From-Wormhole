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

        auto cast_conversion() -> bool {
            auto check{0};
            for(const auto &p : points_) {
                base_point<int64_t> p64 = static_cast<base_point<int64_t>>(*p);
                base_point<int32_t> p32 = static_cast<base_point<int32_t>>(*p);
                base_point<int16_t> p16 = static_cast<base_point<int16_t>>(*p);
                base_point<int8_t> p8 = static_cast<base_point<int8_t>>(*p);
                base_point<uint64_t> pu64 = static_cast<base_point<uint64_t>>(*p);
                base_point<uint32_t> pu32 = static_cast<base_point<uint32_t>>(*p);
                base_point<uint16_t> pu16 = static_cast<base_point<uint16_t>>(*p);
                base_point<uint8_t> pu8 = static_cast<base_point<uint8_t>>(*p);
                base_point<float> pf = static_cast<base_point<float>>(*p);
                base_point<double> pd = static_cast<base_point<double>>(*p);
                base_point<long double> pld = static_cast<base_point<long double>>(*p);
                check += p64.x == static_cast<int64_t>(p->x) && p64.y == static_cast<int64_t>(p->y);
                check += p32.x == static_cast<int32_t>(p->x) && p32.y == static_cast<int32_t>(p->y);
                check += p16.x == static_cast<int16_t>(p->x) && p16.y == static_cast<int16_t>(p->y);
                check += p8.x == static_cast<int8_t>(p->x) && p8.y == static_cast<int8_t>(p->y);
                check += pu64.x == static_cast<uint64_t>(p->x) && pu64.y == static_cast<uint64_t>(p->y);
                check += pu32.x == static_cast<uint32_t>(p->x) && pu32.y == static_cast<uint32_t>(p->y);
                check += pu16.x == static_cast<uint16_t>(p->x) && pu16.y == static_cast<uint16_t>(p->y);
                check += pu8.x == static_cast<uint8_t>(p->x) && pu8.y == static_cast<uint8_t>(p->y);
                check += pf.x == static_cast<float>(p->x) && pf.y == static_cast<float>(p->y);
                check += pd.x == static_cast<double>(p->x) && pd.y == static_cast<double>(p->y);
                check += pld.x == static_cast<long double>(p->x) && pld.y == static_cast<long double>(p->y);
            }
            return check == N * 11;
        }

        auto add_binary_op() -> bool {
            auto check{0};
            for(const auto &p : points_) {
                auto copy_point = *p;
                T x{static_cast<T>(1.0f * rand() / RAND_MAX * M - O)};
                T y{static_cast<T>(1.0f * rand() / RAND_MAX * M - O)};
                base_point<T> random_point{x, y};
                copy_point += random_point;
                check += copy_point.x == p->x + x && copy_point.y == p->y + y;
            }
            return check == N;
        }

        auto sub_binary_op() -> bool {
            auto check{0};
            for(const auto &p : points_) {
                auto copy_point = *p;
                T x{static_cast<T>(1.0f * rand() / RAND_MAX * M - O)};
                T y{static_cast<T>(1.0f * rand() / RAND_MAX * M - O)};
                base_point<T> random_point{x, y};
                copy_point -= random_point;
                check += copy_point.x == p->x - x && copy_point.y == p->y - y;
            }
            return check == N;
        }

        auto mul_binary_op() -> bool {
            auto check{0};
            for(const auto &p : points_) {
                auto copy_point = *p;
                T x{static_cast<T>(1.0f * rand() / RAND_MAX * M - O)};
                T y{static_cast<T>(1.0f * rand() / RAND_MAX * M - O)};
                base_point<T> random_point{x, y};
                copy_point *= random_point;
                check += copy_point.x == p->x * x && copy_point.y == p->y * y;
            }
            return check == N;
        }

        auto mul_scalar_binary_op() -> bool {
            auto check{0};
            for(const auto &p : points_) {
                auto copy_point = *p;
                T s{static_cast<T>(1.0f * rand() / RAND_MAX * M - O)};
                copy_point *= s;
                check += copy_point.x == p->x * s && copy_point.y == p->y * s;
            }
            return check == N;
        }

        auto div_binary_op() -> bool {
            auto check{0};
            for(const auto &p : points_) {
                auto copy_point = *p;
                T x{static_cast<T>(1.0f * rand() / RAND_MAX * M - O)};
                T y{static_cast<T>(1.0f * rand() / RAND_MAX * M - O)};
                if(x == 0) x = 1;
                if(y == 0) y = 1;
                base_point<T> random_point{x, y};
                copy_point /= random_point;
                check += copy_point.x == p->x / x && copy_point.y == p->y / y;
            }
            return check == N;
        }

        auto div_scalar_binary_op() -> bool {
            auto check{0};
            for(const auto &p : points_) {
                auto copy_point = *p;
                T s{static_cast<T>(1.0f * rand() / RAND_MAX * M - O)};
                if(s == 0) s = 1;
                copy_point /= s;
                check += copy_point.x == p->x / s && copy_point.y == p->y / s;
            }
            return check == N;
        }

        auto abs_op() -> bool {
            auto check{0};
            for(const auto &p : points_) {
                auto copy_point = (*p).abs();
                copy_point *= -1;
                auto abs_copy = copy_point.abs();
                check += abs_copy.x == (p->x < 0 ? -p->x : p->x) && abs_copy.y == (p->y < 0 ? -p->y : p->y);
            }
            return check == N;
        }

    public:

        ts_base_point(const wchar_t *name) : 
            scenario(name) {
            
            add_script(script(L"Initialization", std::bind(&ts_base_point<T>::init, this)));
            add_script(script(L"Constructor base_point<T>(ix, iy)", std::bind(&ts_base_point<T>::constructor, this)));
            add_script(script(L"Type cast cast_conversion", std::bind(&ts_base_point<T>::cast_conversion, this)));
            add_script(script(L"Add Point binary op (+=)", std::bind(&ts_base_point<T>::cast_conversion, this)));
            add_script(script(L"Sub Point binary op (-=)", std::bind(&ts_base_point<T>::sub_binary_op, this)));
            add_script(script(L"Mul Point binary op (*=)", std::bind(&ts_base_point<T>::mul_binary_op, this)));
            add_script(script(L"Mul Scalar binary op (*=)", std::bind(&ts_base_point<T>::mul_scalar_binary_op, this)));
            add_script(script(L"Div Point binary op (*=)", std::bind(&ts_base_point<T>::div_binary_op, this)));
            add_script(script(L"Div Scalar binary op (*=)", std::bind(&ts_base_point<T>::div_scalar_binary_op, this)));
            add_script(script(L"Absolute copy op", std::bind(&ts_base_point<T>::abs_op, this)));
        }
    };
}


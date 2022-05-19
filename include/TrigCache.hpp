#ifndef _TRIGCACHE_HPP_
#define _TRIGCACHE_HPP_

#include <vector>
#include <cassert>
#include <type_traits>
#include <SDL.h>
#include "EmptyAllocator.hpp"

namespace g80 {

    template<typename T>
    using AngleValues = std::vector<T, EmptyAllocator<T>>;

    template<typename T>
    class TrigCache {
    static_assert(
        std::is_same<float, T>::value || 
        std::is_same<double, T>::value ||
        std::is_same<long double, T>::value, 
        "Trig Cache must have a floating-point type");

    public:
        TrigCache(Sint32 N) {
        }

        auto operator[](int i) -> T & {
            return angle_values_[i];
        } 

        auto operator[](int i) const -> const T & {
            return angle_values_[i];
        } 

        auto get_size() const -> const size_t {
            return angle_values_.size();
        }

    protected:
        AngleValues<T> angle_values_;
    };

    template<typename T>
    class SinCache : public TrigCache<T> {
    public:
        SinCache(Sint32 N) : TrigCache<T>(N) {
            this->angle_values_.reserve(N);
            T a = 0.0f;
            T ainc = 2.0f * M_PI / N;
            for (int i = 0; i < N; ++i, a += ainc) 
                this->angle_values_.emplace_back(SDL_sin(a));
        }
    };

    template<typename T>
    class CosCache : public TrigCache<T> {
    public:
        CosCache(Sint32 N) : TrigCache<T>(N) {
            this->angle_values_.reserve(N);
            T a = 0.0f;
            T ainc = 2.0f * M_PI / N;
            for (int i = 0; i < N; ++i, a += ainc)
                this->angle_values_.emplace_back(SDL_cos(a));
        }
    };
}

#endif 
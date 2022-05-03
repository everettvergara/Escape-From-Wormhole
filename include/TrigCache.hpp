#ifndef _TRIGCACHE_HPP_
#define _TRIGCACHE_HPP_

#include "Commons.hpp"
#include <vector>
#include <cassert>
#include <type_traits>
#include <EmptyAllocator.hpp>

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
        TrigCache(Dim N) {
            angle_values_.reserve(N);
        }

        auto operator[](int i) -> T & {
            return angle_values_[i];
        } 

    protected:
        AngleValues<T> angle_values_;
    };

    class SinCacheF : public TrigCache<float> {
    public:
        SinCacheF(Dim N) : TrigCache(N) {
            float a = 0.0f;
            float ainc = 2.0f * M_PI / N;
            for (int i = 0; i < N; ++i, a += ainc)
                angle_values_[i] = SDL_sinf(a);
        }
    };

    class SinCache : public TrigCache<double> {
    public:
        SinCache(Dim N) : TrigCache(N) {
            double a = 0.0f;
            double ainc = 2.0f * M_PI / N;
            for (int i = 0; i < N; ++i, a += ainc)
                angle_values_[i] = SDL_sin(a);
        }
    };

    class CosCacheF : public TrigCache<float> {
    public:
        CosCacheF(Dim N) : TrigCache(N) {
            float a = 0.0f;
            float ainc = 2.0f * M_PI / N;
            for (int i = 0; i < N; ++i, a += ainc)
                angle_values_[i] = SDL_cosf(a);
        }
    };

    class CosCache : public TrigCache<double> {
    public:
        CosCache(Dim N) : TrigCache(N) {
            double a = 0.0f;
            double ainc = 2.0f * M_PI / N;
            for (int i = 0; i < N; ++i, a += ainc)
                angle_values_[i] = SDL_cos(a);
        }
    };
}

#endif 
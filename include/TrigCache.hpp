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
            angle_values_.reserve(N);
        }

        auto operator[](int i) -> T & {
            return angle_values_[i];
        } 

        auto operator[](int i) const -> const T & {
            return angle_values_[i];
        } 

    protected:
        AngleValues<T> angle_values_;
    };

    class SinCacheF : public TrigCache<float> {
    public:
        SinCacheF(Sint32 N) : TrigCache(N) {
            float a = 0.0f;
            float ainc = 2.0f * M_PI / N;
            for (int i = 0; i < N; ++i, a += ainc)
                angle_values_[i] = SDL_sinf(a);
        }
    };

    class SinCache : public TrigCache<double> {
    public:
        SinCache(Sint32 N) : TrigCache(N) {
            double a = 0.0f;
            double ainc = 2.0f * M_PI / N;
            for (int i = 0; i < N; ++i, a += ainc)
                angle_values_[i] = SDL_sin(a);
        }
    };

    class CosCacheF : public TrigCache<float> {
    public:
        CosCacheF(Sint32 N) : TrigCache(N) {
            float a = 0.0f;
            float ainc = 2.0f * M_PI / N;
            for (int i = 0; i < N; ++i, a += ainc)
                angle_values_[i] = SDL_cosf(a);
        }
    };

    class CosCache : public TrigCache<double> {
    public:
        CosCache(Sint32 N) : TrigCache(N) {
            double a = 0.0f;
            double ainc = 2.0f * M_PI / N;
            for (int i = 0; i < N; ++i, a += ainc)
                angle_values_[i] = SDL_cos(a);
        }
    };
}

#endif 
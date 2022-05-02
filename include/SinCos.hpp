#ifndef _SINCOS_HPP_
#define _SINCOS_HPP_

#include "Commons.hpp"
#include <vector>
#include <EmptyAllocator.hpp>

namespace g80 {

    template<typename FT>
    using AngleValues = std::vector<FT, EmptyAllocator<FT>>;

    template<typename FT>
    class TrigCache {
    public:
        TrigCache(Dim N) : N_(N) {
            angle_values_.reserve(N_);
        } 

        auto operator[](int i) -> FT & {
            return angle_values_[i];
        } 

    protected:
        Dim N_;
        AngleValues<FT> angle_values_;
    };

    class SinCacheF : public TrigCache<float> {
    public:
        SinCacheF(Dim N) : TrigCache(N) {
            float a = 0.0f;
            float ainc = 2.0f * M_PI / N_;
            for (int i = 0; i < N_; ++i, a += ainc)
                angle_values_[i] = SDL_sinf(a);
        }
    };

    class SinCache : public TrigCache<double> {
    public:
        SinCache(Dim N) : TrigCache(N) {
            double a = 0.0f;
            double ainc = 2.0f * M_PI / N_;
            for (int i = 0; i < N_; ++i, a += ainc)
                angle_values_[i] = SDL_sin(a);
        }
    };

    class CosCacheF : public TrigCache<float> {
    public:
        CosCacheF(Dim N) : TrigCache(N) {
            float a = 0.0f;
            float ainc = 2.0f * M_PI / N_;
            for (int i = 0; i < N_; ++i, a += ainc)
                angle_values_[i] = SDL_cosf(a);
        }
    };

    class CosCache : public TrigCache<double> {
    public:
        CosCache(Dim N) : TrigCache(N) {
            double a = 0.0f;
            double ainc = 2.0f * M_PI / N_;
            for (int i = 0; i < N_; ++i, a += ainc)
                angle_values_[i] = SDL_cos(a);
        }
    };
}

#endif 
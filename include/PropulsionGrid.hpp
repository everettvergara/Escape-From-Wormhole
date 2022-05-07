#ifndef _PROPULSIONGRID_HPP_
#define _PROPULSIONGRID_HPP_

#include "Commons.hpp"
#include "TrigCache.hpp"
#include "EmptyAllocator.hpp"

namespace g80 {

    using VectorAngles = std::vector<float, EmptyAllocator<float>>;
    using VectorMagnitudes = std::vector<float, EmptyAllocator<float>>;

    class PropulsionGrid {

    public:
        PropulsionGrid(Dim width, Dim height) : 
            width_(width), 
            height_(height),
            size_(width_ * height_) {
   
            angles_.reserve(size_);
            magnitudes_.reserve(size_);
        }
        
        inline auto ix(Dim x, Dim y) -> Dim {
            return y * width_ + x; 
        }

        inline auto set_angle(Dim ix, float angle) -> void {
            angles_[ix] = angle;
        }

        inline auto set_magnitude(Dim ix, float magnitude) -> void {
            magnitudes_[ix] = magnitude;
        }

    private:
        Dim width_, height_, size_;
        VectorAngles angles_;
        VectorMagnitudes magnitudes_;

        SinCacheF sin360_{360};
        CosCacheF cos360_{360};

    };
}

#endif 
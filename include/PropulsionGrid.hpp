#ifndef _PROPULSIONGRID_HPP_
#define _PROPULSIONGRID_HPP_

#include "Commons.hpp"
#include "TrigCache.hpp"
#include "EmptyAllocator.hpp"

namespace g80 {

    using VectorAngles = std::vector<Dim, EmptyAllocator<Dim>>;
    using VectorMagnitudes = std::vector<float>;

    class PropulsionGrid {

    public:
        PropulsionGrid(Dim width, Dim height) : 
            width_(width), 
            height_(height),
            size_(width_ * height_),
            magnitudes_(size_, 50.0f),
            min_magnitude_(50.0f) {
            
            angles_.reserve(size_);
            Dim cx = width_ / 2;
            Dim cy = height_ / 2;
            for (Dim y = 0; y < height_; ++y) {
                for (Dim x = 0; x < width_; ++x) {
                    Dim dx = x - cx;
                    Dim dy = y - cy;
                    float angle = SDL_atan2f(dy, dx);
                    if (angle < 0) angle = M_PI * 2 + angle;
                    Dim angle_int = 360.0f *  angle / (M_PI * 2);
                    angles_.push_back(angle_int);
                }
            }
        }
        
        inline auto get_width() -> Dim {
            return width_;
        }
        
        inline auto get_height() -> Dim {
            return height_;
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

        inline auto reduce_magnitude(Dim ix, float reduce) -> void {
            if (magnitudes_[ix]>= min_magnitude_) magnitudes_[ix] *= reduce;
        }

        inline auto get_angle(Dim ix) const -> const Dim & {
            return angles_[ix];
        }

        inline auto get_magnitude(Dim ix) const -> const float & {
            return magnitudes_[ix];
        }

        auto get_angles() const -> const VectorAngles & {
            return angles_;
        }

        auto get_magnitudes() const -> const VectorMagnitudes & {
            return magnitudes_;
        }

        inline auto get_vector_x(Dim ix) const -> const float {
            return cos360_[angles_[ix]] * magnitudes_[ix];
        }

        inline auto get_vector_y(Dim ix) const -> const float {
            return sin360_[angles_[ix]] * magnitudes_[ix];
        }

    private:
        Dim width_, height_, size_;
        VectorAngles angles_;
        VectorMagnitudes magnitudes_;
        float min_magnitude_;

        SinCacheF sin360_{360};
        CosCacheF cos360_{360};

    };
}

#endif 
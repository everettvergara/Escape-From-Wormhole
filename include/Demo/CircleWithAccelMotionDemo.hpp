#ifndef _CIRCLEWITHACCELMOTIONDEMO_HPP_
#define _CIRCLEWITHACCELMOTIONDEMO_HPP_

#include <cstdlib>

#include "Video.hpp"
#include "Motion/CircleWithAccelMotion.hpp"
#include "TrigCache.hpp"

namespace g80 {
    class CircleWithAccelMotionDemo : public Video {
    public:
        CircleWithAccelMotionDemo();

        auto preprocess_states() -> bool;
        auto update_states() -> bool; 

    private:
        const Sint32 TN_{3600}, N_{1};
        SinCache<float> sine_{TN_};
        CosCache<float> cosine_{TN_};      
        std::vector<CircleWithAccelMotion<float>> whirls_;
        Palette pal_;
    };

    CircleWithAccelMotionDemo::CircleWithAccelMotionDemo() : Video() {

    }

    auto CircleWithAccelMotionDemo::preprocess_states() -> bool {

/*
            const Point<T> &p, 
            const Sint32 radius,
            const Sint32 sz_steps,
            const Sint32 sz_trail,
            const Sint32 start_ix, 
            const Sint32 end_ix, 
            const CosCache<T> &cosine_cache,
            const SinCache<T> &sine_cache) {
*/

        whirls_.reserve(N_);
        for (int i = 0; i < N_; ++i) {
            whirls_.emplace_back();
            whirls_[i].circle_with_accel_motion_set(
                Point<float>{static_cast<float>(surface_->w / 2.0f), static_cast<float>(surface_->h / 2.0f)},
                350, 100, 2, 0, 3599, cosine_, sine_);
        } 

        pal_.add_gradients(surface_->format, 
            {
                {0, SDL_MapRGBA(surface_->format, 0, 255, 255, 255)},
                {60, SDL_MapRGBA(surface_->format, 0, 100, 255, 255)},
                {120, SDL_MapRGBA(surface_->format, 100, 255, 255, 255)},
                {180, SDL_MapRGBA(surface_->format, 50, 255, 50, 255)},
                {300, SDL_MapRGBA(surface_->format, 255, 255, 255, 255)},});
        return true;
    }

    auto CircleWithAccelMotionDemo::update_states() -> bool {

        // Erase
        SDL_FillRect(surface_, NULL, 0);
        
        // Draw
        for (auto &w : whirls_) {
            Sint32 size_of_trail = w.get_head_step() - w.get_tail_step();
            line(w.get_head(), w.get_tail(), pal_[static_cast<int>(300.0f * (w.get_tail_step()  / (w.get_size_of_step() + size_of_trail))]);  
        }

        for (int i = 0; i < N_; ++i) {
            if (!whirls_[i].next(cosine_, sine_)) {
                whirls_[i].circle_with_accel_motion_set(
                Point<float>{static_cast<float>(surface_->w / 2.0f), static_cast<float>(surface_->h / 2.0f)},
                350, 100, 2, 0, 3599, cosine_, sine_);
            }
        } 

        return true;
    }
}

#endif 
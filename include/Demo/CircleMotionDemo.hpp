#ifndef _CIRCLEMOTIONDEMO_HPP_
#define _CIRCLEMOTIONDEMO_HPP_

#include <cstdlib>

#include "Video.hpp"
#include "Motion/CircleMotion.hpp"
#include "TrigCache.hpp"

namespace g80 {
    class CircleMotionDemo : public Video {
    public:
        CircleMotionDemo();

        auto preprocess_states() -> bool;
        auto update_states() -> bool; 

    private:
        const Sint32 TN_{3600}, N_{10000};
        SinCache<float> sine_{TN_};
        CosCache<float> cosine_{TN_};      
        std::vector<CircleMotion<float>> whirls_;
        Palette pal_;
    };

    CircleMotionDemo::CircleMotionDemo() : Video() {

    }

    auto CircleMotionDemo::preprocess_states() -> bool {

        whirls_.reserve(N_);
        for (int i = 0; i < N_; ++i) {
            whirls_.emplace_back();
            whirls_[i].circle_motion_set(
                Point<float>{static_cast<float>(rand() % surface_->w), static_cast<float>(rand() % surface_->h)},
                10 + rand() % 100, rand() % 1000, 10, rand() % 3600, rand() % 3600, cosine_, sine_);
        } 

        pal_.add_gradients(surface_->format, 
            {
                {0, SDL_MapRGBA(surface_->format, 0, 255, 255, 255)},
                {60, SDL_MapRGBA(surface_->format, 0, 100, 255, 255)},
                {120, SDL_MapRGBA(surface_->format, 100, 100, 255, 255)},
                {180, SDL_MapRGBA(surface_->format, 255, 0, 255, 255)},
                {300, SDL_MapRGBA(surface_->format, 255, 255, 255, 255)},});
        return true;
    }

    auto CircleMotionDemo::update_states() -> bool {
        // Erase
        SDL_FillRect(surface_, NULL, 0);
        
        // Draw
        for (auto &w : whirls_) {
            Sint32 size_of_trail = w.get_head_step() - w.get_tail_step();
            line(w.get_head(), w.get_tail(), pal_[static_cast<int>(300.0f * (w.get_tail_step() + size_of_trail) / (w.get_size_of_step() + size_of_trail))]);  
        }

        for (auto &w : whirls_) {
            if (!w.next(cosine_, sine_)) {
                w.circle_motion_set(
                    Point<float>{static_cast<float>(rand() % surface_->w), static_cast<float>(rand() % surface_->h)},
                    10 + rand() % 100, rand() % 1000, 10, rand() % 3600, rand() % 3600, cosine_, sine_);
            }  
        }

        return true;
    }
}

#endif 
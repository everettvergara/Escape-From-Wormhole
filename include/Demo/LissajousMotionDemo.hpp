#ifndef LISSAJOUS_MOTION_DEMO
#define LISSAJOUS_MOTION_DEMO

#include <cstdlib>
#include <vector>
#include "Video.hpp"
#include "Motion/LissajousMotion.hpp"
#include "TrigCache.hpp"
#include "LCMRND.hpp"

namespace g80 {
    class LissajousMotionDemo : public Video {
    public:
        LissajousMotionDemo();

        auto preprocess_states() -> bool;
        auto update_states() -> bool; 

    private:
        const Sint32 TN_{3600}, N_{1000};
        SinCache<float> sine_{TN_};
        CosCache<float> cosine_{TN_};      
        std::vector<LissajousMotion<float>> whirls_;
        Palette pal_;
    };

    LissajousMotionDemo::LissajousMotionDemo() : Video() {

    }

    auto LissajousMotionDemo::preprocess_states() -> bool {

        whirls_.reserve(N_);
        for (int i = 0; i < N_; ++i) {
            whirls_.emplace_back();
            
            float angle_x = 100.0f * (lcm_rnd() % 1000);
            float angle_y = 100.0f * (lcm_rnd() % 1000);

            whirls_[i].lissajous_motion_set(
                    Lissajous<float> {
                        Point<float>{static_cast<float>(lcm_rnd() % 1280), static_cast<float>(lcm_rnd() % 720)},
                        100.0f + (lcm_rnd() % 300), 100.0f + (lcm_rnd() % 300),
                        angle_x, angle_y,
                        angle_x + (lcm_rnd() % 3600), angle_y + (lcm_rnd() % 3600)},
                    100, 10, cosine_, sine_);
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

    auto LissajousMotionDemo::update_states() -> bool {

        // Erase
        SDL_FillRect(surface_, NULL, 0);
        
        // Draw
        for (auto &w : whirls_) {
            Sint32 size_of_trail = w.get_head_step() - w.get_tail_step();
            //pset(w.get_head(), pal_[static_cast<int>(300.0f * (w.get_tail_step() + size_of_trail) / (w.get_size_of_step() + size_of_trail))]);  
            line(w.get_head(), w.get_tail(), pal_[static_cast<int>(300.0f * (w.get_tail_step() + size_of_trail) / (w.get_size_of_step() + size_of_trail))]);  
        }

        for (auto &w : whirls_) {
            if (!w.next(cosine_, sine_)) {

                float angle_x = 100.0f * (lcm_rnd() % 1000);
                float angle_y = 100.0f * (lcm_rnd() % 1000);

                w.lissajous_motion_set(
                    Lissajous<float> {
                        Point<float>{static_cast<float>(lcm_rnd() % 1280), static_cast<float>(lcm_rnd() % 720)},
                        100.0f + (lcm_rnd() % 300), 100.0f + (lcm_rnd() % 300),
                        angle_x, angle_y,
                        angle_x + (lcm_rnd() % 3600), angle_y + (lcm_rnd() % 3600)},
                    100, 10, cosine_, sine_);
                } 
            }  
        return true;
    }
}

#endif 
#ifndef QUAD_BEZIER_MOTION_DEMO_HPP
#define QUAD_BEZIER_MOTION_DEMO_HPP

#include <vector>
#include "Video.hpp"
#include "QuadBezierMotion.hpp"
#include "TrigCache.hpp"
#include "LCMRND.hpp"


namespace g80 {
    class QuadBezierMotionDemo : public Video {
    public:
        QuadBezierMotionDemo();

        auto preprocess_states() -> bool;
        auto update_states() -> bool;

        /*
        virtual auto create_window(const VideoConfig &video_config) -> bool;
        virtual auto destroy_window() -> void;
        virtual auto preprocess_states() -> bool;
        virtual auto run() -> bool;
        virtual auto capture_events() -> bool;
        virtual auto update_states() -> bool;
        virtual auto update_window_surface() -> bool;
        */

       auto capture_events() -> bool;

    private:
        const Sint32 TrigCacheN_{3600};
        CosCache<float> cosine_{TrigCacheN_};
        SinCache<float> sine_{TrigCacheN_};
        float inner_radius_{50}, mid_radius_{350}, outer_radius_{700};
        
        std::vector<QuadBezierMotion<float>> quad_bezier_motion_;
    };

    QuadBezierMotionDemo::QuadBezierMotionDemo() : Video() {

    }

    auto QuadBezierMotionDemo::preprocess_states() -> bool {
        
        quad_bezier_motion_.reserve(TrigCacheN_);
        for (Sint32 i = 0; i < TrigCacheN_; ++i) {
            quad_bezier_motion_.emplace_back();

            Point<float> p1, p2, p3;
            p1.x = surface_->w + inner_radius_ * cosine_[i];  
            p1.y = surface_->h / 2 + inner_radius_ * sine_[i];  

            p2.x = surface_->w / 2 + mid_radius_ * cosine_[i];  
            p2.y = surface_->h / 2 + mid_radius_ * sine_[i];  

            p3.x = surface_->w / 2 + outer_radius_ * cosine_[i];  
            p3.y = surface_->h / 2 + outer_radius_ * sine_[i];  

            Sint32 steps = 10 + lcm_rnd() % 100;
            Sint32 trail = 11 - steps / 110.0f;
            quad_bezier_motion_[i].quad_bezier_set(p1, p2, p3, steps, trail);
        }
        return true;
    }

    auto QuadBezierMotionDemo::update_states() -> bool {
        // Palette pal;
        // pal.add_gradients(surface_->format,
        //     {
        //         {0, SDL_MapRGBA(surface_->format, 255, 0, 0, 255)},
        //         {38, SDL_MapRGBA(surface_->format, 0, 255, 0, 255)},
        //         {75, SDL_MapRGBA(surface_->format, 0, 0, 255, 255)},
        //         {112, SDL_MapRGBA(surface_->format, 255, 255, 0, 255)},
        //         {150, SDL_MapRGBA(surface_->format, 255, 0, 255, 255)},
        //         {188, SDL_MapRGBA(surface_->format, 255, 255, 0, 255)},

        //         {226, SDL_MapRGBA(surface_->format, 0, 0, 255, 255)},                
        //         {264, SDL_MapRGBA(surface_->format, 0, 255, 0, 255)},    
        //         {300, SDL_MapRGBA(surface_->format, 255, 0, 0, 255)},
                
        //         });

        // // circle({1280/2, 720/2}, 200, SDL_MapRGBA(surface_->format, 255, 0, 0, 255));
        // circle(mouse_, r_, pal, 0, 299);
        return true;
    }

    auto QuadBezierMotionDemo::capture_events() -> bool {
        SDL_Event e;
        while(SDL_PollEvent(&e)) {
            if(e.type == SDL_QUIT)
                is_running_ = false;

            else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_ESCAPE)
                    is_running_ = false;
            }
            
            else if (e.type == SDL_MOUSEMOTION) {
                // mouse_.x = e.motion.x;
                // mouse_.y = e.motion.y;
                // if (r_ >100 || r_ <1) rn_ *= -1;
                // r_ += rn_;
                
            }
        }
        return true;
    }
}

#endif 
#ifndef BETTER_QUAD_BEZIER_MOTION_DEMO_HPP
#define BETTER_QUAD_BEZIER_MOTION_DEMO_HPP

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
       auto capture_events() -> bool;

    private:
        const Sint32 TrigCacheN_{36000};
        CosCache<float> cosine_{TrigCacheN_};
        SinCache<float> sine_{TrigCacheN_};
        Point<float> origin_;
        float inner_radius_{10}, mid_radius_{100}, outer_radius_{800};
        
        std::vector<QuadBezierMotion<float>> quad_bezier_motion_;
        std::array<int, 100> qb_priority_queue_ix;
        std::array<int, TrigCacheN_ + 1> qb_priority_queue_list;
        std::array<int, TrigCacheN_> current_priority_queue_ix;
        Palette pal_;
    };

    QuadBezierMotionDemo::QuadBezierMotionDemo() : Video() {

    }

    auto QuadBezierMotionDemo::preprocess_states() -> bool {
        
        origin_ = {static_cast<float>(surface_->w), static_cast<float>(surface_->h / 2)};
        quad_bezier_motion_.reserve(TrigCacheN_);
        qb_priority_queue_ix[0] = 0;
        for (Sint32 i = 1; i <= 99; ++i) qb_priority_queue_ix[i] = TrigCacheN_;

        for (Sint32 i = 0; i < TrigCacheN_; ++i) {
            quad_bezier_motion_.emplace_back();
            //quad_bezier_motion_

            Point<float> p1, p2, p3;
            p1.x = origin_.x + inner_radius_ * cosine_[i];  
            p1.y = origin_.y + inner_radius_ * sine_[i];  

            p2.x = surface_->w / 2 + mid_radius_ * cosine_[i];  
            p2.y = surface_->h / 2 + mid_radius_ * sine_[i];  

            p3.x = surface_->w / 2 + outer_radius_ * cosine_[i];  
            p3.y = surface_->h / 2 + outer_radius_ * sine_[i];  

            Sint32 steps = 10 + lcm_rnd() % 100;
            Sint32 trail = 1; // 11 - steps / 110.0f;
            quad_bezier_motion_[i].quad_bezier_set(p1, p2, p3, steps, trail);
            qb_priority_queue_list[i] = i + 1;
            current_priority_queue_ix[i] = 0;
        }

        pal_.add_gradients(surface_->format,
            {
                {0, SDL_MapRGBA(surface_->format, 0, 0, 0, 255)},
                {25, SDL_MapRGBA(surface_->format, 0, 0, 100, 255)},
                {50, SDL_MapRGBA(surface_->format, 0, 100, 255, 255)},
                {75, SDL_MapRGBA(surface_->format, 100, 255, 255, 255)},
                {100, SDL_MapRGBA(surface_->format, 255, 255, 255, 255)},
                
                });        
        return true;
    }

    auto QuadBezierMotionDemo::update_states() -> bool {

        SDL_FillRect(surface_, NULL, 0);

        
        for (Sint32 i = 0; i <= 99; ++i) {
            j = qb_priority_queue_ix[i];
            while (j != TrigCacheN_) {
                RGBAColor c = pal_[100 * qb.get_head_step() / qb.get_size_of_step()];
                line(quad_bezier_motion_[j].get_head(), quad_bezier_motion_[j].get_tail(), c);
                j = qb_priority_queue_list[j];
            }
        }

        for (Sint32 i = 0; i < TrigCacheN_; ++i) {

            bool next = quad_bezier_motion_[i].next();
            new_pq_ix = 99 * qb.get_head_step() / qb.get_size_of_step();

            // check if there's a need to move
            if (current_priority_queue_ix[i] != new_pq_ix) {
                current_priority_queue_ix[i] = new_pq_ix;
            }
            
        }

        // for (auto &qb : quad_bezier_motion_) {
        //     RGBAColor c = pal_[100 * qb.get_head_step() / qb.get_size_of_step()];
        //     // pset(qb.get_head(), c);
        //     line(qb.get_head(), qb.get_tail(), c);
        // }

        // for (Sint32 i = 0; i < TrigCacheN_; ++i) {
        //     if (!quad_bezier_motion_[i].next()) {
        //         Point<float> p1, p2, p3;
        //         p1.x = origin_.x + inner_radius_ * cosine_[i];  
        //         p1.y = origin_.y + inner_radius_ * sine_[i];  

        //         p2.x = surface_->w / 2 + mid_radius_ * cosine_[i];  
        //         p2.y = surface_->h / 2 + mid_radius_ * sine_[i];  

        //         p3.x = surface_->w / 2 + outer_radius_ * cosine_[i];  
        //         p3.y = surface_->h / 2 + outer_radius_ * sine_[i];  

        //         Sint32 steps = 10 + lcm_rnd() % 100;
        //         Sint32 trail = 1; //11 - steps / 110.0f;
        //         quad_bezier_motion_[i].quad_bezier_set(p1, p2, p3, steps, trail);
        //     }
        // }

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
                origin_.x = static_cast<float>(e.motion.x);
                origin_.y = static_cast<float>(e.motion.y);
            }
        }
        return true;
    }
}

#endif 
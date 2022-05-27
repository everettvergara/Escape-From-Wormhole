#ifndef BETTER_QUAD_BEZIER_MOTION_DEMO_HPP
#define BETTER_QUAD_BEZIER_MOTION_DEMO_HPP

#include <vector>
#include "Video.hpp"
#include "QuadBezierMotion.hpp"
#include "TrigCache.hpp"
#include "LCMRND.hpp"
#include "PriorityList.hpp"


namespace g80 {
    class BetterQuadBezierMotionDemo : public Video {
    public:
        BetterQuadBezierMotionDemo();

        auto preprocess_states() -> bool;
        auto update_states() -> bool;
        auto capture_events() -> bool;

    private:
        const size_t TrigCacheN_{10000};
        CosCache<float> cosine_{TrigCacheN_};
        SinCache<float> sine_{TrigCacheN_};
        Point<float> origin_;
        float inner_radius_{10}, mid_radius_{100}, outer_radius_{800};
        
        std::vector<QuadBezierMotion<float>> quad_bezier_motion_;
        Palette pal_;

        PriorityList pl_{110, TrigCacheN_};

    };

    BetterQuadBezierMotionDemo::BetterQuadBezierMotionDemo() : Video() {

    }

    auto BetterQuadBezierMotionDemo::preprocess_states() -> bool {
        
        origin_ = {static_cast<float>(surface_->w), static_cast<float>(surface_->h / 2)};
        quad_bezier_motion_.reserve(TrigCacheN_);

        for (Sint32 i = 0; i < TrigCacheN_; ++i) {
            quad_bezier_motion_.emplace_back();

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
            pl_.add(0, i);
        }

        pal_.add_gradients(surface_->format,
            {
                {0, SDL_MapRGBA(surface_->format, 100, 0, 100, 255)},
                {25, SDL_MapRGBA(surface_->format, 0, 0, 100, 255)},
                {50, SDL_MapRGBA(surface_->format, 0, 100, 255, 255)},
                {75, SDL_MapRGBA(surface_->format, 100, 255, 255, 255)},
                {100, SDL_MapRGBA(surface_->format, 255, 255, 255, 255)},
                
                });        
        return true;
    }

    auto BetterQuadBezierMotionDemo::update_states() -> bool {

        SDL_FillRect(surface_, NULL, 0);

        // for (auto &qb : quad_bezier_motion_) {
        //     RGBAColor c = pal_[100 * qb.get_head_step() / qb.get_size_of_step()];
        //     // pset(qb.get_head(), c);
        //     line(qb.get_head(), qb.get_tail(), c);
        // }

        for (size_t group = 0; group < 110; ++group) {
            auto cur = pl_.get_next_after(group);
            auto tail = pl_.get_tail_group_ix(group);
            while (cur != tail) {
                size_t i = pl_.get_node_from_nix(cur);
                RGBAColor c = pal_[100 * quad_bezier_motion_[i].get_head_step() / quad_bezier_motion_[i].get_size_of_step()];
                line(quad_bezier_motion_[i].get_head(), quad_bezier_motion_[i].get_tail(), c);
                cur = pl_.get_next_after(cur);
            }
        }

        for (Sint32 i = 0; i < TrigCacheN_; ++i) {
            auto prev = 100 * quad_bezier_motion_[i].get_head_step() / quad_bezier_motion_[i].get_size_of_step();

            if (!quad_bezier_motion_[i].next()) {
                Point<float> p1, p2, p3;
                p1.x = origin_.x + inner_radius_ * cosine_[i];  
                p1.y = origin_.y + inner_radius_ * sine_[i];  

                p2.x = surface_->w / 2 + mid_radius_ * cosine_[i];  
                p2.y = surface_->h / 2 + mid_radius_ * sine_[i];  

                p3.x = surface_->w / 2 + outer_radius_ * cosine_[i];  
                p3.y = surface_->h / 2 + outer_radius_ * sine_[i];  

                Sint32 steps = 10 + lcm_rnd() % 100;
                Sint32 trail = 1; //11 - steps / 110.0f;
                quad_bezier_motion_[i].quad_bezier_set(p1, p2, p3, steps, trail);
            }

            auto curr = 100 * quad_bezier_motion_[i].get_head_step() / quad_bezier_motion_[i].get_size_of_step();
            if (prev != curr) pl_.add(curr, i);
        }

        return true;
    }

    auto BetterQuadBezierMotionDemo::capture_events() -> bool {
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
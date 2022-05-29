#ifndef WORMHOLE_WITH_PROPULSION_DEMO_HPP
#define WORMHOLE_WITH_PROPULSION_DEMO_HPP

#include <vector>
#include "Video.hpp"
#include "QuadBezierMotion.hpp"
#include "TrigCache.hpp"
#include "LCMRND.hpp"
#include "PriorityList.hpp"
#include "PropulsionMotion.hpp"

// TODO: Create a separate demo for wormhole and combine them here for refactoring
// 

namespace g80 {
    class WormholeWithPropulsionDemo : public Video {
    public:
        WormholeWithPropulsionDemo();

        auto preprocess_states() -> bool;
        auto update_states() -> bool;
        auto capture_events() -> bool;

    private:
        const size_t TrigCacheN_{3600};
        CosCache<float> cosine_{TrigCacheN_};
        SinCache<float> sine_{TrigCacheN_};

        const size_t TrigCacheCraftN_{3600};
        CosCache<float> cosine_craft_{TrigCacheCraftN_};
        SinCache<float> sine_craft_{TrigCacheCraftN_};        
        
        Point<float> origin_, craft_, center_;
        Sint32 origin_angle_{0}, origin_radius_from_center_{1280/2};
        Sint32 origin_angle_inc_{1};
        float inner_radius_{10}, mid_radius_{100}, outer_radius_{800};
        //float corrected_prop_offset_{60};
        
        
        std::vector<QuadBezierMotion<float>> quad_bezier_motion_;
        Palette pal_, prop_pal_;

        PriorityList pl_{110, TrigCacheN_};
        PropulsionMotion<float> prop_{10, 2};


    };

    WormholeWithPropulsionDemo::WormholeWithPropulsionDemo() : Video() {

    }

    auto WormholeWithPropulsionDemo::preprocess_states() -> bool {
        
        
        center_ = {static_cast<float>(surface_->w / 2), static_cast<float>(surface_->h / 2)};
        origin_ = center_;
        origin_.x += origin_radius_from_center_;

        craft_ = origin_;
        quad_bezier_motion_.reserve(TrigCacheN_);

        for (Sint32 i = 0; i < TrigCacheN_; ++i) {
            quad_bezier_motion_.emplace_back();

            Point<float> p1, p2, p3;
            p1.x = origin_.x + inner_radius_ * cosine_[i];  
            p1.y = origin_.y + inner_radius_ * sine_[i];  

            p2.x = center_.x + mid_radius_ * cosine_[i];  
            p2.y = center_.y + mid_radius_ * sine_[i];  

            p3.x = center_.x + outer_radius_ * cosine_[i];  
            p3.y = center_.y + outer_radius_ * sine_[i];  

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

        prop_pal_.add_gradients(surface_->format,
            {
                {0, SDL_MapRGBA(surface_->format, 255, 255, 255, 255)},
                {50, SDL_MapRGBA(surface_->format, 255, 255, 0, 255)},
                {75, SDL_MapRGBA(surface_->format, 255, 0, 0, 255)},
                {100, SDL_MapRGBA(surface_->format, 50, 20, 150, 255)},
                });

        prop_.set(center_, 10, 40, mid_radius_ * 3, mid_radius_ * 3 + 300, 1000, cosine_, sine_, 0, 0);        
        
        return true;
    }

    auto WormholeWithPropulsionDemo::update_states() -> bool {

        SDL_FillRect(surface_, NULL, 0);

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

                p2.x = center_.x + mid_radius_ * cosine_[i];  
                p2.y = center_.y + mid_radius_ * sine_[i];  

                p3.x = center_.x + outer_radius_ * cosine_[i];  
                p3.y = center_.y + outer_radius_ * sine_[i];  

                Sint32 steps = 10 + lcm_rnd() % 100;
                Sint32 trail = 1; //11 - steps / 110.0f;
                quad_bezier_motion_[i].quad_bezier_set(p1, p2, p3, steps, trail);
            }

            auto curr = 100 * quad_bezier_motion_[i].get_head_step() / quad_bezier_motion_[i].get_size_of_step();
            if (prev != curr) pl_.add(curr, i);
        }

        //RGBAColor guide_c = SDL_MapRGBA(surface_->format, 255, 255, 0, 255);
        // RGBAColor corrected_c = SDL_MapRGBA(surface_->format, 0, 255, 0, 255);

        // auto angle_point = craft_ -  Point<float>(surface_->w / 2, surface_->h / 2);
        // float a = SDL_atan2f(angle_point.y, angle_point.x) / M_PI;

        // float corrected_a = a * 180.0f;
        // corrected_a = corrected_a > 90.0f ? 180 - corrected_a : (corrected_a < -90 ? -180 - corrected_a : corrected_a);
        // auto corrected_a_offset = corrected_a / 90.0f * corrected_prop_offset_;
        // auto new_a = a + corrected_a_offset;

        // auto TrigCacheCraftN_2 = TrigCacheCraftN_ / 2.0f;
        // auto TrigCacheCraftN_4 = TrigCacheCraftN_ / 4.0f;

        // float corrected_a = a * TrigCacheCraftN_2;
        // corrected_a = corrected_a > TrigCacheCraftN_4 ? TrigCacheCraftN_2 - corrected_a : (corrected_a < -TrigCacheCraftN_4 ? -TrigCacheCraftN_2 - corrected_a : corrected_a);
        // auto corrected_a_offset = corrected_a / TrigCacheCraftN_4 * corrected_prop_offset_;
        // auto new_a = a + corrected_a_offset;
        // new_a = new_a >= TrigCacheCraftN_ ? new_a - TrigCacheCraftN_ : new_a;

        // Sint32 ai = a >= 0 ? TrigCacheCraftN_ / 2.0f * a : TrigCacheCraftN_ + TrigCacheCraftN_ / 2.0f * a;
        // Sint32 ai_left = ai + 200 >= TrigCacheCraftN_ ? ai + 200 - TrigCacheCraftN_ : ai + 200;
        // Sint32 ai_right =  ai - 200 < 0 ? TrigCacheCraftN_ + (ai - 200) : ai - 200;

        // circle(prop_.get_center(), prop_.get_irad_dist(), guide_c);
        //circle(center_, mid_radius_, guide_c);
        
        // Point<float> t {center_.x + mid_radius_ * cosine_craft_[ai], center_.y + mid_radius_ * sine_craft_[ai]};
        // Point<float> t2 {center_.x + outer_radius_ * cosine_craft_[ai], center_.y + outer_radius_ * sine_craft_[ai]};

        // quad_bezier(origin_, t, t2, 50, guide_c);
        // line(origin_, t, guide_c); 
        // line(t, t2, guide_c); 
        // circle(prop_.get_irad_center(cosine_craft_, sine_craft_, ai), prop_.get_irad(), guide_c);
        // circle(prop_.get_orad_center(cosine_craft_, sine_craft_, ai), prop_.get_orad(), guide_c);

        // Animate the propulsion blasts 
        for (auto &tb : prop_.get_blasts()) {
            RGBAColor pc = 100.0f * tb.get_head_step() / tb.get_size_of_step();
            line(tb.get_head(), tb.get_tail(), prop_pal_[pc]);
        }
        
        auto a_origin_i_new = 1.0f * origin_angle_ / TrigCacheN_ * TrigCacheCraftN_;
        auto angle_point = craft_ -  center_;
        auto a = SDL_atan2f(angle_point.y, angle_point.x) / M_PI;
        auto ai = a >= 0 ? TrigCacheCraftN_ / 2.0f * a : TrigCacheCraftN_ + TrigCacheCraftN_ / 2.0f * a;
        prop_.next(cosine_craft_, sine_craft_, ai, ai, a_origin_i_new);

        // SDL_Log("%.2f %.2f", ai, a_origin_i_new);

        // for (auto &tb : prop_left_.get_blasts()) {
        //     RGBAColor pc = 100.0f * tb.get_head_step() / tb.get_size_of_step();
        //     line(tb.get_head(), tb.get_tail(), prop_pal_[pc]);
        // }
        // prop_left_.next(cosine_craft_, sine_craft_, ai_left);

        // for (auto &tb : prop_right_.get_blasts()) {
        //     RGBAColor pc = 100.0f * tb.get_head_step() / tb.get_size_of_step();
        //     line(tb.get_head(), tb.get_tail(), prop_pal_[pc]);
        // }
        // prop_right_.next(cosine_craft_, sine_craft_, ai_right);


        origin_angle_ += origin_angle_inc_;
        if (origin_angle_ >= TrigCacheN_) origin_angle_ = 0;
        origin_ = center_;
        origin_.x += origin_radius_from_center_ * cosine_[origin_angle_];
        origin_.y += origin_radius_from_center_ * sine_[origin_angle_];

        return true;
    }

    auto WormholeWithPropulsionDemo::capture_events() -> bool {
        SDL_Event e;
        while(SDL_PollEvent(&e)) {
            if(e.type == SDL_QUIT)
                is_running_ = false;

            else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_ESCAPE)
                    is_running_ = false;
                else if (e.key.keysym.sym == SDLK_SPACE) {
                    if (!origin_angle_inc_) origin_angle_inc_ = 1;
                    else origin_angle_inc_ = 0;
                }
            }
            
            else if (e.type == SDL_MOUSEMOTION) {
                // origin_.x = static_cast<float>(e.motion.x);
                // origin_.y = static_cast<float>(e.motion.y);
                craft_.x = static_cast<float>(e.motion.x);
                craft_.y = static_cast<float>(e.motion.y);                
            }
        }
        return true;
    }
}

#endif 
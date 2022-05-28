#ifndef WORMHOLE_WITH_PROPULSION_DEMO_HPP
#define WORMHOLE_WITH_PROPULSION_DEMO_HPP

#include <vector>
#include "Video.hpp"
#include "QuadBezierMotion.hpp"
#include "TrigCache.hpp"
#include "LCMRND.hpp"
#include "PriorityList.hpp"
#include "PropulsionMotion.hpp"


namespace g80 {
    class WormholeWithPropulsionDemo : public Video {
    public:
        WormholeWithPropulsionDemo();

        auto preprocess_states() -> bool;
        auto update_states() -> bool;
        auto capture_events() -> bool;

    private:
        const size_t TrigCacheN_{30000};
        CosCache<float> cosine_{TrigCacheN_};
        SinCache<float> sine_{TrigCacheN_};
        Point<float> origin_;
        float inner_radius_{10}, mid_radius_{100}, outer_radius_{800};
        
        std::vector<QuadBezierMotion<float>> quad_bezier_motion_;
        Palette pal_, prop_pal_;

        PriorityList pl_{110, TrigCacheN_};
        PropulsionMotion prop_{1000};

    };

    WormholeWithPropulsionDemo::WormholeWithPropulsionDemo() : Video() {

    }

    auto WormholeWithPropulsionDemo::preprocess_states() -> bool {
        
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

        prop_pal_.add_gradients(surface_->format,
            {
                {0, SDL_MapRGBA(surface_->format, 255, 255, 255, 255)},
                {50, SDL_MapRGBA(surface_->format, 255, 255, 0, 255)},
                {75, SDL_MapRGBA(surface_->format, 255, 0, 0, 255)},
                {100, SDL_MapRGBA(surface_->format, 150, 50, 150, 255)},
                });

        prop_.set_propulsion_motion({surface_->w / 2, surface_->h / 2}, 10, 60, mid_radius_ * 3, mid_radius_ * 3 + 200, cosine_, sine_, 0);        
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

        RGBAColor orbit_c = SDL_MapRGBA(surface_->format, 255, 0, 255, 255);
        RGBAColor inner_c = SDL_MapRGBA(surface_->format, 255, 0, 0, 255);
        RGBAColor outer_c = SDL_MapRGBA(surface_->format, 255, 255, 0, 255);

        auto angle_point = origin_ -  Point<float>(surface_->w / 2, surface_->h / 2);
        float a = SDL_atan2f(angle_point.y, angle_point.x) / M_PI;
        Sint32 ai = a >= 0 ? TrigCacheN_ / 2.0f * a : TrigCacheN_ + TrigCacheN_ / 2.0f * a;
        // circle(prop_.get_center(), prop_.get_irad_dist(), orbit_c);
        // circle(prop_.get_irad_center(cosine_, sine_, ai), prop_.get_irad(), inner_c);
        // circle(prop_.get_orad_center(cosine_, sine_, ai), prop_.get_orad(), outer_c);


        for (auto &b : prop_.get_blasts()) {
            RGBAColor pc = 100.0f * b.get_head_step() / b.get_size_of_step();
            line(b.get_head(), b.get_tail(), prop_pal_[pc]);
        }
        prop_.next(cosine_, sine_, ai);

        // Point<float> craft {surface_->w / 2 + mid_radius_ * 3 * cosine_[ai], surface_->h / 2 + mid_radius_ * 3 * sine_[ai]};
        // circle(craft, 20, c);
        
        // for (int prop = ai - 100; prop <= ai + 100; prop += 20) {
        //     auto t = prop > 0 ? prop : TrigCacheN_ + prop;
        //     if (t >= TrigCacheN_) t -= TrigCacheN_;
        //     Point<float> inner {surface_->w / 2 + mid_radius_ * 3 *  cosine_[t], surface_->h / 2 + mid_radius_ * 3 * sine_[t]};
        //     Point<float> outer {surface_->w / 2 + outer_radius_ * cosine_[t], surface_->h / 2 + outer_radius_  * sine_[t]};
        //     line(inner, outer, c2);
        // }
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
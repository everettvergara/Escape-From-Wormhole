/*
 *  Demo.hpp - Handles the demo of the animation proper
 *  Copyright (C) 2022 Everett Gaius S. Vergara
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *  
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *	
 */

#ifndef _DEMO_HPP_
#define _DEMO_HPP_

#include <vector>
#include "Commons.hpp"
#include "Video.h"
#include "Gfx.hpp"
#include "QuadBezierAnim.hpp"
#include "PropulsionGrid.hpp"
#include "Propulsion.hpp"

namespace g80 {

    using QuadBeizerPoints = std::vector<QuadBezierAnim, EmptyAllocator<QuadBezierAnim>>;
    
    class Demo : public Video {

    public: 
        Demo (Dim N, float SZ_WORMHOLE = 1000.0f) : N_(N), SZ_WORMHOLE_(SZ_WORMHOLE), propulsion_grid_(50, 50), propulsion_(500) { }
        ~Demo() {}
        auto create_window(const VideoConfig &video_config) -> bool;
        auto preprocess_states() -> bool;
        auto update_states() -> bool;
        auto capture_events() -> bool;

    private:
        Dim N_;
        float SZ_WORMHOLE_;
        Floats sinf_, cosf_;
        
        Point wormhole_origin_;
        float wormhole_radius_from_center{750.0f};
        Dim wormhole_angle_{0};
        Point center_screen_;
        SinCacheF sin_craft_{360};
        CosCacheF cos_craft_{360};
        Dim air_craft_angle_{180};
        Point player_;

        QuadBeizerPoints quad_bezier_points_;
        PropulsionGrid propulsion_grid_;
        Propulsion propulsion_;
        

        inline auto rnd() -> UDim {
            static std::time_t now = time(&now);
            static UDim seed = now;
            static UDim a = 1103515245;
            static UDim c = 12345;
            static UDim m = 2147483647;
            static UDim rand = seed;
            return rand = (rand * a + c) % m;
        }

        auto get_wormhole_speed(Dim min, Dim max) -> Dim {
            return min + rnd() % (max - min);
        }

        auto get_wormhole_color(Dim speed) -> RGBAColor {
            RGBAColor color;
            if (speed >= 0 && speed < 75)
                color = SDL_MapRGBA(surface_->format, 180, 142, 173, 255);
            else if (speed >= 75 && speed < 100)
                color = SDL_MapRGBA(surface_->format, 136, 192, 208, 255);
            else if (speed >= 100 && speed < 150)
                color = SDL_MapRGBA(surface_->format, 129, 161, 193, 255);
            else 
                color = SDL_MapRGBA(surface_->format, 94, 129, 172, 255);
            return color;
        }

        auto update_wormhole_angle(Dim direction) -> void {
            wormhole_angle_ = wormhole_angle_ + direction;
            if (wormhole_angle_ >= N_) wormhole_angle_ = wormhole_angle_ - N_;
            else if (wormhole_angle_ < 0) wormhole_angle_ = N_ + wormhole_angle_;
            wormhole_origin_ = {
                center_screen_.x + static_cast<Dim>(cosf_[wormhole_angle_] * wormhole_radius_from_center), 
                center_screen_.y + static_cast<Dim>(sinf_[wormhole_angle_] * wormhole_radius_from_center)};
        }

    };

    auto Demo::create_window(const VideoConfig &video_config) -> bool {
        if (!Video::create_window(video_config)) return false;
        return true;
    }

    auto Demo::preprocess_states() -> bool {
        float angle = 0.0f;
        float sz_angle = M_PI * 2 / N_;
        sinf_.reserve(N_);
        cosf_.reserve(N_);        
        for (Dim i = 0; i < N_; ++i) {
            cosf_.emplace_back(SDL_cosf(angle));
            sinf_.emplace_back(SDL_sinf(angle));
            angle += sz_angle;
        }
       
        quad_bezier_points_.reserve(N_);
        center_screen_ = {surface_->w / 2, surface_->h / 2};

        update_wormhole_angle(+1);

        for (Dim i = 0; i < N_; ++i) {

            Point target;
            target.x = center_screen_.x + SZ_WORMHOLE_ * cosf_[i];
            target.y = center_screen_.y + SZ_WORMHOLE_ * sinf_[i];
            Dim speed = get_wormhole_speed(20, 200);
            RGBAColor color = get_wormhole_color(speed);
            quad_bezier_points_.emplace_back(surface_->format, wormhole_origin_, center_screen_, target, color, speed);
        }

        player_ = center_screen_;
        player_.x += cos_craft_[air_craft_angle_] * 300;
        player_.y += sin_craft_[air_craft_angle_] * 300;

        return true;
    }

    auto Demo::update_states() -> bool {
        SDL_LockSurface(surface_);
        
        // Erase all
        for (auto &qbp : quad_bezier_points_)
            set_pixel_strict_bounds(qbp.get_tail_point(), 0);
        // SDL_FillRect(surface_, NULL, 0);
            
        // Update and Plot
        update_wormhole_angle(10);
        for (auto &qbp : quad_bezier_points_) {
            if (!qbp.is_valid_current_point()) {

                // Erase remaining tail
                while (qbp.is_valid_tail_point())
                    set_pixel_strict_bounds(qbp.get_tail_point(), 0);

                Dim speed = get_wormhole_speed(20, 200);
                RGBAColor color = get_wormhole_color(speed);
                qbp.reset(surface_->format, wormhole_origin_, center_screen_, qbp.get_p3(), color, speed);
            }
            set_pixel_strict_bounds(qbp.next(), qbp.get_color(surface_->format));
        }

        // Draw Propulsion Grid
        
        float width_size = 1.0f * surface_->w / propulsion_grid_.get_width();
        float height_size = 1.0f * surface_->h / propulsion_grid_.get_height();
        Uint32 grid_color = SDL_MapRGBA(surface_->format, 40, 40, 40, 255);
        Uint32 vector_color = SDL_MapRGBA(surface_->format, 0, 0, 255, 255);
        Uint32 propulsion_color = SDL_MapRGBA(surface_->format, 255, 0, 0, 255);
        

        for (float y = 0; y <= surface_->h; y += height_size)
            Gfx::line(surface_, {0, static_cast<Dim>(y)}, {surface_->w - 1, static_cast<Dim>(y)}, grid_color);

        for (float x = 0; x <= surface_->w; x += width_size)
            Gfx::line(surface_, {static_cast<Dim>(x), 0}, {static_cast<Dim>(x), surface_->h - 1}, grid_color);

        
        // 
        // Draw a line from p1 to p2
        Point p1{propulsion_grid_.get_width()/2, propulsion_grid_.get_height()/2};
        Point p2{static_cast<Dim>(wormhole_origin_.x / width_size), static_cast<Dim>(wormhole_origin_.y / height_size)};
        Sint32 dx = p2.x - p1.x;
        Sint32 dy = p2.y - p1.y;
        Sint32 sdx = dx < 0 ? -1 : 1;
        Sint32 sdy = dy < 0 ? -1 : 1;
        Sint32 adx = dx < 0 ? dx * -1 : dx;
        Sint32 ady = dy < 0 ? dy * -1 : dy;
        
        if (adx >= ady) {    
                for (Sint32 i = 0, t = ady; i <= adx; ++i, t += ady) {
                    // if (cp >= min_point && cp < max_point) *cp = c;
                    if (p1.x >= 0 && p1.x < propulsion_grid_.get_width() && 
                        p1.y >= 0 && p1.y < propulsion_grid_.get_height()) {
                            propulsion_grid_.set_magnitude(propulsion_grid_.ix(p1.x, p1.y), 50.0f);
                    }
                    if (t >= adx) {
                        p1.y += sdy;
                        t -= adx;
                    }
                    p1.x +=sdx;
                }
            } else {
                for (Sint32 i = 0, t = adx; i <= ady; ++i, t += adx) {
                    if (p1.x >= 0 && p1.x < propulsion_grid_.get_width() && 
                        p1.y >= 0 && p1.y < propulsion_grid_.get_height()) {
                            propulsion_grid_.set_magnitude(propulsion_grid_.ix(p1.x, p1.y), 50.0f);
                    }
                    if (t >= ady) {
                        p1.x += sdx;
                        t -= ady;
                    }
                    p1.y += sdy;
                }
            }
        
        // for (int y = 0; y <= propulsion_grid_.get_height(); ++y) {
        //     for (int x = 0; x < propulsion_grid_.get_width(); ++x) {
        //         // Point center {
        //         //     static_cast<Dim>(x * width_size + width_size / 2), 
        //         //     static_cast<Dim>(y * height_size + height_size / 2)};

        //         // Dim ix = propulsion_grid_.ix(x, y);
        //         // Point dest {
        //         //     static_cast<Dim>(center.x + propulsion_grid_.get_vector_x(ix)),
        //         //     static_cast<Dim>(center.y + propulsion_grid_.get_vector_y(ix))};
        //         // Gfx::line(surface_, center, dest, vector_color);
        //         // propulsion_grid_.reduce_magnitude(ix, 0.9925f);
        //     }
        // }
        



        // Draw Target
        Gfx::circle(surface_, center_screen_, 300, SDL_MapRGBA(surface_->format, 100, 100, 100, 255));

        Gfx::circle(surface_, player_, 20, 0);
        player_ = center_screen_;
        player_.x += cos_craft_[air_craft_angle_] * 300;
        player_.y += sin_craft_[air_craft_angle_] * 300;
        Gfx::circle(surface_, player_, 20, vector_color);


        // Create new Propulsion
        for (Dim i = propulsion_.get_free_() ; i < propulsion_.get_size_() - 1 ; ++i) {
            
            Dim angle = air_craft_angle_ - 15 + rnd() % 30;
            Dim radius = 20 + rnd() % 20;
            Point start_burst;
            start_burst.x = player_.x + radius * cos_craft_[angle];
            start_burst.y = player_.y + radius * sin_craft_[angle];

            Dim ix = propulsion_grid_.ix(start_burst.x / width_size, start_burst.y / height_size);
            angle = propulsion_grid_.get_angle(ix);
            float magnitude = propulsion_grid_.get_magnitude(ix);

            // SDL_Log("%d, %.2f\n", angle, magnitude);
            Point end_burst = start_burst;
            end_burst.x += magnitude * cos_craft_[angle] ;
            end_burst.y += magnitude * sin_craft_[angle] ;
            propulsion_.add_burst(start_burst, end_burst);

        }

        // Erase Propulsion
        for (Dim i = 0; i < propulsion_.get_free_(); ++i) {
            const LinePoint &lp = propulsion_[i];
            Gfx::pset(surface_, lp.p1, 0);
        }

        propulsion_.next();
        
        // Draw Propulsion
        for (Dim i = 0; i < propulsion_.get_free_(); ++i) {
            const LinePoint &lp = propulsion_[i];
            Gfx::pset(surface_, lp.p1, propulsion_color);
        }


        // SDL_Log("%d, %0.4f, %0.4f",air_craft_angle_,  cos_craft_[air_craft_angle_], sin_craft_[air_craft_angle_]);
        // Gfx::line(surface_, center_screen_, wormhole_origin_, SDL_MapRGBA(surface_->format, 100, 100, 100, 255));

        SDL_UnlockSurface(surface_);
        return true;
    }

    auto Demo::capture_events() -> bool {
        SDL_Event e;
        while(SDL_PollEvent(&e)) {
            if(e.type == SDL_QUIT)
                is_running_ = false;

            else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_ESCAPE)
                    is_running_ = false;
            }

            else if (e.type == SDL_MOUSEMOTION) {
                e.motion.xrel /= 2;
                if (e.motion.xrel < 0) { 
                    Dim xrel = e.motion.xrel < -90 ? 90 : -e.motion.xrel;
                    air_craft_angle_ += xrel;
                    if (air_craft_angle_ >= 360) air_craft_angle_ -= 360;
                } else if (e.motion.xrel > 0) {
                    Dim xrel = e.motion.xrel > 90 ? 90 : e.motion.xrel;
                    air_craft_angle_ -= xrel;
                    if (air_craft_angle_ < 0) air_craft_angle_ = air_craft_angle_ + 360;
                }
                

                // update_wormhole_angle((e.motion.xrel * e.motion.yrel));
            }
        }
        return true;
    }
}

#endif 
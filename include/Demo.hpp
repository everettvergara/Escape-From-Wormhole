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
#include "Video.h"
#include "Gfx.hpp"
#include "Bezier.hpp"
#include "EmptyAllocator.hpp"

namespace g80 {

    using QuadBeizerPoints = std::vector<QuadBezierAnim, EmptyAllocator<QuadBezierAnim>>;
    using Floats = std::vector<float, EmptyAllocator<float>>; 
    class Demo : public Video {

    public: 
        Demo (Dim N, float SZ_WORMHOLE = 350.0f) : N_(N), SZ_WORMHOLE_(SZ_WORMHOLE) { }
        ~Demo() {}
        auto create_window(const VideoConfig &video_config) -> bool;
        auto preprocess_states() -> bool;
        auto update_states() -> bool;
        auto capture_events() -> bool;

    private:
        Dim N_;
        float SZ_WORMHOLE_;
        Point mouse_pointer, center_screen;
        Floats sinf_, cosf_;
        
        QuadBeizerPoints quad_bezier_points_;

        inline auto rnd() -> Sint32 {
            static std::time_t now = time(&now);
            static Sint32 seed = now;
            static Sint32 a = 1103515245;
            static Sint32 c = 12345;
            static Sint32 m = 2147483647;
            static Sint32 rand = (seed * a + c) % m;
            return rand = (rand * a + c) % m; 
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
        mouse_pointer = {10, 10};
        quad_bezier_points_.reserve(N_);
        center_screen = {surface_->w / 2, surface_->h / 2};
        for (Dim i = 0; i < N_; ++i) {
            Point target;
            target.x = center_screen.x + SZ_WORMHOLE_ * cosf_[i];
            target.y = center_screen.y + SZ_WORMHOLE_ * sinf_[i];
            quad_bezier_points_.emplace_back(mouse_pointer, center_screen, target, SDL_MapRGBA(surface_->format, 255, 255, 255, 255), 10 + rand() % 100);
        }
        return true;
    }

    auto Demo::update_states() -> bool {
        SDL_LockSurface(surface_);
        
        // Erase all
        for (auto &qbp : quad_bezier_points_)
            set_pixel(qbp.get_current_point(), 0);
    
            
        // Update and Plot
        for (auto &qbp : quad_bezier_points_) {
            if (!qbp.is_valid())
                qbp.reset(mouse_pointer, center_screen, qbp.get_p3(), qbp.get_color(), 10 + rand() % 100);
            
            set_pixel(qbp.next(), qbp.get_color());
        }

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
                mouse_pointer = {e.motion.x, e.motion.y};  
            }
        }
        return true;
    }
}

#endif 
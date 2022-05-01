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
        Demo (Dim N, float SZ_WORMHOLE = 1000.0f) : N_(N), SZ_WORMHOLE_(SZ_WORMHOLE) { }
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
            Dim speed = get_wormhole_speed(20, 200);
            RGBAColor color = get_wormhole_color(speed);
            quad_bezier_points_.emplace_back(mouse_pointer, center_screen, target, color, speed);
        }
        return true;
    }

    auto Demo::update_states() -> bool {
        SDL_LockSurface(surface_);
        



        // Erase all
        for (auto &qbp : quad_bezier_points_)
            set_pixel_strict_bounds(qbp.get_tail_point(), 0);
    
            
        // Update and Plot
        for (auto &qbp : quad_bezier_points_) {
            if (!qbp.is_valid_current_point()) {

                // Erase remaining tail
                while (qbp.is_valid_tail_point())
                    set_pixel_strict_bounds(qbp.get_tail_point(), 0);

                Dim speed = get_wormhole_speed(20, 200);
                RGBAColor color = get_wormhole_color(speed);
                qbp.reset(mouse_pointer, center_screen, qbp.get_p3(), color, speed);
            }
            set_pixel_strict_bounds(qbp.next(), qbp.get_color(surface_->format));
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
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

#include "Video.h"
#include "Gfx.hpp"
#include "Bezier.hpp"

namespace g80 {

    class Demo : public Video {

    public: 
        // Demo () {

        // }   
        ~Demo() {
        }
        auto create_window(const VideoConfig &video_config) -> bool;
        auto preprocess_states() -> bool;
        auto update_states() -> bool;
        auto capture_events() -> bool;

    private:
        Sint32 mouse_x, mouse_y;
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

        return true;
    }

    auto Demo::update_states() -> bool {
        SDL_LockSurface(surface_);
        SDL_FillRect(surface_, NULL, 0);
        Sint32 cx = surface_->w / 2;
        Sint32 cy = surface_->h / 2;
        Point p1{mouse_x, mouse_y};
        Point p2{cx + static_cast<Sint32>(SDL_cosf(90 * M_PI / 180) * 0), cy + static_cast<Sint32>(SDL_sinf(90 * M_PI / 180) * 0)};
        Point p3{cx + static_cast<Sint32>(SDL_cosf(90 * M_PI / 180) * 350), cy + static_cast<Sint32>(SDL_sinf(90 * M_PI / 180) * 350)};
    

        QuadBezierAnim quad_bezier_anim{p1, p2, p3, 20};

        for (int i = 0; i <= 20; ++i) {
            Point p = quad_bezier_anim.next();
            Gfx::pset(surface_, p, SDL_MapRGBA(surface_->format, 255, 0, 0, 255));
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
                mouse_x = e.motion.x;
                mouse_y = e.motion.y;                
            }
        }
        return true;
    }
}

#endif 
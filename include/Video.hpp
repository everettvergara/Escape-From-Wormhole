/*
 *  Video.hpp - My simple SDL Graphics library 
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

#ifndef _VIDEO_HPP_
#define _VIDEO_HPP_

#include <SDL.h>
#include "VideoConfig.hpp"
#include "PixelPoint.hpp"
#include "Color.hpp"

namespace g80 {

    // Video Class
    class Video {
    public:
        Video();
        virtual ~Video();

        // Getters
        inline auto is_init() const -> bool;
        inline auto is_running() const -> bool;
        inline auto get_window() const -> SDL_Window *;
        inline auto get_surface() const -> SDL_Surface *;
        inline auto get_video_width() const -> Sint32;
        inline auto get_video_height() const -> Sint32;
        inline auto get_pixel_buffer(const PixelPoint &p) const -> Uint32 *;

        // User Def Functions
        virtual auto create_window(const VideoConfig &video_config) -> bool;
        virtual auto destroy_window() -> void;
        virtual auto preprocess_states() -> bool;
        virtual auto run() -> bool;
        virtual auto capture_events() -> bool;
        virtual auto update_states() -> bool;
        virtual auto update_window_surface() -> bool;

        // Graphics
        inline auto is_pixel_within_bounds(const PixelPoint &p) const -> bool;
        auto pset(const PixelPoint &p, RGBAColor c) -> void;
        auto pset_lite(const PixelPoint &p, RGBAColor c) -> void;
        auto line(PixelPoint p1, const PixelPoint &p2, RGBAColor c) -> void;
        auto line_lite(PixelPoint p1, const PixelPoint &p2, RGBAColor c) -> void;
       
    protected:
        bool is_init_;
        bool is_running_ {false};
        SDL_Window *window_ {nullptr};
        SDL_Surface *surface_ {nullptr};
        Uint32 *pixel_start_, *pixel_end_;
        Uint16 MSPF_;        
    };


    Video::Video() : is_init_(SDL_VideoInit(NULL) == 0 ? true : false) {
    }

    Video::~Video() {
        destroy_window();
        SDL_VideoQuit();
    }

    auto Video::is_init() const -> bool {
        return is_init_;
    }
    
    auto Video::is_running() const -> bool {
        return is_running_;
    }
    
    auto Video::get_window() const -> SDL_Window * {
        return window_;
    }
    
    auto Video::get_surface() const -> SDL_Surface * {
        return surface_;
    }

    auto Video::get_video_width() const -> Sint32 {
        return surface_->w;
    }
    
    auto Video::get_video_height() const -> Sint32 {
        return surface_->h;
    }

    auto Video::get_pixel_buffer(const PixelPoint &p) const -> Uint32 * {
        return pixel_start_ + surface_->w * p.y + p.x;
    }

    auto Video::create_window(const VideoConfig &video_config) -> bool {
        if (!is_init_ || video_config.FPS == 0 || window_) return false;
        
        if ((window_ = SDL_CreateWindow(
            video_config.title.c_str(), video_config.rect.x, video_config.rect.y, 
            video_config.rect.w, video_config.rect.h, video_config.flags)) == NULL) return false;

        if ((surface_ = SDL_GetWindowSurface(window_)) == NULL) return false;

        MSPF_ = 1000 / video_config.FPS;
        pixel_start_ = static_cast<Uint32 *>(surface_->pixels);
        pixel_end_ = static_cast<Uint32 *>(surface_->pixels) + surface_->w * surface_->h;
        
        return true;
    }

    auto Video::destroy_window() -> void {
        if (window_) SDL_DestroyWindow(window_);
        window_ = {NULL};
        is_init_ = {false};
    }

    auto Video::preprocess_states() -> bool {
        return true;
    }

    auto Video::run() -> bool {
        is_running_ = true;
        while (is_running_) {

            Uint32 start = SDL_GetTicks(); 
            
            if (!capture_events() || !update_states() || !update_window_surface()) return is_running_ = false; 
            
            Uint32 end = SDL_GetTicks();
            Uint32 elapsed = end - start;
            if (elapsed < MSPF_) SDL_Delay(MSPF_ - elapsed);
        }
        return true;
    }

    auto Video::capture_events() -> bool {
        SDL_Event e;
        while(SDL_PollEvent(&e)) {
            if(e.type == SDL_QUIT)
                is_running_ = false;

            else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_ESCAPE)
                    is_running_ = false;
            }
        }
        return true;
    }    

    auto Video::update_states() -> bool {
        return true;
    }

    auto Video::update_window_surface() -> bool {
        return SDL_UpdateWindowSurface(window_) == 0;
    }

    auto Video::is_pixel_within_bounds(const PixelPoint &p) const -> bool {
        if (p.x < 0 || p.y < 0 || p.x >= surface_->w || p.y >= surface_->h) return false;
        return true;
    }

    auto Video::pset(const PixelPoint &p, RGBAColor c) -> void {
        if (!is_pixel_within_bounds(p)) return;
        *get_pixel_buffer(p) = c;
    }

    auto Video::pset_lite(const PixelPoint &p, RGBAColor c) -> void {
        *get_pixel_buffer(p) = c;
    }

    auto Video::line(PixelPoint p1, const PixelPoint &p2, RGBAColor c) -> void {
        
        // Out of bounds recomputation
        Sint32 h = p2.y - p1.y;
        Sint32 w = p2.x - p1.x;

        /*
            if p1.y < 0 && p1.x >= 0
            if (p2.y < 0) then no line

            if (p2.y >= 0)
            p1.
            |\
            | \
            |  \
            ----x  0
            |    \
            |     \ p2

            p2.x > p1.x, p2.y > p1.y
            p2.x < p1.x, p2.y > p1.y
            p2.x = p1.x, p2.y > p1.y
            
            --
            w = p2.x - p1.x
            h = p2.y - p1.y
            
            solve for m:
            y = mx + b
            m = 1.0f * h / w;

            solve for b:
            mw + b = h
            b = 1.0f * h - mw;

            what is x if y = 0;
            mw = h - b
            w = -b / m


        */ 


        if (p1.y < 0 && w != 0) {
            float m = 1.0f * h / w;
            float b = 1.0f * p1.y - m * p1.x;
            Sint32 x = -b / m;

            // x is not within the bounds
            if (x < 0 || x >= surface_->w) return; // check for y intercept
            p1.x = x;
            p1.y = 0;
        } else if (p1.y < 0 && w == 0) {
            if (p1.x < 0 || p1.x >= surface_->w) return; 
            p1.y = 0;
        }
        
        PixelPoint d = p2 - p1;
        PixelPoint ad = d.abs();
        Sint32 sdx = d.x < 0 ? -1 : 1;
        Sint32 sdy = d.y < 0 ? -surface_->w : surface_->w;

        Uint32 *pixel_buffer = static_cast<Uint32 *>(surface_->pixels) + p1.y * surface_->w + p1.x;
        auto draw_line = [&](Sint32 abs_g, Sint32 abs_l, Sint32 sig_g, Sint32 sig_l) -> void {
            for (Sint32 i = 0, t = abs_l; i <= abs_g; ++i, t += abs_l) {
                *pixel_buffer = c;
                if (t >= abs_g) {
                    pixel_buffer += sig_l;
                    t -= abs_g;
                }
                pixel_buffer += sig_g;
            }
        };
        if (ad.x >= ad.y) draw_line(ad.x, ad.y, sdx, sdy);
        else draw_line(ad.y, ad.x, sdy, sdx);
    }

    auto Video::line_lite(PixelPoint p1, const PixelPoint &p2, RGBAColor c) -> void {
        PixelPoint d = p2 - p1;
        PixelPoint ad = d.abs();
        Sint32 sdx = d.x < 0 ? -1 : 1;
        Sint32 sdy = d.y < 0 ? -surface_->w : surface_->w;

        Uint32 *pixel_buffer = static_cast<Uint32 *>(surface_->pixels) + p1.y * surface_->w + p1.x;
        auto draw_line = [&](Sint32 abs_g, Sint32 abs_l, Sint32 sig_g, Sint32 sig_l) -> void {
            for (Sint32 i = 0, t = abs_l; i <= abs_g; ++i, t += abs_l) {
                *pixel_buffer = c;
                if (t >= abs_g) {
                    pixel_buffer += sig_l;
                    t -= abs_g;
                }
                pixel_buffer += sig_g;
            }
        };
        if (ad.x >= ad.y) draw_line(ad.x, ad.y, sdx, sdy);
        else draw_line(ad.y, ad.x, sdy, sdx);
    }

}
#endif 
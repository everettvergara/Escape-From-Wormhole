/*
 *  Video.h - My simple Graphics library 
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

#ifndef _VIDEO_H_
#define _VIDEO_H_

#include "SDL.h"
#include "Commons.hpp"
#include "VideoConfig.h"

namespace g80 {

    using PixelBuffer = Uint32 *;
    class Video {
    
    public:
        struct Iterator {
            Iterator(Uint32 *begin) : pixel_ptr(begin) {}
            auto operator*() const -> Uint32 & {return *pixel_ptr;}
            auto operator->() const -> Uint32 * {return pixel_ptr;}
            auto operator++() -> Iterator & {++pixel_ptr; return *this;}
            auto operator++(int) -> Iterator {Iterator t = *this; ++pixel_ptr; return t;}
            inline friend auto operator==(const Iterator &lhs, const Iterator &rhs) -> bool {return lhs.pixel_ptr == rhs.pixel_ptr;}
            inline friend auto operator!=(const Iterator &lhs, const Iterator &rhs) -> bool {return lhs.pixel_ptr != rhs.pixel_ptr;}
        
        private:
            Uint32 *pixel_ptr;
        };

        inline auto begin() const -> Iterator {return Iterator(static_cast<Uint32 *>(surface_->pixels));} 
        inline auto end() const -> Iterator {return Iterator(static_cast<Uint32 *>((surface_->pixels)) + surface_->h * surface_->w);} 

    public:
        Video();
        Video(const Video &) = delete;
        Video(Video &&) = delete;
        auto operator=(const Video &) -> Video & = delete;
        auto operator=(Video &&) -> Video & = delete;
        virtual ~Video();

        virtual auto create_window(const VideoConfig &video_config) -> bool;
        auto destroy_window() -> void;
        auto get_window() -> const SDL_Window *;
        auto is_init() -> bool;
        auto is_running() -> bool;

        // Helper
        inline auto get_width() -> int {
            return surface_->w;
        }

        inline auto get_height() -> int {
            return surface_->h;
        }

        inline auto get_pixel_buffer(const Point &p) -> PixelBuffer {
            return static_cast<PixelBuffer>(surface_->pixels) + surface_->w * p.y + p.x;
        }

        inline auto set_pixel(const Point &p, RGBAColor color) -> void {
            PixelBuffer pixel_buffer = get_pixel_buffer(p);
            if (pixel_buffer >= static_cast<PixelBuffer>(surface_->pixels) && pixel_buffer < pixel_end_)
                *pixel_buffer = color;
        }

        // User Def Functions
        virtual auto preprocess_states() -> bool;
        virtual auto update_states() -> bool;
        virtual auto capture_events() -> bool;
        virtual auto run() -> bool;

    protected:
        bool is_init_;
        bool is_running_ {false};
        SDL_Window *window_ {nullptr};
        SDL_Surface *surface_ {nullptr};
        Uint32 *pixel_end_;
        Uint16 MSPF_;

        auto update_window_surface() -> bool;
        
    };
}
#endif 
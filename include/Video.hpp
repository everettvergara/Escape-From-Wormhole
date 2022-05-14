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

#include <cassert>
#include <type_traits>

#include <SDL.h>

#include "VideoConfig.hpp"
#include "Point.hpp"
#include "Color.hpp"
#include "Palette.hpp"

namespace g80 {

    template<typename T>
    inline auto lerp(const T a, const T b, const T t) -> T {
        static_assert(
            std::is_same<T, float>::value || 
            std::is_same<T, double>::value || 
            std::is_same<T, long double>::value,
            "Must be of floating-point type");
        return a + t * (b - a);
    }

    template<typename T>
    inline auto lerp_point(const Point<T> &a, const Point<T> &b, T t, T tmax) -> Point<T> {
        return a + (b - a) * t / tmax;
    }

    template<typename T>
    inline auto lerp_point_b_less_a(const Point<T> &a, const Point<T> &b_less_a, T t, T tmax) -> Point<T> {
        return a + b_less_a * t / tmax;
    }

    class Video {
    public:
        Video();
        Video(const Video &) = delete;
        Video(Video &&) = delete;
        auto operator=(const Video &) -> Video & = delete;
        auto operator=(Video &&) -> Video & = delete;
        virtual ~Video();

        // Getters
        inline auto is_init() const -> bool;
        inline auto is_running() const -> bool;
        inline auto get_window() const -> SDL_Window *;
        inline auto get_surface() const -> SDL_Surface *;
        inline auto get_video_width() const -> Sint32;
        inline auto get_video_height() const -> Sint32;
        inline auto get_pixel_buffer(const Point<Sint32> &p) const -> Uint32 *;

        // User Def Functions
        virtual auto create_window(const VideoConfig &video_config) -> bool;
        virtual auto destroy_window() -> void;
        virtual auto preprocess_states() -> bool;
        virtual auto run() -> bool;
        virtual auto capture_events() -> bool;
        virtual auto update_states() -> bool;
        virtual auto update_window_surface() -> bool;

        // Drawing functions

        inline auto is_point_within_bounds(const Point<Sint32> &p) const -> bool;
        
        auto pset(const Point<Sint32> &p, const RGBAColor c) -> void;
        inline auto pset_lite(const Point<Sint32> &p, const RGBAColor c) -> void;
        
        // TODO: Non-lite should use lites
        auto line(Point<Sint32> p1, Point<Sint32> p2, const RGBAColor c) -> void;
        auto line(Point<Sint32> p1, Point<Sint32> p2, const Palette &palette, Uint32 pal_ix_from, Uint32 pal_ix_to) -> void;   
        auto line_lite(const Point<Sint32> &p1, const Point<Sint32> &p2, const RGBAColor c) -> void;
        auto line_lite(const Point<Sint32> &p1, const Point<Sint32> &p2, const Palette &palette, const Uint32 pal_ix_from, const Uint32 pal_ix_to) -> void;
       
        auto quad_bezier(const Point<Sint32> &p1, const Point<Sint32> &p2, const Point<Sint32> &p3, const Sint32 max_steps, const RGBAColor c) -> void;        
        auto quad_bezier(const Point<Sint32> &p1, const Point<Sint32> &p2, const Point<Sint32> &p3, const Sint32 max_steps, const Palette &palette, const Uint32 pal_ix_from, const Uint32 pal_ix_to) -> void;
        auto quad_bezier_lite(const Point<Sint32> &p1, const Point<Sint32> &p2, const Point<Sint32> &p3, const Sint32 max_steps, const RGBAColor c) -> void;
        auto quad_bezier_lite(const Point<Sint32> &p1, const Point<Sint32> &p2, const Point<Sint32> &p3, const Sint32 max_steps, const Palette &palette, const Uint32 pal_ix_from, const Uint32 pal_ix_to) -> void;
        
        auto cubic_bezier_lite(const Point<Sint32> &p1, const Point<Sint32> &p2, const Point<Sint32> &p3, const Point<Sint32> &p4, const Sint32 max_steps, const RGBAColor c) -> void;
        auto cubic_bezier(const Point<Sint32> &p1, const Point<Sint32> &p2, const Point<Sint32> &p3, const Point<Sint32> &p4, const Sint32 max_steps, const RGBAColor c) -> void;
        auto cubic_bezier_lite(const Point<Sint32> &p1, const Point<Sint32> &p2, const Point<Sint32> &p3, const Point<Sint32> &p4, const Sint32 max_steps, const Palette &palette, const Uint32 pal_ix_from, const Uint32 pal_ix_to) -> void;
        auto cubic_bezier(const Point<Sint32> &p1, const Point<Sint32> &p2, const Point<Sint32> &p3, const Point<Sint32> &p4, const Sint32 max_steps, const Palette &palette, const Uint32 pal_ix_from, const Uint32 pal_ix_to) -> void;

        auto bezier_lite(const std::initializer_list<Point<Sint32>> &points, const Sint32 max_steps, const RGBAColor c) -> void;
        auto bezier_lite(const std::initializer_list<Point<Sint32>> &points, const Sint32 max_steps, const Palette &palette, const Uint32 pal_ix_from, const Uint32 pal_ix_to) -> void;
        auto bezier(const std::initializer_list<Point<Sint32>> &points, const Sint32 max_steps, const RGBAColor c) -> void;
        auto bezier(const std::initializer_list<Point<Sint32>> &points, const Sint32 max_steps, const Palette &palette, const Uint32 pal_ix_from, const Uint32 pal_ix_to) -> void;
        
        auto catmullrom_spline_lite(const std::initializer_list<Point<Sint32>> &points, const Sint32 max_steps, const RGBAColor c) -> void;
        auto catmullrom_spline_lite(const std::initializer_list<Point<Sint32>> &points, const Sint32 max_steps, const Palette &palette, const Uint32 pal_ix_from, const Uint32 pal_ix_to) -> void;
        auto catmullrom_spline(const std::initializer_list<Point<Sint32>> &points, const Sint32 max_steps, const RGBAColor c) -> void;

    protected:
        bool is_init_;
        bool is_running_ {false};
        SDL_Window *window_ {nullptr};
        SDL_Surface *surface_ {nullptr};
        Uint32 *pixel_start_, *pixel_end_;
        Uint16 MSPF_;

        auto line_recalc_points(Point<Sint32> &p1, Point<Sint32> &p2) -> void;
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

    auto Video::get_pixel_buffer(const Point<Sint32> &p) const -> Uint32 * {
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

    auto Video::is_point_within_bounds(const Point<Sint32> &p) const -> bool {
        if (p.x < 0 || p.y < 0 || p.x >= surface_->w || p.y >= surface_->h) return false;
        return true;
    }

    auto Video::pset(const Point<Sint32> &p, const RGBAColor c) -> void {
        if (!is_point_within_bounds(p)) return;
        pset_lite(p, c);
    }

    auto Video::pset_lite(const Point<Sint32> &p, const RGBAColor c) -> void {
        *get_pixel_buffer(p) = c;
    }

    auto Video::line_recalc_points(Point<Sint32> &p1, Point<Sint32> &p2) -> void {
        auto bbox_plane = [&](const Point<Sint32> &pixel_point) -> Sint8 {
            if (pixel_point.x < 0 && pixel_point.y < 0) return 0;
            else if (pixel_point.x < 0 && pixel_point.y >= 0 && pixel_point.y < surface_->h) return 3;
            else if (pixel_point.x < 0 && pixel_point.y >= surface_->h) return 6;
            else if (pixel_point.x >=0 && pixel_point.x < surface_->w && pixel_point.y < 0) return 1;
            else if (pixel_point.x >=0 && pixel_point.x < surface_->w && pixel_point.y >= 0 && pixel_point.y < surface_->h) return 4;
            else if (pixel_point.x >=0 && pixel_point.x < surface_->w && pixel_point.y >= surface_->h) return 7;
            else if (pixel_point.x >= surface_->w && pixel_point.y < 0) return 2;
            else if (pixel_point.x >= surface_->w &&pixel_point.y >= 0 && pixel_point.y < surface_->h) return 5;
            else return 8;
        };

        Sint32 h = p2.y - p1.y;
        Sint32 w = p2.x - p1.x;
        float m = 1.0f * h / w;
            
        auto get_point_on_x_intercept = [&](Point<Sint32> p, Sint32 y_value) -> Point<Sint32> {
            if (w == 0) return {p.x, y_value};
            float b = 1.0f * p.y - m * p.x;
            p.x = (y_value - b) / m;
            p.y = y_value;
            return p;
        };

        auto get_point_on_y_intercept = [&](Point<Sint32> p, Sint32 x_value) -> Point<Sint32> {
            if (h == 0) return {x_value, p.y};
            float b = 1.0f * p.y - m * p.x;
            p.y = m * x_value + b;
            p.x = x_value;
            return p;
        };

        auto get_new_point_from_intercept = [&](const Point<Sint32> &p) -> Point<Sint32> {
            Point<Sint32> top_p = get_point_on_x_intercept(p, 0);
            Point<Sint32> bottom_p = get_point_on_x_intercept(p, surface_->h - 1);
            Point<Sint32> left_p = get_point_on_y_intercept(p, 0);
            Point<Sint32> right_p = get_point_on_y_intercept(p, surface_->w - 1);
            Uint8 bbox = bbox_plane(p);

            if (bbox == 0) {
                if (is_point_within_bounds(top_p)) return top_p;
                else if (is_point_within_bounds(left_p)) return left_p;
            } else if (bbox == 2) {
                if (is_point_within_bounds(top_p)) return top_p;
                else if (is_point_within_bounds(right_p)) return right_p;                
            } else if (bbox == 6) {
                if (is_point_within_bounds(bottom_p)) return bottom_p;
                else if (is_point_within_bounds(left_p)) return left_p;                
            } else if (bbox == 8) {
                if (is_point_within_bounds(bottom_p)) return bottom_p;
                else if (is_point_within_bounds(right_p)) return right_p;   
            } else if (bbox == 1 && is_point_within_bounds(top_p)) {
                return top_p;
            } else if (bbox == 3 && is_point_within_bounds(left_p)) {
                return left_p;
            } else if (bbox == 7 && is_point_within_bounds(bottom_p)) {
                return bottom_p;
            } else if (is_point_within_bounds(right_p)) {
                return right_p;
            } 
            return p;
        };

        if (bbox_plane(p1) != 4) {
            p1 = get_new_point_from_intercept(p1);
            if (bbox_plane(p1) != 4) return;
        }
        
        if (bbox_plane(p2) != 4) 
            p2 = get_new_point_from_intercept(p2);
    }

    auto Video::line(Point<Sint32> p1, Point<Sint32> p2, const RGBAColor c) -> void {
        line_recalc_points(p1, p2);
        if (!is_point_within_bounds(p1) || !is_point_within_bounds(p2)) return;
        line_lite(p1, p2, c);
    }

    auto Video::line(Point<Sint32> p1, Point<Sint32> p2, const Palette &palette, Uint32 pal_ix_from, Uint32 pal_ix_to) -> void {
        line_recalc_points(p1, p2);
        if (!is_point_within_bounds(p1) || !is_point_within_bounds(p2)) return;

        Point<Sint32> op1 = p1;
        Point<Sint32> op2 = p2;
        Uint32 opal_ix_from = pal_ix_from;

        auto lerp_pal = [&](const Point<Sint32> &p, Uint32 &pal) {
            Point ad_op = (op1 - op2).abs();
            Point ad = (op1 - p).abs();
            if (ad_op.x >= ad_op.y && ad_op.x > 0) pal = opal_ix_from + (1.0f * ad.x / ad_op.x) * (pal_ix_to - pal_ix_from);
            else if (ad_op.y > 0) pal = opal_ix_from + (1.0f * ad.y / ad_op.y) * (pal_ix_to - pal_ix_from);
            else pal = opal_ix_from;
        };
        
        if (op1 != p1) lerp_pal(p1, pal_ix_from);
        if (op2 != p2) lerp_pal(p2, pal_ix_to);
        line_lite(p1, p2, palette, pal_ix_from, pal_ix_to);
    }

    auto Video::line_lite(const Point<Sint32> &p1, const Point<Sint32> &p2, const RGBAColor c) -> void {
        Point<Sint32> d = p2 - p1;
        Point<Sint32> ad = d.abs();
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

    auto Video::line_lite(const Point<Sint32> &p1, const Point<Sint32> &p2, const Palette &palette, const Uint32 pal_ix_from, const Uint32 pal_ix_to) -> void {
        Point<Sint32> d = p2 - p1;
        Point<Sint32> ad = d.abs();
        Sint32 sdx = d.x < 0 ? -1 : 1;
        Sint32 sdy = d.y < 0 ? -surface_->w : surface_->w;

        Uint32 *pixel_buffer = static_cast<Uint32 *>(surface_->pixels) + p1.y * surface_->w + p1.x;
        auto draw_line = [&](Sint32 abs_g, Sint32 abs_l, Sint32 sig_g, Sint32 sig_l, float ix_inc) -> void {
            float ix = pal_ix_from;
            for (Sint32 i = 0, t = abs_l; i <= abs_g; ++i, t += abs_l) {
                *pixel_buffer = palette[static_cast<Uint32>(ix)];
                if (t >= abs_g) {
                    pixel_buffer += sig_l;
                    t -= abs_g;
                }
                pixel_buffer += sig_g;
                ix += ix_inc;
            }
        };
        if (ad.x >= ad.y) {
            float ix_inc = 1.0f * (pal_ix_to - pal_ix_from) / (ad.x == 0 ? 1 : ad.x);
            draw_line(ad.x, ad.y, sdx, sdy, ix_inc);
        } else {
            float ix_inc = 1.0f * (pal_ix_to - pal_ix_from) / (ad.y == 0 ? 1 : ad.y);
            draw_line(ad.y, ad.x, sdy, sdx, ix_inc);
        }
    }

    auto Video::quad_bezier_lite(const Point<Sint32> &p1, const Point<Sint32> &p2, const Point<Sint32> &p3, const Sint32 max_steps, const RGBAColor c) -> void {
        auto d1 = p2 - p1;
        auto d2 = p3 - p2;
        
        Point<Sint32> pv = p1;
        for (auto s = 1; s <= max_steps; ++s) {
            auto cp1 = lerp_point_b_less_a(p1, d1, s, max_steps);
            auto cp2 = lerp_point_b_less_a(p2, d2, s, max_steps);
            auto bz = lerp_point(cp1, cp2, s, max_steps);
            line_lite(pv, bz, c);
            pv = bz;
        }
    }

    auto Video::quad_bezier_lite(const Point<Sint32> &p1, const Point<Sint32> &p2, const Point<Sint32> &p3, const Sint32 max_steps, const Palette &palette, const Uint32 pal_ix_from, const Uint32 pal_ix_to) -> void {
        auto d1 = p2 - p1;
        auto d2 = p3 - p2;
        
        Point<Sint32> pv = p1;
        float step_size = 1.0f * (pal_ix_to - pal_ix_from) / max_steps;
        for (auto s = 1; s <= max_steps; ++s) {
            Uint32 from = pal_ix_from +  (s - 1) * step_size, to = from + step_size;
            auto cp1 = lerp_point_b_less_a(p1, d1, s, max_steps);
            auto cp2 = lerp_point_b_less_a(p2, d2, s, max_steps);
            auto bz = lerp_point(cp1, cp2, s, max_steps);
            line_lite(pv, bz, palette, from, to);
            pv = bz;
        }        
    }
        

    auto Video::quad_bezier(const Point<Sint32> &p1, const Point<Sint32> &p2, const Point<Sint32> &p3, const Sint32 max_steps, const RGBAColor c) -> void {
        auto d1 = p2 - p1;
        auto d2 = p3 - p2;
        
        Point<Sint32> pv = p1;
        for (auto s = 1; s <= max_steps; ++s) {
            auto cp1 = lerp_point_b_less_a(p1, d1, s, max_steps);
            auto cp2 = lerp_point_b_less_a(p2, d2, s, max_steps);
            auto bz = lerp_point(cp1, cp2, s, max_steps);
            line(pv, bz, c);
            pv = bz;
        }
    }

    auto Video::quad_bezier(const Point<Sint32> &p1, const Point<Sint32> &p2, const Point<Sint32> &p3, const Sint32 max_steps, const Palette &palette, const Uint32 pal_ix_from, const Uint32 pal_ix_to) -> void {
        auto d1 = p2 - p1;
        auto d2 = p3 - p2;
        
        Point<Sint32> pv = p1;
        float step_size = 1.0f * (pal_ix_to - pal_ix_from) / max_steps;
        for (auto s = 1; s <= max_steps; ++s) {
            Uint32 from = pal_ix_from +  (s - 1) * step_size, to = from + step_size;
            auto cp1 = lerp_point_b_less_a(p1, d1, s, max_steps);
            auto cp2 = lerp_point_b_less_a(p2, d2, s, max_steps);
            auto bz = lerp_point(cp1, cp2, s, max_steps);
            line(pv, bz, palette, from, to);
            pv = bz;
        }        
    }
            
    
    auto Video::cubic_bezier_lite(const Point<Sint32> &p1, const Point<Sint32> &p2, const Point<Sint32> &p3, const Point<Sint32> &p4, const Sint32 max_steps, const RGBAColor c) -> void {
        auto d1 = p2 - p1;
        auto d2 = p3 - p2;
        auto d3 = p4 - p3;
        
        Point<Sint32> pv = p1;
        for (auto s = 1; s <= max_steps; ++s) {
            auto cp1 = lerp_point_b_less_a(p1, d1, s, max_steps);
            auto cp2 = lerp_point_b_less_a(p2, d2, s, max_steps);
            auto cp3 = lerp_point_b_less_a(p3, d3, s, max_steps);
            auto bz1 = lerp_point(cp1, cp2, s, max_steps);
            auto bz2 = lerp_point(cp2, cp3, s, max_steps);
            auto bz = lerp_point(bz1, bz2, s, max_steps);

            line_lite(pv, bz, c);
            pv = bz;
        }
    }

    auto Video::cubic_bezier_lite(const Point<Sint32> &p1, const Point<Sint32> &p2, const Point<Sint32> &p3, const Point<Sint32> &p4, const Sint32 max_steps, const Palette &palette, const Uint32 pal_ix_from, const Uint32 pal_ix_to) -> void {
        auto d1 = p2 - p1;
        auto d2 = p3 - p2;
        auto d3 = p4 - p3;
        
        Point<Sint32> pv = p1;
        float step_size = 1.0f * (pal_ix_to - pal_ix_from) / max_steps;
        
        for (auto s = 1; s <= max_steps; ++s) {
            Uint32 from = pal_ix_from +  (s - 1) * step_size, to = from + step_size;
            auto cp1 = lerp_point_b_less_a(p1, d1, s, max_steps);
            auto cp2 = lerp_point_b_less_a(p2, d2, s, max_steps);
            auto cp3 = lerp_point_b_less_a(p3, d3, s, max_steps);
            auto bz1 = lerp_point(cp1, cp2, s, max_steps);
            auto bz2 = lerp_point(cp2, cp3, s, max_steps);
            auto bz = lerp_point(bz1, bz2, s, max_steps);

            line_lite(pv, bz, palette, from, to);
            pv = bz;
        }
    }

    auto Video::cubic_bezier(const Point<Sint32> &p1, const Point<Sint32> &p2, const Point<Sint32> &p3, const Point<Sint32> &p4, const Sint32 max_steps, const RGBAColor c) -> void {
        auto d1 = p2 - p1;
        auto d2 = p3 - p2;
        auto d3 = p4 - p3;
        
        Point<Sint32> pv = p1;
        for (auto s = 1; s <= max_steps; ++s) {
            auto cp1 = lerp_point_b_less_a(p1, d1, s, max_steps);
            auto cp2 = lerp_point_b_less_a(p2, d2, s, max_steps);
            auto cp3 = lerp_point_b_less_a(p3, d3, s, max_steps);
            auto bz1 = lerp_point(cp1, cp2, s, max_steps);
            auto bz2 = lerp_point(cp2, cp3, s, max_steps);
            auto bz = lerp_point(bz1, bz2, s, max_steps);

            line(pv, bz, c);
            pv = bz;
        }
    }

    auto Video::cubic_bezier(const Point<Sint32> &p1, const Point<Sint32> &p2, const Point<Sint32> &p3, const Point<Sint32> &p4, const Sint32 max_steps, const Palette &palette, const Uint32 pal_ix_from, const Uint32 pal_ix_to) -> void {
        auto d1 = p2 - p1;
        auto d2 = p3 - p2;
        auto d3 = p4 - p3;
        
        Point<Sint32> pv = p1;
        float step_size = 1.0f * (pal_ix_to - pal_ix_from) / max_steps;
        
        for (auto s = 1; s <= max_steps; ++s) {
            Uint32 from = pal_ix_from +  (s - 1) * step_size, to = from + step_size;
            auto cp1 = lerp_point_b_less_a(p1, d1, s, max_steps);
            auto cp2 = lerp_point_b_less_a(p2, d2, s, max_steps);
            auto cp3 = lerp_point_b_less_a(p3, d3, s, max_steps);
            auto bz1 = lerp_point(cp1, cp2, s, max_steps);
            auto bz2 = lerp_point(cp2, cp3, s, max_steps);
            auto bz = lerp_point(bz1, bz2, s, max_steps);

            line(pv, bz, palette, from, to);
            pv = bz;
        }
    }

    auto Video::bezier_lite(const std::initializer_list<Point<Sint32>> &points, const Sint32 max_steps, const RGBAColor c) -> void {
        if (points.size() < 3) return;
        Sint32 steps_per_segment_t = static_cast<Sint32>(1.0f * max_steps / (points.size() - 1));
        Sint32 steps_per_segment = steps_per_segment_t == 0 ? 1 : steps_per_segment_t; 

        auto p = points.begin();
        auto p1 = *p;
        do {
            auto p2 = *(p + 1);
            auto p3 = (p + 3) == points.end() ? *(p + 2) : (p2 + (*(p + 2) - p2) / 2);
            quad_bezier_lite(p1, p2, p3, steps_per_segment, c);
            p1 = p3;
            ++p;
        } while ((p + 2) != points.end());
    }

    auto Video::bezier_lite(const std::initializer_list<Point<Sint32>> &points, const Sint32 max_steps, const Palette &palette, const Uint32 pal_ix_from, const Uint32 pal_ix_to) -> void {
        if (points.size() < 3) return;
        Sint32 steps_per_segment_t = static_cast<Sint32>(1.0f * max_steps / (points.size() - 1));
        Sint32 steps_per_segment = steps_per_segment_t == 0 ? 1 : steps_per_segment_t; 
        float step_size = 1.0f * (pal_ix_to - pal_ix_from) / (points.size() - 2);
        
        auto p = points.begin();
        auto p1 = *p;
        Sint32 s = 0;
        do {
            Uint32 from = pal_ix_from + (s++) * step_size, to = from + step_size;
            auto p2 = *(p + 1);
            auto p3 = (p + 3) == points.end() ? *(p + 2) : (p2 + (*(p + 2) - p2) / 2);
            quad_bezier_lite(p1, p2, p3, steps_per_segment, palette, from, to);
            p1 = p3;
            ++p;
        } while ((p + 2) != points.end());
    }

    auto Video::bezier(const std::initializer_list<Point<Sint32>> &points, const Sint32 max_steps, const RGBAColor c) -> void {
        if (points.size() < 3) return;
        Sint32 steps_per_segment_t = static_cast<Sint32>(1.0f * max_steps / (points.size() - 1));
        Sint32 steps_per_segment = steps_per_segment_t == 0 ? 1 : steps_per_segment_t; 

        auto p = points.begin();
        auto p1 = *p;
        do {
            auto p2 = *(p + 1);
            auto p3 = (p + 3) == points.end() ? *(p + 2) : (p2 + (*(p + 2) - p2) / 2);
            quad_bezier(p1, p2, p3, steps_per_segment, c);
            p1 = p3;
            ++p;
        } while ((p + 2) != points.end());
    }

    auto Video::bezier(const std::initializer_list<Point<Sint32>> &points, const Sint32 max_steps, const Palette &palette, const Uint32 pal_ix_from, const Uint32 pal_ix_to) -> void {
        if (points.size() < 3) return;
        Sint32 steps_per_segment_t = static_cast<Sint32>(1.0f * max_steps / (points.size() - 1));
        Sint32 steps_per_segment = steps_per_segment_t == 0 ? 1 : steps_per_segment_t; 
        float step_size = 1.0f * (pal_ix_to - pal_ix_from) / (points.size() - 2);
        
        auto p = points.begin();
        auto p1 = *p;
        Sint32 s = 0;
        do {
            Uint32 from = pal_ix_from + (s++) * step_size, to = from + step_size;
            auto p2 = *(p + 1);
            auto p3 = (p + 3) == points.end() ? *(p + 2) : (p2 + (*(p + 2) - p2) / 2);
            quad_bezier(p1, p2, p3, steps_per_segment, palette, from, to);
            p1 = p3;
            ++p;
        } while ((p + 2) != points.end());
    }

    auto Video::catmullrom_spline_lite(const std::initializer_list<Point<Sint32>> &points, const Sint32 max_steps, const RGBAColor c) -> void {
        if (points.size() < 4) return;
        const float segments = 1.0f * max_steps / (points.size() - 3);
        auto p = points.begin();
        do {
            auto p1 = *p;
            auto p2 = *(p + 1);
            auto p3 = *(p + 2);
            auto p4 = *(p + 3);
            Point<Sint32> prev = p2;
            for (float u = 0, uinc = 1.0f / segments; u <= 1.0f; u += uinc) {
                float uu = u * u;
                float uuu = uu * u;
                float nc1 = -uuu + 2.0f * uu - u;
                float nc2 = 3.0f * uuu - 5.0f * uu + 2.0f;
                float nc3 = -3.0f * uuu + 4.0f * uu + u;
                float nc4 = uuu - uu;
                Point<float> b = (p1 * nc1 + p2 * nc2 + p3 * nc3 + p4 * nc4) * 0.5f;
                line_lite(prev, b, c);
                prev = b;
            }
            line_lite(prev, p3, c);
            ++p;
        } while (p + 3 != points.end());
    }

    auto Video::catmullrom_spline(const std::initializer_list<Point<Sint32>> &points, const Sint32 max_steps, const RGBAColor c) -> void {
        if (points.size() < 4) return;
        const float segments = 1.0f * max_steps / (points.size() - 3);
        auto p = points.begin();
        do {
            auto p1 = *p;
            auto p2 = *(p + 1);
            auto p3 = *(p + 2);
            auto p4 = *(p + 3);
            Point<Sint32> prev = p2;
            for (float u = 0, uinc = 1.0f / segments; u <= 1.0f; u += uinc) {
                float uu = u * u;
                float uuu = uu * u;
                float nc1 = -uuu + 2.0f * uu - u;
                float nc2 = 3.0f * uuu - 5.0f * uu + 2.0f;
                float nc3 = -3.0f * uuu + 4.0f * uu + u;
                float nc4 = uuu - uu;
                Point<float> b = (p1 * nc1 + p2 * nc2 + p3 * nc3 + p4 * nc4) * 0.5f;
                line_lite(prev, b, c);
                prev = b;
            }
            line(prev, p3, c);
            ++p;
        } while (p + 3 != points.end());
    }

    auto Video::catmullrom_spline_lite(const std::initializer_list<Point<Sint32>> &points, const Sint32 max_steps, const Palette &palette, const Uint32 pal_ix_from, const Uint32 pal_ix_to) -> void {
        if (points.size() < 4) return;
        const float segments = 1.0f * max_steps / (points.size() - 3);
        float step_size = 1.0f * (pal_ix_to - pal_ix_from) / (points.size() - 3);
        
        auto p = points.begin();
        float from = pal_ix_from, to = from;
        do {
            auto p1 = *p;
            auto p2 = *(p + 1);
            auto p3 = *(p + 2);
            auto p4 = *(p + 3);
            Point<float> prev = p2;
            for (float u = 0, uinc = 1.0f / segments, pal_inc = step_size / segments; u <= 1.0f; u += uinc, to += pal_inc) {
                float uu = u * u;
                float uuu = uu * u;
                float nc1 = -uuu + 2.0f * uu - u;
                float nc2 = 3.0f * uuu - 5.0f * uu + 2.0f;
                float nc3 = -3.0f * uuu + 4.0f * uu + u;
                float nc4 = uuu - uu;
                Point<float> b = (p1 * nc1 + p2 * nc2 + p3 * nc3 + p4 * nc4) * 0.5f;
                line_lite(prev, b, palette, from, to);
                prev = b;
                from = to;
            }
            line(prev, p3, palette, from, to);
            ++p;
        } while (p + 3 != points.end());        
    }
        
}
#endif 
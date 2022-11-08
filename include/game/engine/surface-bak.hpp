#pragma once

#include <SDL.h>
#include "game/gfx/base_point.hpp"
#include "game/gfx/common.hpp" 

namespace g80::game::engine {

    using namespace g80::game::gfx;

    class surface {

    // Surface Main Components
    // --
    private:
        SDL_Surface     *s_;                        
        int_type        wb_, hb_;                   
        bool            is_surface_from_window_;

    public:
        surface(SDL_Window *window) :               
            s_(SDL_GetWindowSurface(window)), 
            wb_(s_->w - 1), 
            hb_(s_->h - 1), 
            is_surface_from_window_(true) {
        }

        surface(int w, int h, Uint32 format) :
            s_(SDL_CreateRGBSurfaceWithFormat(0, w, h, 32, format)), 
            wb_(s_->w - 1), 
            hb_(s_->h - 1), 
            is_surface_from_window_(false) {
        }

        surface(const surface &) = delete;
        surface(surface &&) = delete;
        auto operator=(const surface &) -> surface & = delete;
        auto operator=(surface &&) -> surface & = delete;
        ~surface() {if(!is_surface_from_window_) SDL_FreeSurface(s_);}

        auto set_surface_from_window(SDL_Window *window) -> SDL_Surface * {
            if(!is_surface_from_window_) return NULL;
            s_ = SDL_GetWindowSurface(window); 
            if(!s_) return NULL;
            wb_ = s_->w - 1;
            hb_ = s_->h - 1;
            return s_;
        }

        inline auto get_handle() -> SDL_Surface * {return s_;}
        inline auto is_valid() const -> bool {return s_ != NULL;}
        inline auto get_w() const -> int_type {return s_->w;}
        inline auto get_h() const -> int_type {return s_->h;}
        inline auto get_cw() const -> int_type {return s_->w / 2;}
        inline auto get_ch() const -> int_type {return s_->h / 2;}
        inline auto get_format() const -> SDL_PixelFormat * {return s_->format;}
        inline auto get_pixels() const -> void * {return s_->pixels;}
        inline auto get_wb() const -> int_type {return wb_;}
        inline auto get_hb() const -> int_type {return hb_;}

    // Pixel validators
    public:
        inline auto is_point_within_bounds(const int_type x, const int_type y) const -> bool {
            if(x < 0 || y < 0 || x >= s_->w || y >= s_->h) return false; 
            return true;
        }
        inline auto is_point_within_bounds(const point &p) const -> bool {
            if(p.x < 0 || p.y < 0 || p.x >= s_->w || p.y >= s_->h) return false; 
            return true;
        }

    // Pixel
    // --
    public:
        inline auto pixel(const int_type x, const int_type y, const Uint32 rgba) -> void {
            *((static_cast<Uint32 *>(s_->pixels) + x) + (y * s_->w)) = rgba;
        }    
        inline auto pixel(const point &p, const Uint32 rgba) -> void {
            *((static_cast<Uint32 *>(s_->pixels) + p.x) + (p.y * s_->w)) = rgba;
        }
        auto pixel_s(const int_type x, const int_type y, const Uint32 rgba) -> void {
            if(!is_point_within_bounds(x, y)) [[unlikely]] return;
            pixel(x, y, rgba);
        }    
        auto pixel_s(const point &p, const Uint32 rgba) -> void {
            if(!is_point_within_bounds(p)) [[unlikely]] return;
            pixel(p, rgba);
        }

    // Line
    // --
    private:
        enum SCREEN_PLANE{TOP_LEFT = 0, TOP = 1, TOP_RIGHT = 2, LEFT = 3, ON_SCREEN = 4, 
                            RIGHT = 5, BOTTOM_LEFT = 6, BOTTOM = 7, BOTTOM_RIGHT = 8};

        auto get_screen_plane(const point &p) const -> SCREEN_PLANE {
            if(p.x >= 0) [[likely]] {
                if(p.x < s_->w) [[likely]] {
                    if(p.y >= 0) [[likely]] {
                        if(p.y < s_->h) [[likely]] return ON_SCREEN;
                        else return BOTTOM;
                    } else return TOP;
                } else {
                    if(p.y < 0) return TOP_RIGHT;
                    else if(p.y >= s_->h) return BOTTOM_RIGHT;
                    else return RIGHT;
                }
            } else {
                if(p.y < 0) return TOP_LEFT;
                else if(p.y >= s_->h) return BOTTOM_LEFT;
                else return LEFT;
            }
        }

        // It is assumed that recalculation is required if this function is called
        // Either point1(x1, y1) or point2 (x2, y2) is/are not ON_SCREEN
        auto recalc_line_points(point &p1, point &p2, const SCREEN_PLANE sp1, const SCREEN_PLANE sp2) -> bool {
            fp_type h = p2.y - p1.y;
            fp_type w = p2.x - p1.x;

            // Call only if it's beyond ON_SCREEN
            // ∴ the condition if(y == y_equals) return x is not applicable;
            auto get_x_at_y_equals = [&](const point &p, const int_type y_equals) -> int_type {
                if(w == 0) return p.x;
                fp_type m = h / w;
                fp_type b = p.y - (m * p.x);
                return static_cast<int_type>((y_equals - b) / m);
            };

            // Call only if it's beyond ON_SCREEN
            // ∴ the condition if(w == 0) is not applicable;
            auto get_y_at_x_equals = [&](const point &p, const int_type x_equals) -> int_type {
                if(h == 0) return p.y;
                fp_type m = h / w;
                fp_type b = p.y - (m * p.x);
                return static_cast<int_type>(m * x_equals + b);
            };

            // Call only if one of the points is out of bounds
            // ∴ the condition screen_plane == ON_SCREEN is not applicable 
            auto recalc_point_at_bound = [&](point &p, SCREEN_PLANE screen_plane) -> void {

                auto is_x_at_top = [&]() -> bool {if(auto tx = get_x_at_y_equals(p, 0); 
                                                    is_point_within_bounds(tx, 0)) {p.x = tx; p.y = 0; return true;} 
                                                    return false;};
                auto is_x_at_bottom = [&]() -> bool {if(auto tx = get_x_at_y_equals(p, hb_); 
                                                        is_point_within_bounds(tx, hb_)) {p.x = tx; p.y = hb_; return true;} 
                                                        return false;};
                auto get_x_at_top = [&]() -> void {p.x = get_x_at_y_equals(p, 0); p.y = 0;};
                auto get_x_at_bottom = [&]() -> void {p.x = get_x_at_y_equals(p, hb_); p.y = hb_;};
                auto get_y_at_left = [&]() -> void {p.y = get_y_at_x_equals(p, 0); p.x = 0;};
                auto get_y_at_right = [&]() -> void {p.y = get_y_at_x_equals(p, wb_); p.x = wb_;};
                auto check_top_left = [&]() -> void {if(is_x_at_top()) return; get_y_at_left(); return;};
                auto check_top_right = [&]() -> void {if(is_x_at_top()) return; get_y_at_right(); return;};
                auto check_bottom_left = [&]() -> void {if(is_x_at_bottom()) return; get_y_at_left(); return;};
                auto check_bottom_right = [&]() -> void {if(is_x_at_bottom()) return; get_y_at_right(); return;};

                switch(screen_plane) {
                    case TOP_LEFT: check_top_left(); break;
                    case TOP: get_x_at_top(); break;
                    case TOP_RIGHT: check_top_right(); break;
                    case BOTTOM_LEFT: check_bottom_left(); break;
                    case BOTTOM_RIGHT: check_bottom_right(); break;
                    case BOTTOM: get_x_at_bottom(); break;
                    case LEFT: get_y_at_left(); break;
                    case RIGHT: get_y_at_right(); break;
                    default: break;
                }
            };

            if(sp1 != ON_SCREEN) {
                recalc_point_at_bound(p1, sp1);
                if(get_screen_plane(p1) != ON_SCREEN) return false;
            }

            if(sp2 != ON_SCREEN) {
                recalc_point_at_bound(p2, sp2);
                if(get_screen_plane(p2) != ON_SCREEN) return false;
            }

            return true;
        }

    public:
        auto line(const point &p1, const point &p2, const Uint32 rgba) -> void {
            auto d = p2 - p1;
            auto ad = d.abs();
            int_type sdx = d.x < 0 ? -1 : 1;
            int_type sdy = d.y < 0 ? -s_->w : s_->w;
            Uint32 *pixel_buffer = static_cast<Uint32 *>(s_->pixels) + p1.y * s_->w + p1.x;
            auto draw_line = [&](int_type abs_g, int_type abs_l, int_type sig_g, int_type sig_l) -> void {
                for (int_type i = 0, t = abs_l; i <= abs_g; ++i, t += abs_l) {
                    *pixel_buffer = rgba;
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

        auto line_s(point p1, point p2, const Uint32 rgba) -> void {
            auto sp1 = get_screen_plane(p1);
            auto sp2 = get_screen_plane(p2);
            if(sp1 != ON_SCREEN || sp2 != ON_SCREEN) [[unlikely]] 
                if(!recalc_line_points(p1, p2, sp1, sp2)) return;
            line(p1, p2, rgba);
       }    
    };
}
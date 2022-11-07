#pragma once

#include <SDL.h>
#include "game/gfx/base_point.hpp"
#include "game/gfx/common.hpp"
#include "game/gfx/pset.hpp"

namespace g80::game::engine {

    using namespace g80::game::gfx;

    class surface {
    private:
        SDL_Surface *s_;
        int_type wb_, hb_;
        bool is_surface_window_;
        
    public:

        // Window Surface
        surface(SDL_Window *window) : 
            s_(SDL_GetWindowSurface(window)), 
            wb_(s_->w - 1), hb_(s_->h - 1), 
            is_surface_window_(true) {
        }
        
        // Custom Surface
        surface(int w, int h, Uint32 format) : 
            s_(SDL_CreateRGBSurfaceWithFormat(0, w, h, 32, format)), 
            wb_(s_->w - 1), hb_(s_->h - 1), 
            is_surface_window_(false) {
        }

        auto set_surface_from_window(SDL_Window *window) -> SDL_Surface * {
            if(!is_surface_window_) return NULL;
            s_ = SDL_GetWindowSurface(window); 
            if(!s_) return NULL;
            wb_ = s_->w - 1;
            hb_ = s_->h - 1;
            return s_;
        }

        // Deleted constructors and assignments 
        surface(const surface &) = delete;
        surface(surface &&) = delete;
        auto operator=(const surface &) -> surface & = delete;
        auto operator=(surface &&) -> surface & = delete;

        // Destructor
        ~surface() {
            if(!is_surface_window_)SDL_FreeSurface(s_);
        }

        // Getters
        inline auto get_handle() -> SDL_Surface * {return s_;}
        inline auto is_valid() const -> bool {return s_ != NULL;}
        inline auto get_wb() const -> int_type {return wb_;}
        inline auto get_hb() const -> int_type {return hb_;}


        // Validators
        inline auto is_point_within_bounds(const point &p) const -> bool {
            if(p.x < 0 || p.y < 0 || p.x >= s_->w || p.y >= s_->h) return false; 
            return true;
        }

    // Pixel
    // --
    public:
        auto pixel(const point &p, const uint_type rgba) -> void {
            if(!is_point_within_bounds(p)) [[unlikely]] return;
            *((static_cast<uint_type *>(s_->pixels) + p.x) + (p.y * s_->w)) = rgba;
        }

    // Line
    // --
    private:
        enum SCREEN_PLANE{TOP_LEFT = 0, TOP = 1, TOP_RIGHT = 2, LEFT = 3, ON_SCREEN = 4, RIGHT = 5, BOTTOM_LEFT = 6, BOTTOM = 7, BOTTOM_RIGHT = 8};
        auto get_screen_plane(const SDL_Surface *s, const point &p) const -> SCREEN_PLANE {
            if(p.x >= 0) [[likely]] {
                if(p.x < s->w) [[likely]] {
                    if(p.y >= 0) [[likely]] {
                        if(p.y < s->h) [[likely]] return ON_SCREEN;
                        else return BOTTOM;
                    } else return TOP;
                } else {
                    if(p.y < 0) return TOP_RIGHT;
                    else if(p.y >= s->h) return BOTTOM_RIGHT;
                    else return RIGHT;
                }
            } else {
                if(p.y < 0) return TOP_LEFT;
                else if(p.y >= s->h) return BOTTOM_LEFT;
                else return LEFT;
            }
        }

        // It is assumed that recalculation is required if this function is called
        // Either point1(x1, y1) or point2 (x2, y2) is/are not ON_SCREEN
        auto recalc_line_points(const SDL_Surface *s, point &p1, point &p2, const SCREEN_PLANE sp1, const SCREEN_PLANE sp2) -> bool {
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
                auto is_x_at_top = [&]() -> bool {if(auto tx = get_x_at_y_equals(x, y, 0); 
                                                        is_point_within_bounds(tx, 0, s->w, s->h)) {x = tx; y = 0; return true;} 
                                                    return false;};
                auto is_x_at_bottom = [&]() -> bool {if(auto tx = get_x_at_y_equals(x, y, s->h - 1); 
                                                        is_point_within_bounds(tx, s->h - 1, s->w, s->h)) {x = tx; y = s->h - 1; return true;} 
                                                    return false;};
                auto get_x_at_top = [&]() -> void {x = get_x_at_y_equals(x, y, 0); y = 0;};
                auto get_x_at_bottom = [&]() -> void {x = get_x_at_y_equals(x, y, s->h - 1); y = s->h - 1;};
                auto get_y_at_left = [&]() -> void {y = get_y_at_x_equals(x, y, 0); x = 0;};
                auto get_y_at_right = [&]() -> void {y = get_y_at_x_equals(x, y, s->w - 1); x = s->w - 1;};
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
                recalc_point_at_bound(x1, y1, sp1);
                if(get_screen_plane(s, x1, y1) != ON_SCREEN) return false;
            }

            if(sp2 != ON_SCREEN) {
                recalc_point_at_bound(x2, y2, sp2);
                if(get_screen_plane(s, x2, y2) != ON_SCREEN) return false;
            }

            return true;
        }


    };
}
#pragma once

#include <SDL.h>
#include "game/engine/common.hpp" 

namespace g80::game::engine {

    class surface {
    public:
        enum SCREEN_PLANE{TOP_LEFT = 0, TOP = 1, TOP_RIGHT = 2, LEFT = 3, ON_SCREEN = 4, RIGHT = 5, BOTTOM_LEFT = 6, BOTTOM = 7, BOTTOM_RIGHT = 8};
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
        inline auto get_handle() const -> const SDL_Surface * {return s_;}
        inline auto is_valid() const -> bool {return s_ != NULL;}
        inline auto get_w() const -> int_type {return s_->w;}
        inline auto get_h() const -> int_type {return s_->h;}
        inline auto get_cw() const -> int_type {return s_->w / 2;}
        inline auto get_ch() const -> int_type {return s_->h / 2;}
        inline auto get_format() const -> SDL_PixelFormat * {return s_->format;}
        inline auto get_pixels() const -> void * {return s_->pixels;}
        inline auto get_wb() const -> int_type {return wb_;}
        inline auto get_hb() const -> int_type {return hb_;}

    public:
        inline auto is_point_within_bounds(const int_type x, const int_type y) const -> bool {
            if(x < 0 || y < 0 || x >= s_->w || y >= s_->h) return false; 
            return true;
        }
        inline auto is_point_within_bounds(const point &p) const -> bool {
            if(p.x < 0 || p.y < 0 || p.x >= s_->w || p.y >= s_->h) return false; 
            return true;
        }

    };
}
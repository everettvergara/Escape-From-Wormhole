#pragma once

#include <SDL.h>
#include "game/engine/common.hpp" 

namespace g80::game::engine {

    class surface {
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

        inline auto get_s() -> SDL_Surface * {return s_;}
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
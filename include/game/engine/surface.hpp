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
        auto pixel(const point &p, const uint_type rgba) -> void {
            if(!is_point_within_bounds(p)) [[unlikely]] return;
            *((static_cast<uint_type *>(s_->pixels) + p.x) + (p.y * s_->w)) = rgba;
        }

    };
}
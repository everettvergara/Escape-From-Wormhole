#pragma once

#include <SDL.h>
#include "game/gfx/pset.hpp"

namespace g80::game::engine {

    class surface {
    private:
        SDL_Surface *surface_;
        bool is_surface_from_window_;
        
    public:

        // Window Surface
        surface(SDL_Window *window) : 
            surface_(SDL_GetWindowSurface(window)), is_surface_from_window_(true) {
        }
        
        // Custom Surface
        surface(int w, int h, Uint32 format) : 
            surface_(SDL_CreateRGBSurfaceWithFormat(0, w, h, 32, format)), is_surface_from_window_(false) {
        }

        // Deleted constructors and assignments 
        surface(const surface &) = delete;
        surface(surface &&) = delete;
        auto operator=(const surface &) -> surface & = delete;
        auto operator=(surface &&) -> surface & = delete;

        // Destructor
        ~surface() {
            if(!is_surface_from_window_)SDL_FreeSurface(surface_);
        }

        // Getters
        auto get_handle() -> SDL_Surface * {return surface_;}
        auto is_valid() -> bool {return surface_ != NULL;}
    };
}
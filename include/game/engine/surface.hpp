#pragma once

#include <SDL.h>

namespace g80::game::engine {

    class surface {
    private:
        SDL_Surface *surface_;
        bool is_surface_from_window_;
        
    public:
        surface(SDL_Window *window) : surface_(SDL_GetWindowSurface(window)), is_surface_from_window_(true) {}
        surface(int w, int h, Uint32 format) : surface_(SDL_CreateRGBSurfaceWithFormat(0, w, h, 32, format)), is_surface_from_window_(false) {}
        
        surface(const surface &) = delete;
        surface(surface &&) = delete;
        auto operator=(const surface &) -> surface & = delete;
        auto operator=(surface &&) -> surface & = delete;
        ~surface() {SDL_FreeSurface(surface_);}

        auto is_valid() -> bool {return surface_ != NULL;}
        auto get_handle() -> SDL_Surface * {return surface_;}
    };
}
#pragma once

#include <SDL.h>

namespace g80::game::engine {

    class surface {
    private:
        SDL_Surface *surface_;
    public:
        surface(int w, int h, Uint32 format) : surface_(SDL_CreateRGBSurfaceWithFormat(0, w, h, 32, format)) {}
        surface(const surface &) = delete;
        surface(surface &&) = delete;
        auto operator=(const surface &) -> surface & = delete;
        auto operator=(surface &&) -> surface & = delete;
        ~surface() {SDL_FreeSurface(surface_);}
        auto is_valid() -> bool {return surface_ != NULL;}
        auto get_handle() -> SDL_Surface * {return surface_;}
    };
}
#pragma once

#include <SDL.h>

namespace g80::game::engine {

    class window {

    private:
        SDL_Window *window_;

    public:
        window(const char *title, int x, int y, int w, int h, Uint32 flags) : window_(SDL_CreateWindow(title, x, y, w, h, flags)) {}
        window(const window &) = delete;
        window(window &&) = delete;
        auto operator=(const window &) -> window & = delete;
        auto operator=(window &&) -> window & = delete;
        ~window() {SDL_DestroyWindow(window_);}
        inline auto is_valid() -> bool {return window_ != NULL;}
        inline auto get_handle() -> SDL_Window * {return window_;}
        inline auto get_surface() -> SDL_Surface * {return SDL_GetWindowSurface(window_);}
    };

}
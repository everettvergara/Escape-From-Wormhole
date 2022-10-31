#pragma once

#include <unordered_map>
#include <optional>
#include "sys/common.hpp"
#include "base_point.hpp"
#include "config.hpp"

namespace g80::video {

    using point = base_point<g80::sys::int_type>;

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

    class surface32 {
    private:
        SDL_Surface *surface_;
    public:
        surface32(int w, int h, Uint32 format) : surface_(SDL_CreateRGBSurfaceWithFormat(0, w, h, 32, format)) {}
        ~surface32() {SDL_FreeSurface(surface_);}
        auto get_surface() -> SDL_Surface * {return surface_;}
    };

    class video {

    // Static Helpers for initialization    
    private:
        static bool is_init_;
    public:
        static inline auto is_init() -> bool {return is_init_;}
        static auto init() -> bool {if(!is_init_) is_init_ = SDL_VideoInit(NULL) ? true : false; return is_init_;}
        static auto quit() -> void {SDL_VideoQuit();}

    // Constructors, Destructors and Assignments
    public:
        video() {}
        video(const config &c) = delete;
        video(config &&c) = delete;
        auto operator=(const config &) -> config & = delete;
        auto operator=(config &&) -> config & = delete;
        virtual ~video() {destroy_window();};

    // Windows and surfaces
    private:
        SDL_Window *window_;
        std::unordered_map<size_t, surface32> surfaces_;
    public:
        inline auto get_window() -> SDL_Window * {return window_;}
        auto create_window(const config &c) -> bool {return window_ ? false : ((window_ = SDL_CreateWindow(c.title.c_str(), c.x, c.y, c.w, c.h, c.flags)) ? true : false);}
        auto destroy_window() -> void {SDL_DestroyWindow(window_); window_ = NULL;}
        auto get_surface() -> SDL_Surface * {return SDL_GetWindowSurface(window_);}
        auto create_surface(const size_t id, int w, int h) -> bool {
            if(!window_) return false;
            
            auto surface = get_surface(); 
            if(!surface) return false;

            surfaces_.try_emplace(id, surface32{w, h, surface->format->format});
            
            return true;
        }

    };

    bool video::is_init_{false};
}
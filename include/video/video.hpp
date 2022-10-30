#pragma once

#include <unordered_map>
#include <optional>
#include "sys/common.hpp"
#include "base_point.hpp"
#include "config.hpp"

namespace g80::video {

    using point = base_point<g80::sys::int_type>;

    class surface32 {
    private:
        SDL_Surface *surface_;
    public:
        surface(const int w, const int h, const Uint32 format) : surface_(SDL_CreateRGBSurfaceWithFormat(0, w, h, 32, format)) {}
        auto get_surface() -> SDL_Surface * {return surface_;}
        ~surface() {SDL_FreeSurface(surface_);}
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
        std::unordered_map<size_t, SDL_Surface *> surfaces_;
    public:
        inline auto get_window() -> SDL_Window * {return window_;}
        auto create_window(const config &c) -> bool {return window_ ? false : ((window_ = SDL_CreateWindow(c.title.c_str(), c.x, c.y, c.w, c.h, c.flags)) ? true : false);}
        auto destroy_window() -> void {SDL_DestroyWindow(window_); window_ = NULL;}
        auto get_surface() -> SDL_Surface * {return SDL_GetWindowSurface(window_);}
        auto create_surface(const size_t id, const int w, const int h) -> bool {
            if(!window_) return false;
            
            auto surface = get_surface(); 
            if(!surface) return false;

            auto t = SDL_CreateRGBSurfaceWithFormat(0, w, h, 32, surface->format);
            return t ? true : false;
        }

    };

    bool video::is_init_{false};
}
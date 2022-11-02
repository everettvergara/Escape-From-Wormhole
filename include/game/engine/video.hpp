#pragma once

#include <memory>
#include <SDL.h>
#include "game/engine/window.hpp"
#include "game/engine/surface.hpp"
#include "game/engine/config.hpp"

namespace g80::game::engine {

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
        virtual ~video() {};

    // Window
    private:
        std::unique_ptr<window> window_{nullptr};
        SDL_Window *sdl_window_;
    public:
        auto create_window(const config &c) -> bool {
            window_.reset(new window(c.title.c_str(), c.x, c.y, c.w, c.h, c.flags));
            sdl_window_ = window_->get_handle();
            return window_->is_valid();
        }
        auto get_window() -> window & {return *window_.get();}
        inline auto get_sdl_window() -> SDL_Window * {return sdl_window_;}
        auto reset_window() -> void {window_.reset(nullptr);}

    // Run and Events
    private:
        bool is_running_;
    public:
        virtual auto update_window_surface() -> void {
            SDL_UpdateWindowSurface(sdl_window_);
        }

        virtual auto capture_events() -> void {
            SDL_Event e;
            while(SDL_PollEvent(&e)) {
                if(e.type == SDL_QUIT) {
                    is_running_ = false;
                    break;
                }
            }
        }

        virtual auto update_states() -> void {
            auto *surface = SDL_GetWindowSurface(sdl_window_);
            SDL_FillRect(surface, NULL, 0);
        }

        auto run(const Uint32 MSPF) -> void {
            is_running_ = true;
            [[likely]] while(is_running_) {
                Uint32 start = SDL_GetTicks();
                update_window_surface();
                capture_events();
                update_states();
                Uint32 end = SDL_GetTicks();
                Uint32 elapsed = end - start;
                if (elapsed < MSPF) [[likely]] SDL_Delay(MSPF - elapsed);
            }
        }
    };

    bool video::is_init_{false};
}
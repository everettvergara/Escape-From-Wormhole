#pragma once

#include <memory>
#include <SDL.h>
#include "window.hpp"
#include "surface.hpp"
#include "config.hpp"

namespace g80::video {

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
    public:
        auto create_window(const config &c) -> bool {
            window_.reset(new window(c.title.c_str(), c.x, c.y, c.w, c.h, c.flags));
            return window_->is_valid();
        }
        auto get_window() -> window & {return *window_.get();}
        auto reset_window() -> void {window_.reset(nullptr);}

    // Run and Events
    private:
        bool is_running_;
    public:
        virtual auto update_window_surface() -> void {}
        virtual auto capture_events() -> void {}
        virtual auto update_states() -> void {}
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
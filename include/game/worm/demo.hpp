#pragma once

#include "game/engine/video.hpp"

namespace g80::game::worm {

    using namespace g80::game::engine;
    class demo : public video {

    // Run and Events
    private:
        g80::sys::fp_type rads_ {0.0};
    public:
        virtual auto update_states() -> void {
            auto *surface = SDL_GetWindowSurface(sdl_window_);
            SDL_FillRect(surface, NULL, 0);
            using namespace g80::game::gfx;
            pset(surface, 100, 100, SDL_MapRGBA(surface->format, 255, 0, 0, 255));
            rads_ += 0.01;
            // line(surface, surface->w / 2, surface->h / 2, surface->w / 2 + static_cast<int_type>(200 * SDL_cosf(rads_)), surface->h / 2 + static_cast<int_type>(200 * SDL_sinf(rads_)), SDL_MapRGBA(surface->format, 255, 0, 0, 255));
            line(surface, surface->w / 2, surface->h / 2, surface->w / 2 + static_cast<int_type>(surface->w * SDL_cosf(rads_)), surface->h / 2 + static_cast<int_type>(surface->w * SDL_sinf(rads_)), SDL_MapRGBA(surface->format, 255, 0, 0, 255));
        }
    };
}
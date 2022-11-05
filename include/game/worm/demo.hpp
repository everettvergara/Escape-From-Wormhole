#pragma once
#include <cstdlib>
#include "game/engine/video.hpp"
#include "game/gfx/pset.hpp"

namespace g80::game::worm {

    using namespace g80::game::engine;
    using namespace g80::game::gfx;
    
    class demo : public video {

    // Run and Events
    private:
        g80::sys::fp_type rads_ {0.0};
    public:
        demo() {}

        auto update_states() -> void override {
            auto *surface = SDL_GetWindowSurface(sdl_window_);
            SDL_FillRect(surface, NULL, 0);
            //pset_.draw(100, 100, SDL_MapRGBA(pset_.get_surface()->format, 255, 0, 0, 255));
            for(size_t i{0}; i< 1000; ++i) {
                pset_.draw(rand() % pset_.get_surface()->w, rand() % pset_.get_surface()->h, SDL_MapRGBA(pset_.get_surface()->format, 255, 0, 0, 255));
            }
            // using namespace g80::game::gfx;
            // pset(surface, 100, 100, SDL_MapRGBA(surface->format, 255, 0, 0, 255));
            // rads_ += 0.01;
            // line(surface, surface->w / 2, surface->h / 2, surface->w / 2 + static_cast<int_type>(200 * SDL_cosf(rads_)), surface->h / 2 + static_cast<int_type>(200 * SDL_sinf(rads_)), SDL_MapRGBA(surface->format, 255, 0, 0, 255));
            // line(surface, surface->w / 2, surface->h / 2, surface->w / 2 + static_cast<int_type>(surface->w * SDL_cosf(rads_)), surface->h / 2 + static_cast<int_type>(surface->w * SDL_sinf(rads_)), SDL_MapRGBA(surface->format, 255, 0, 0, 255));
        }
    };
}
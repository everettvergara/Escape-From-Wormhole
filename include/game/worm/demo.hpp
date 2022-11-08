#pragma once
#include <cstdlib>
#include <SDL.h>
#include "game/engine/video.hpp"
#include "game/engine/surface.hpp"
#include "game/engine/gfx_pixel.hpp"
#include "game/engine/gfx_line.hpp"

namespace g80::game::worm {

    using namespace g80::game::engine;
    
    class demo : public video {

    // Run and Events
    private:
        g80::sys::fp_type rads_ {0.0};
    public:
        demo() {}

        auto update_states() -> void override {
            
            surface s(sdl_window_);
            gfx_pixel pixel(&s);
            gfx_line line(&s);

            SDL_FillRect(s.get_handle(), NULL, 0); 
            for(size_t i{0}; i< 1000; ++i) {
                
                pixel.draw(rand() % s.get_handle()->w,
                        rand() % s.get_handle()->h,
                        SDL_MapRGBA(s.get_handle()->format, 255, 0, 0, 255));
            }

            rads_ += 0.01;
            line.draw( point{s.get_cw(), s.get_ch()}, 
                        point{s.get_cw() + static_cast<int_type>(200 * SDL_cosf(rads_)), s.get_ch() + static_cast<int_type>(200 * SDL_sinf(rads_))}, 
                    SDL_MapRGBA(s.get_format(), 255, 0, 0, 255));
            // s.line_s( point{s.get_cw(), s.get_ch()}, 
            //             point{s.get_cw() + static_cast<int_type>(s.get_w() * SDL_cosf(rads_)), s.get_ch() + static_cast<int_type>(s.get_w() * SDL_sinf(rads_))}, 
            //         SDL_MapRGBA(s.get_format(), 255, 0, 0, 255));
        }
    };
}



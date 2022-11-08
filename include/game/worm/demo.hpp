#pragma once
#include <cstdlib>
#include <SDL.h>
#include "game/engine/video.hpp"
#include "game/engine/surface.hpp"
#include "game/gfx/pixel.hpp"
#include "game/gfx/line.hpp"

namespace g80::game::worm {

    using namespace g80::game::engine;
    
    class demo : public video {

    // Run and Events
    private:
        fp_type rads_ {0.0};
    public:
        demo() {}

        auto update_states() -> void override {
            
            surface s(sdl_window_);
            g80::game::gfx::pixel pixel(&s);
            g80::game::gfx::line line(&s);

            SDL_FillRect(s.get_handle(), NULL, 0); 
            for(size_t i{0}; i< 1000; ++i) {
                
                pixel.draw(rand() % s.get_handle()->w,
                        rand() % s.get_handle()->h,
                        SDL_MapRGBA(s.get_handle()->format, 255, 0, 0, 255));
            }

            rads_ += 0.01;
            line.draw_masked( point{s.get_cw(), s.get_ch()}, 
                        point{s.get_cw() + static_cast<int_type>(200 * SDL_cosf(rads_)), s.get_ch() + static_cast<int_type>(200 * SDL_sinf(rads_))}, 
                    SDL_MapRGBA(s.get_format(), 255, 0, 0, 255), 0xff00ff00);
            // s.line_s( point{s.get_cw(), s.get_ch()}, 
            //             point{s.get_cw() + static_cast<int_type>(s.get_w() * SDL_cosf(rads_)), s.get_ch() + static_cast<int_type>(s.get_w() * SDL_sinf(rads_))}, 
            //         SDL_MapRGBA(s.get_format(), 255, 0, 0, 255));
        }
    };
}



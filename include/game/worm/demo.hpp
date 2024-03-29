#pragma once
#include <cstdlib>
#include <SDL.h>
#include "game/engine/video.hpp"
#include "game/engine/surface.hpp"
#include "game/gfx/pixel.hpp"
#include "game/gfx/line.hpp"
#include "game/gfx/rect.hpp"
#include "game/gfx/circle.hpp"
#include "game/gfx/palette.hpp"


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
            g80::game::gfx::palette pal(&s);
            g80::game::gfx::rect rect(&s);
            g80::game::gfx::circle circle(&s);

            auto one_shade = pal.get_palette_gradient({{0, 0}, {100, 255}, {199, SDL_MapRGBA(s.get_handle()->format, 255, 0, 255, 255)}});
            auto multi_shade = pal.get_palette_gradient({
                {0, SDL_MapRGBA(s.get_handle()->format, 255, 0, 0, 255)}, 
                {50, SDL_MapRGBA(s.get_handle()->format, 0, 255, 0, 255)}, 
                {100, SDL_MapRGBA(s.get_handle()->format, 0, 0, 255, 255)}, 
                {150, SDL_MapRGBA(s.get_handle()->format, 255, 0, 255, 255)}, 
                {200, SDL_MapRGBA(s.get_handle()->format, 0, 255, 255, 255)}, 
                {255, SDL_MapRGBA(s.get_handle()->format, 255, 255, 255, 255)},});

            SDL_FillRect(s.get_handle(), NULL, 0); 

            //line.draw(point{50,50}, point{1000,700}, multi_shade.value(), 0, 255);

            // rect.draw_s(point{300, 270}, 64, 128, SDL_MapRGBA(s.get_handle()->format, 255, 0, 255, 255), 0x00ff00ff);
            // rect.draw_s(point{-32, -64}, 64, 128, SDL_MapRGBA(s.get_handle()->format, 255, 0, 255, 255), 0x00ff00ff);


            // rect.draw_s(600, 600, 1, 0, SDL_MapRGBA(s.get_handle()->format, 255, 255, 0, 255));

            // rect.draw_s(500, 500, 100, 100, SDL_MapRGBA(s.get_handle()->format, 255, 0, 0, 255));
//            rect.draw_s(point{-50, -50}, 100, 100, one_shade.value(), 0, 199);
            // rect.draw_s(point{-50, s.get_h() - 50}, 100, 100, one_shade.value(), 0, 199);
            // rect.draw_s(point{s.get_w() - 50, -50}, 100, 100, one_shade.value(), 0, 199);
            // rect.draw_s(point{s.get_w() - 50, s.get_h() - 50}, 100, 100, one_shade.value(), 0, 199);
            // rect.draw_s(point{-50, -50}, 3000, 1000, one_shade.value(), 0, 199);
            // rect.draw_s(point{-50, 300}, 3000, 100, one_shade.value(), 0, 199);
            // rect.draw_s(point{700, 850}, -200, -1000, one_shade.value(), 0, 199);


//            line.draw(point{50, s.get_h() - 1}, point{300, s.get_h() - 1}, SDL_MapRGBA(s.get_handle()->format, 255, 0, 0, 255));

            // for(size_t i{0}; i< 1000; ++i) {
            //     pixel.draw(point{rand() % s.get_handle()->w,
            //             rand() % s.get_handle()->h},
            //             SDL_MapRGBA(s.get_handle()->format, 255, 0, 0, 255));
            // }
            rads_ += 0.005;
            line.draw_s( point{s.get_cw() + static_cast<int_type>(1200 * SDL_cosf(rads_)), s.get_ch() + static_cast<int_type>(1200 * SDL_sinf(rads_))}, 
                    point{s.get_cw(), s.get_ch()},
                    multi_shade.value(), 0, 255);
            
            // rect.draw_s(point{-50, -50}, 100, 100, multi_shade.value(), 0, 255);
            
            // line.draw( point{s.get_cw(), s.get_ch()}, 
            //             point{s.get_cw() + static_cast<int_type>(200 * SDL_cosf(rads_)), s.get_ch() + static_cast<int_type>(200 * SDL_sinf(rads_))}, 
            //         SDL_MapRGBA(s.get_format(), 255, 0, 0, 255), 0x0000fff);
            
            // s.line_s( point{s.get_cw(), s.get_ch()}, 
            //             point{s.get_cw() + static_cast<int_type>(s.get_w() * SDL_cosf(rads_)), s.get_ch() + static_cast<int_type>(s.get_w() * SDL_sinf(rads_))}, 
            //         SDL_MapRGBA(s.get_format(), 255, 0, 0, 255));

            // line.draw(point{100, s.get_ch()}, point{s.get_cw() + 500, s.get_ch()}, SDL_MapRGBA(s.get_handle()->format, 255, 255, 255, 255));
            // line.draw(point{s.get_cw(), 50}, point{s.get_cw(), 600}, SDL_MapRGBA(s.get_handle()->format, 255, 255, 255, 255));
            //circle.draw(point{s.get_cw(), s.get_ch()}, 200, SDL_MapRGBA(s.get_handle()->format, 255, 0, 255, 255), 0x0000fff); // 0x00f3000A

            circle.draw(point{s.get_cw(), s.get_ch()}, 200, multi_shade.value(), 0, 255); // 0x00f3000A
            // for(auto &v : multi_shade.value()) {
            //     std::cout << v << " ";
            // }
            // std::cout << "\n";
        }
    };
}



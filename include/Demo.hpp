#ifndef _DEMO_HPP_
#define _DEMO_HPP_

#include <cstdlib>

#include "Video.hpp"

namespace g80 {
    class Demo : public Video {
    public:
        Demo();

        auto preprocess_states() -> bool;
        auto update_states() -> bool;

        /*
        virtual auto create_window(const VideoConfig &video_config) -> bool;
        virtual auto destroy_window() -> void;
        virtual auto preprocess_states() -> bool;
        virtual auto run() -> bool;
        virtual auto capture_events() -> bool;
        virtual auto update_states() -> bool;
        virtual auto update_window_surface() -> bool;
        */

    private:
    };

    Demo::Demo() : Video() {

    }

    auto Demo::preprocess_states() -> bool {
        return true;
    }

    auto Demo::update_states() -> bool {

        SDL_FillRect(surface_, NULL, 0);
        Palette pal;
        pal.add_gradients(surface_->format, 40, 
            {
                {0, SDL_MapRGBA(surface_->format, 255, 255, 255, 255)},
                {10, SDL_MapRGBA(surface_->format, 255, 255, 0, 255)},
                {20, SDL_MapRGBA(surface_->format, 255, 100, 0, 255)},
                {30, SDL_MapRGBA(surface_->format, 255, 0, 0, 255)},
                {40, SDL_MapRGBA(surface_->format, 255, 0, 255, 255)},});
        
        // for (int i = 0; i < surface_->w - 1; ++i) {
        //     int h =  100 + rand() % 500;
        //     line_lite({i, surface_->h - 1}, {i, surface_->h - h}, pal, 0, 39);

        // }
        
        line({-1000, surface_->h / 2}, {+3000, surface_->h / 2}, pal, 0, 39);
        //line({-1000, surface_->h / 2}, {+1000, surface_->h / 2}, SDL_MapRGBA(surface_->format, 255, 0, 0, 255));

        return true;
    }
}

#endif 
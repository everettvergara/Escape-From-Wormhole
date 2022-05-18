#ifndef _CIRCLEDEMO_HPP_
#define _CIRCLEDEMO_HPP_

#include <cstdlib>

#include "Video.hpp"
#include "Motion/LineWithAccelMotion.hpp"
#include "Motion/LineMotion.hpp"
#include "TrigCache.hpp"

namespace g80 {
    class CircleDemo : public Video {
    public:
        CircleDemo();

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

       auto capture_events() -> bool;

    private:

        Point<Sint32> mouse_;
        Sint32 r_ = 1, rn_ = 1;
    };

    CircleDemo::CircleDemo() : Video() {

    }

    auto CircleDemo::preprocess_states() -> bool {
        return true;
    }

    auto CircleDemo::update_states() -> bool {
        Palette pal;
        // TODO: Palette, size should be automatic based on gradients
        // todo: FIX BUG, size SHould be based on the last index + 1 
        pal.add_gradients(surface_->format,
            {
                {0, SDL_MapRGBA(surface_->format, 255, 0, 0, 255)},
                {38, SDL_MapRGBA(surface_->format, 0, 255, 0, 255)},
                {75, SDL_MapRGBA(surface_->format, 0, 0, 255, 255)},
                {112, SDL_MapRGBA(surface_->format, 255, 255, 0, 255)},
                {150, SDL_MapRGBA(surface_->format, 255, 0, 255, 255)},
                {188, SDL_MapRGBA(surface_->format, 255, 255, 0, 255)},

                {226, SDL_MapRGBA(surface_->format, 0, 0, 255, 255)},                
                {264, SDL_MapRGBA(surface_->format, 0, 255, 0, 255)},    
                {300, SDL_MapRGBA(surface_->format, 255, 0, 0, 255)},
                
                });

        // circle({1280/2, 720/2}, 200, SDL_MapRGBA(surface_->format, 255, 0, 0, 255));
        circle(mouse_, r_, pal, 0, 299);
        return true;
    }

    auto CircleDemo::capture_events() -> bool {
        SDL_Event e;
        while(SDL_PollEvent(&e)) {
            if(e.type == SDL_QUIT)
                is_running_ = false;

            else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_ESCAPE)
                    is_running_ = false;
            }
            
            else if (e.type == SDL_MOUSEMOTION) {
                mouse_.x = e.motion.x;
                mouse_.y = e.motion.y;
                if (r_ >100 || r_ <1) rn_ *= -1;
                r_ += rn_;
                
            }
        }
        return true;
    }
}

#endif 
#ifndef _VIDEODEMO_HPP_
#define _VIDEODEMO_HPP_

#include <cstdlib>

#include "Video.hpp"
#include "Motion/LineWithAccelMotion.hpp"
#include "Motion/LineMotion.hpp"
#include "TrigCache.hpp"

namespace g80 {
    class VideoDemo : public Video {
    public:
        VideoDemo();

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
    };

    VideoDemo::VideoDemo() : Video() {

    }

    auto VideoDemo::preprocess_states() -> bool {
        return true;
    }

    auto VideoDemo::update_states() -> bool {

        circle(mouse_, 200, SDL_MapRGBA(surface_->format, 255, 0, 0, 255));
        return true;
    }

    auto VideoDemo::capture_events() -> bool {
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
            }
        }
        return true;
    }
}

#endif 
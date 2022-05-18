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

    private:


    };

    VideoDemo::VideoDemo() : Video() {

    }

    auto VideoDemo::preprocess_states() -> bool {
        return true;
    }

    auto VideoDemo::update_states() -> bool {

        circle_lite({1280/2, 720/2}, 100, SDL_MapRGBA(surface_->format, 255, 0, 0, 255));
        return true;
    }
}

#endif 
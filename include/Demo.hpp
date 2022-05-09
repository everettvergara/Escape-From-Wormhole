#ifndef _DEMO_HPP_
#define _DEMO_HPP_

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
        // line({200, -100}, {1280, 350}, SDL_MapRGBA(surface_->format, 255, 0, 0, 255));
        return true;
    }
}

#endif 
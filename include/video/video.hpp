#pragma once

#include "sys/common.hpp"
#include "base_point.hpp"
#include "config.hpp"

namespace g80::video {

    using point = base_point<g80::sys::int_type>;
    


    class video {
    
    public:
        static bool is_init_;
        static inline auto is_init() -> bool {return is_init_;}
        static auto init() -> bool {if(!is_init_) is_init_ = SDL_VideoInit(NULL) ? true : false; return is_init_;}
        static auto quit() -> void {SDL_VideoQuit();}

    public:
        config config_;
        video(config &&c) : config_{std::move(c)} {};
    };

    bool video::is_init_{false};
}
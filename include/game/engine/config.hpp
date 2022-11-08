#pragma once

#include <SDL.h>
#include <string>

namespace g80::game::engine {

    class config {
    
    private:
        std::string title_;
        int         x_, y_, w_, h_;
        Uint32      flags_;
        Uint16      FPS_;
        Uint16      MSPF_;

    public:
        config( std::string title, 
                int x = SDL_WINDOWPOS_CENTERED, 
                int y = SDL_WINDOWPOS_CENTERED, 
                int w = 1280, 
                int h = 720, 
                Uint32 flags = SDL_WINDOW_SHOWN, 
                Uint16 FPS = 60) :
                title_{std::move(title)}, 
                x_{x}, y_{y}, w_{w}, h_{h},
                flags_{flags}, FPS_{FPS}, 
                MSPF_{static_cast<Uint16>(static_cast<Uint16>(1000) / FPS)} {
        }

        inline auto get_title() const -> const std::string & {return title_;}
        inline auto get_x() const -> int {return x_;}
        inline auto get_y() const -> int {return y_;}
        inline auto get_w() const -> int {return w_;}
        inline auto get_h() const -> int {return h_;}
        inline auto get_flags() const -> Uint32 {return flags_;}
        inline auto get_FPS() const -> Uint16 {return FPS_;}
        inline auto get_MSPF() const -> Uint16 {return MSPF_;}
    };


}
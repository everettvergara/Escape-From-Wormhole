#pragma once

#include <iostream>
#include <vector>
#include <initializer_list>
#include <tuple>
#include <optional>
#include "game/engine/surface.hpp" 

namespace g80::game::gfx {

    using namespace g80::game::engine;

    class palette {

    private:

        surface *s_;
        

    public:

        palette(surface *s) : s_(s) {
        }

        auto get_gradient(std::initializer_list<std::tuple<Uint32, Uint32>> rgba_colors) -> std::optional<std::vector<Uint32>> {
            if(rgba_colors.size() < 4) return {};
            if(rgba_colors.size() & 1) return {};
            
            std::vector<Uint32> gradients;

            auto last = rgba_colors.end() - 1;
            auto N = std::get<0>(*last);

            gradients.reserve(N);

            Uint8 r1, g1, b1, a1;
            Uint8 r2, g2, b2, a2;

            // fp_type percent = static_cast<fp_type>(rgba_colors[0]);
            // Uint32 rgba_from = static_cast<Uint32>(rgba_colors[1]);
            // SDL_GetRGBA(rgba_from, s_->get_format(), &r1, &g1, &b1, &a1);

            // for(size_t i{2}; i < n; i += 2) {

            // }

            return gradients;
        }
        
    };
}
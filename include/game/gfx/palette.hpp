#pragma once

#include <iostream>
#include <vector>
#include <initializer_list>
#include <tuple>
#include <optional>
#include "game/engine/surface.hpp" 

namespace eg::vidfeo {

    using namespace g80::game::engine;

    using palette_gradient = std::vector<Uint32>;

    class palette {

    private:

        surface *s_;
        
    public:

        palette(surface *s) : s_(s) {
        }

        auto get_palette_gradient(std::initializer_list<std::tuple<Uint32, Uint32>> rgba_colors) -> std::optional<palette_gradient> {
            if(rgba_colors.size() < 2) return {};
            
            std::vector<Uint32> gradients;

            auto last = rgba_colors.end() - 1;
            auto N = std::get<0>(*last) - 1;

            gradients.reserve(N + 1);

            auto t = rgba_colors.begin();
            auto i_from = std::get<0>(*t);
            auto rgba_color_from = std::get<1>(*t);
            Uint8 r1, g1, b1, a1;
            Uint8 r2, g2, b2, a2;            
            SDL_GetRGBA(rgba_color_from, s_->get_format(), &r1, &g1, &b1, &a1);

            while(++t != rgba_colors.end()) {
                auto i_to = std::get<0>(*t);
                auto rgba_color_to = std::get<1>(*t);
                SDL_GetRGBA(rgba_color_to, s_->get_format(), &r2, &g2, &b2, &a2);

                fp_type inc = 1.0f / (i_to - i_from);
                fp_type perc = 0.0f;
                for (Uint32 i = i_from; i != i_to; ++i) {
                    gradients.emplace_back(SDL_MapRGBA(
                        s_->get_format(), 
                        r1 + (r2 - r1) * perc,
                        g1 + (g2 - g1) * perc,
                        b1 + (b2 - b1) * perc,
                        a1 + (a2 - a1) * perc));
                    perc += inc;
                }

                i_from = i_to;
                r1 = r2; g1 = g2; b1 = b2; a1 = a2;
            }

            gradients.emplace_back(SDL_MapRGBA(s_->get_format(), r1, g1, b1, a1));
            return gradients;
        }
        
    };


}
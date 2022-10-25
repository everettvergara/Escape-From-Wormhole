#ifndef _PALETTE_HPP_
#define _PALETTE_HPP_

#include <vector>
#include <initializer_list>
#include <tuple>
#include "EmptyAllocator.hpp"
#include "Color.hpp"

namespace g80 {

    using RGBAColors = std::vector<RGBAColor, EmptyAllocator<RGBAColor>>;
    class Palette {
    public:

        Palette() {};
        Palette(const Uint32 n) : colors_(n) {
        }
        
        auto operator[](const int i) const -> const RGBAColor & {
            return colors_[i];
        };
        
        auto operator[](const int i) -> RGBAColor & {
            return colors_[i];
        };

        auto add_gradients(SDL_PixelFormat *format, std::initializer_list<std::tuple<Uint32, RGBAColor>> rgba_colors) -> void {
            if (colors_.size() > 0) return;
            if (rgba_colors.size() < 2) return;

            auto last = rgba_colors.end() - 1;
            auto n = std::get<0>(*last);
            colors_.reserve(n + 1);

            Color r1, g1, b1, a1;
            Color r2, g2, b2, a2;

            auto t = rgba_colors.begin();
            auto i_from = std::get<0>(*t);
            auto rgba_color_from = std::get<1>(*t);
            SDL_GetRGBA(rgba_color_from, format, &r1, &g1, &b1, &a1);

            while(++t != rgba_colors.end()) {
                auto i_to = std::get<0>(*t);
                auto rgba_color_to = std::get<1>(*t);
                SDL_GetRGBA(rgba_color_to, format, &r2, &g2, &b2, &a2);

                float inc = 1.0f / (i_to - i_from);
                float perc = 0.0f;
                for (Uint32 i = i_from; i != i_to; ++i) {
                    colors_.emplace_back(SDL_MapRGBA(
                        format, 
                        r1 + (r2 - r1) * perc,
                        g1 + (g2 - g1) * perc,
                        b1 + (b2 - b1) * perc,
                        a1 + (a2 - a1) * perc));
                    perc += inc;
                }

                i_from = i_to;
                r1 = r2; g1 = g2; b1 = b2; a1 = a2;
            }

            colors_.emplace_back(SDL_MapRGBA(format, r1, g1, b1, a1));
        }

    private:
        RGBAColors colors_;
    };
}

#endif 
#ifndef _GFX_HPP_
#define _GFX_HPP_

#include "Commons.hpp"

namespace g80 {

    class Gfx {
    public:
        static auto pset(SDL_Surface *surface, const Point &p, Color c) -> void {
            Uint32 *cp = static_cast<Uint32 *>(surface->pixels) + p.y * surface->w + p.x;
            *cp = c;            
        }

        static auto line(SDL_Surface *surface, const Point &p1, const Point &p2, Color c) -> void {
            Sint32 dx = p2.x - p1.x;
            Sint32 dy = p2.y - p1.y;
            Sint32 sdx = dx < 0 ? -1 : 1;
            Sint32 sdy = dy < 0 ? -surface->w : surface->w;
            Sint32 adx = dx < 0 ? dx * -1 : dx;
            Sint32 ady = dy < 0 ? dy * -1 : dy;
            Sint32 *cp = static_cast<Sint32 *>(surface->pixels) + p1.y * surface->w + p1.x;
            Sint32 *min_point = static_cast<Sint32 *>(surface->pixels);
            Sint32 *max_point = static_cast<Sint32 *>(surface->pixels) + surface->h * surface->w;

            if (adx >= ady) {    
                for (Sint32 i = 0, t = ady; i <= adx; ++i, t += ady) {
                    if (cp >= min_point && cp < max_point) *cp = c;
                    if (t >= adx) {
                        cp += sdy;
                        t -= adx;
                    }
                    cp +=sdx;
                }
            } else {
                for (Sint32 i = 0, t = adx; i <= ady; ++i, t += adx) {
                    if (cp >= min_point && cp < max_point) *cp = c;
                    if (t >= ady) {
                        cp += sdx;
                        t -= ady;
                    }
                    cp += sdy;
                }
            }
        }
    };
}

#endif
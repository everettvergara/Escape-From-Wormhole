#ifndef _GFX_HPP_
#define _GFX_HPP_

#include "Commons.hpp"

namespace g80 {

    class Gfx {
    public:
        static auto pset(SDL_Surface *surface, const Point &p, RGBAColor c) -> void {
            Uint32 *cp = static_cast<Uint32 *>(surface->pixels) + p.y * surface->w + p.x;
            *cp = c;            
        }

        static auto line(SDL_Surface *surface, const Point &p1, const Point &p2, RGBAColor c) -> void {
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

        static auto circle(SDL_Surface *surface, const Point &p, const Dim r, const RGBAColor c) {
            
            Uint32 *center = static_cast<Uint32 *>(surface->pixels) + p.y * surface->w + p.x;
            Uint32 *min = static_cast<Uint32 *>(surface->pixels);
            Uint32 *max = static_cast<Uint32 *>(surface->pixels) + surface->w * surface->h;
            
            Dim x = r;
            Dim y = 0;
            Dim bx = x * surface->w;
            Dim by = y * surface->w;

            Dim dx = 1 - (r << 1);
            Dim dy = 1;
            Dim re = 0;


            while (x >= y)
            {
                if ((center + y - bx) >= min && (center + y - bx) < max) *(center + x - by) = c;
                if ((center + y - bx) >= min && (center + y - bx) < max) *(center + y - bx) = c;
                if ((center - y - bx) >= min && (center - y - bx) < max) *(center - y - bx) = c;
                if ((center - x - by) >= min && (center - x - by) < max) *(center - x - by) = c;
                if ((center + x + by) >= min && (center + x + by) < max) *(center + x + by) = c;
                if ((center + y + bx) >= min && (center + y + bx) < max) *(center + y + bx) = c;
                if ((center - y + bx) >= min && (center - y + bx) < max) *(center - y + bx) = c;
                if ((center - x + by) >= min && (center - x + by) < max) *(center - x + by) = c;

                ++y;
                re += dy;
                dy += 2;
                if ((re << 1) + dx > 0)
                {
                    --x;
                    bx -= surface->w;
                    re += dx;
                    dx += 2;
                }
                by += surface->w;
            }
        }


    };
}

#endif
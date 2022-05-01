#ifndef _GFX_HPP_
#define _GFX_HPP_

#include <cstdint>
#include <SDL.h>


namespace g80 {

    struct Point {
        Sint32 x;
        Sint32 y;
    };

    using Color = Uint32;

    class Gfx {
    public:
        static auto bezier2(SDL_Surface *surface, const Point &p1, const Point &p2, const Point &p3, Color c, Sint32 max_steps = 50) {

            // line(surface, p1, p2, c);
            // line(surface, p2, p3, c);

            // return;
            max_steps--;
            Sint32 dx1 = p2.x - p1.x;
            Sint32 dy1 = p2.y - p1.y;
            Sint32 dx2 = p3.x - p2.x;
            Sint32 dy2 = p3.y - p2.y;
            
            Point cp1 = p1;
            Point cp2 = p2;
            Point prev_bp = p1;

            for (Sint32 s = 0; s <= max_steps; ++s) {
                cp1.x = p1.x + dx1 * s / max_steps;
                cp1.y = p1.y + dy1 * s / max_steps;
                cp2.x = p2.x + dx2 * s / max_steps;
                cp2.y = p2.y + dy2 * s / max_steps;

                Sint32 dcx1 = cp2.x - cp1.x;
                Sint32 dcy1 = cp2.y - cp1.y;
                Point bp;
                bp.x = cp1.x + dcx1 * s / max_steps;
                bp.y = cp1.y + dcy1 * s / max_steps;

                //if (s > max_steps / 3) {
                    Uint8 r, g, b, a;
                    SDL_GetRGBA(c, surface->format, &r, &g, &b, &a);
                    r = 1.0f * r * s / max_steps;
                    //cif (s < max_steps / 2) {
                    g = .5f * g * s / max_steps;
                    b = .5f * b * s / max_steps;
                    // } else {
                    //     g = 0; b = 0;
                    // }
                    Uint32 color = SDL_MapRGBA(surface->format, r, g, b, 255);
                    line(surface, prev_bp, bp, color);
                    pset(surface, cp1, SDL_MapRGBA(surface->format, 255, 0, 0, 255));
                    pset(surface, cp2, SDL_MapRGBA(surface->format, 0, 255, 0, 255));
                    pset(surface, bp, SDL_MapRGBA(surface->format, 0, 0, 255, 255));
                // } 
                prev_bp = bp;
            }
        }

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
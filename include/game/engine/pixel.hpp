#pragma once

#include "game/engine/surface.hpp" 

namespace g80::game::engine {

    class pixel : public surface {
    public:
        inline auto draw_pixel(const int_type x, const int_type y, const Uint32 rgba) -> void {
            *((static_cast<Uint32 *>(get_s()->pixels) + x) + (y * get_s()->w)) = rgba;
        }    
        inline auto draw_pixel(const point &p, const Uint32 rgba) -> void {
            *((static_cast<Uint32 *>(get_s()->pixels) + p.x) + (p.y * get_s()->w)) = rgba;
        }
        auto draw_pixel_s(const int_type x, const int_type y, const Uint32 rgba) -> void {
            if(!is_point_within_bounds(x, y)) [[unlikely]] return;
            draw_pixel(x, y, rgba);
        }    
        auto draw_pixel_s(const point &p, const Uint32 rgba) -> void {
            if(!is_point_within_bounds(p)) [[unlikely]] return;
            draw_pixel(p, rgba);
        }
    };
}
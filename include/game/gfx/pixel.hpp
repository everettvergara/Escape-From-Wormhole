#pragma once

#include "game/engine/surface.hpp" 

namespace g80::game::gfx {

    using namespace g80::game::engine;
    
    class pixel {
    
    private:
        surface *s_;

    public:
        pixel(surface *s);
        auto draw(const int_type x, const int_type y, const Uint32 rgba) -> void;
        auto draw(const point &p, const Uint32 rgba) -> void;
        auto draw(Uint32 *p, const Uint32 rgba) -> void;
        auto draw_s(const int_type x, const int_type y, const Uint32 rgba) -> void;
        auto draw_s(const point &p, const Uint32 rgba) -> void;
    };

    pixel::pixel(surface *s) : s_(s) {
    }

    inline auto pixel::draw(const int_type x, const int_type y, const Uint32 rgba) -> void {
        *((static_cast<Uint32 *>(s_->get_handle()->pixels) + x) + (y * s_->get_handle()->w)) = rgba;
    }

    inline auto pixel::draw(const point &p, const Uint32 rgba) -> void {
        *((static_cast<Uint32 *>(s_->get_handle()->pixels) + p.x) + (p.y * s_->get_handle()->w)) = rgba;
    }

    inline auto pixel::draw(Uint32 *p, const Uint32 rgba) -> void {
        *p = rgba;
    }

    auto pixel::draw_s(const int_type x, const int_type y, const Uint32 rgba) -> void {
        if(!s_->is_point_within_bounds(x, y)) return;
        draw(x, y, rgba);
    }

    auto pixel::draw_s(const point &p, const Uint32 rgba) -> void {
        if(!s_->is_point_within_bounds(p)) return;
        draw(p, rgba);
    }
}
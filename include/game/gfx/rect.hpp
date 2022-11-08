#pragma once

#include "game/engine/surface.hpp" 

namespace g80::game::gfx {

    using namespace g80::game::engine;

    class rect {

    private:

        surface *s_;

    public:

        rect(surface *s) : s_(s) {
        }

        inline auto draw(const int_type x, const int_type y, const int_type w, const int_type h, const Uint32 rgba) -> void {
            // *((static_cast<Uint32 *>(s_->get_handle()->pixels) + x) + (y * s_->get_handle()->w)) = rgba;
        }    
    };
}
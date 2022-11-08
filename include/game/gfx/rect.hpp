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
            auto *pixel_top = (static_cast<Uint32 *>(s_->get_handle()->pixels) + x) + (y * s_->get_handle()->w);
            auto *pixel_bottom = (static_cast<Uint32 *>(s_->get_handle()->pixels) + x) + ((y + h - 1) * s_->get_handle()->w);
            auto *pixel_left = pixel_top + s_->get_handle()->w;
            auto *pixel_right = pixel_top + s_->get_handle()->w + w - 1;

            for(int i{0}; i < w; ++i) {
                *pixel_top++ = rgba;
                *pixel_bottom++ = rgba;
            }

            for(int i{0}; i < h - 2; ++i) {
                *pixel_left = rgba;
                *pixel_right = rgba;
                pixel_left += s_->get_handle()->w;
                pixel_right += s_->get_handle()->w;
            }
        }    

        inline auto draw(const int_type x, const int_type y, const int_type w, const int_type h, const Uint32 rgba, const Uint32 mask) -> void {
            auto *pixel_top = (static_cast<Uint32 *>(s_->get_handle()->pixels) + x) + (y * s_->get_handle()->w);
            auto *pixel_bottom = (static_cast<Uint32 *>(s_->get_handle()->pixels) + x) + ((y + h - 1) * s_->get_handle()->w);
            auto *pixel_left = pixel_top + s_->get_handle()->w;
            auto *pixel_right = pixel_top + s_->get_handle()->w + w - 1;

            auto tmask = mask;
            for(int i{0}; i < w; ++i) {
                *pixel_top = tmask & 1 ? rgba : *pixel_top;
                *pixel_bottom = tmask & 1 ? rgba : *pixel_bottom;
                ++pixel_top;
                ++pixel_bottom;
                tmask >>= 1;
                tmask = !tmask ? mask : tmask;
            }

            tmask = mask;
            for(int i{0}; i < h - 2; ++i) {
                *pixel_left = tmask & 1 ? rgba : *pixel_left;
                *pixel_right = tmask & 1 ? rgba : *pixel_right;
                pixel_left += s_->get_handle()->w;
                pixel_right += s_->get_handle()->w;
                tmask >>= 1;
                tmask = !tmask ? mask : tmask;
            }
        }    

    };
}
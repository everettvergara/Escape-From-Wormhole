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
            auto *pixel_top     = (static_cast<Uint32 *>(s_->get_handle()->pixels) + x) + (y * s_->get_handle()->w);
            auto *pixel_bottom  = h > 0 ? pixel_top + ((h - 1) * s_->get_handle()->w) :
                                        pixel_top + ((h + 1) * s_->get_handle()->w);
            auto *pixel_left    = w > 0 ? pixel_top + s_->get_handle()->w : pixel_top - s_->get_handle()->w;
            auto *pixel_right   = w > 0 ? pixel_top + s_->get_handle()->w + w - 1 : (pixel_top - s_->get_handle()->w) + (w + 1);

            auto aw = w > 0 ? w : -w;
            auto iw = w > 0 ? 1 : -1;
            for(int i{0}; i < aw; ++i) {
                *pixel_top = rgba;
                *pixel_bottom = rgba;
                pixel_top += iw;
                pixel_bottom += iw;
            }

            auto ah = h > 0 ? h : -h;
            auto ih = h > 0 ? s_->get_handle()->w : -s_->get_handle()->w;
            for(int i{0}; i < ah - 2; ++i) {
                *pixel_left = rgba;
                *pixel_right = rgba;
                pixel_left += ih;
                pixel_right += ih;
            }
        }    

        inline auto draw(const int_type x, const int_type y, const int_type w, const int_type h, const Uint32 rgba, const Uint32 mask) -> void {
            auto *pixel_top     = (static_cast<Uint32 *>(s_->get_handle()->pixels) + x) + (y * s_->get_handle()->w);
            auto *pixel_bottom  = h > 0 ? pixel_top + ((h - 1) * s_->get_handle()->w) :
                                        pixel_top + ((h + 1) * s_->get_handle()->w);
            auto *pixel_left    = w > 0 ? pixel_top + s_->get_handle()->w : pixel_top - s_->get_handle()->w;
            auto *pixel_right   = w > 0 ? pixel_top + s_->get_handle()->w + w - 1 : (pixel_top - s_->get_handle()->w) + (w + 1);

            auto tmask = mask;
            auto aw = w > 0 ? w : -w;
            auto iw = w > 0 ? 1 : -1;
            for(int i{0}; i < aw; ++i) {
                *pixel_top = tmask & 1 ? rgba : *pixel_top;
                *pixel_bottom = tmask & 1 ? rgba : *pixel_bottom;
                pixel_top += iw;
                pixel_bottom += iw;
                tmask >>= 1;
                tmask = !tmask ? mask : tmask;
            }

            tmask = mask;
            auto ah = h > 0 ? h : -h;
            auto ih = h > 0 ? s_->get_handle()->w : -s_->get_handle()->w;
            for(int i{0}; i < ah - 2; ++i) {
                *pixel_left = tmask & 1 ? rgba : *pixel_left;
                *pixel_right = tmask & 1 ? rgba : *pixel_right;
                pixel_left += ih;
                pixel_right += ih;
                tmask >>= 1;
                tmask = !tmask ? mask : tmask;
            }
        }    

        inline auto draw_s(const int_type x, const int_type y, const int_type w, const int_type h, const Uint32 rgba) -> void {
            int_type sx, sy, mw, mh;

            // Starting X
            if (w >= 0) {
                if (0 > x && 0 <= x + w - 1) {  // Remember that we're comparing x2, so we need to deduct -1
                    sx = 0;
                    mw = w + x;

                } else if (x + w - 1 < 0 || x >= s_->get_handle()->w) {
                    return;

                } else {
                    sx = x;
                    mw = w;
                }

            } else {
                if (x >= s_->get_handle()->w && x + w + 1 < s_->get_handle()->w) { 
                    sx = s_->get_wb();
                    mw = x - s_->get_wb() + w;
                }
            }

            // Starting Y
            if (0 > y && 0 <= y + h - 1) {
                sy = 0;
                
                mh = h + y;

            } else if (y + h - 1 < 0 || y >= s_->get_handle()->h) {
                return;
                
            } else {
                sy = y;
                mh = h;
            }

            // Modified Width
            if (sx + mw >= s_->get_handle()->w) mw -= sx + mw - s_->get_handle()->w;

            // Modified Height
            if (sy + mh >= s_->get_handle()->h) mh -= sy + mh - s_->get_handle()->h;


            auto *upper_left = (static_cast<Uint32 *>(s_->get_handle()->pixels) + sx) + (sy * s_->get_handle()->w);
            
            // Draw Top
            if(y == sy) [[likely]] {
                auto *pixel_top = upper_left;
                for (int i{0}; i < mw; ++i) *pixel_top++ = rgba;
            }
            
            // Draw Bottom
            if (y + h - 1 < s_->get_handle()->h) [[likely]] {
                auto *pixel_bottom = upper_left + ((mh - 1) * s_->get_handle()->w);
                for (int i{0}; i < mw; ++i) *pixel_bottom++ = rgba;
            }
            
            // Draw Left
            if (x == sx) [[likely]] {
                auto *pixel_left = upper_left + (y == sy ? s_->get_handle()->w : 0);
                auto d = (y + h - 1 < s_->get_handle()->h ? 2 : 1) + (y == sy ? 0 : -1);
                for (int i{0}; i < mh - d; ++i) {
                    *pixel_left = rgba;
                    pixel_left += s_->get_handle()->w;
                }
            }

            // Draw Right
            if (x + w - 1 < s_->get_handle()->w) [[likely]] {
                auto *pixel_right = upper_left + (y == sy ? s_->get_handle()->w : 0) + mw - 1;
                auto d = (y + h - 1 < s_->get_handle()->h ? 2 : 1) + (y == sy ? 0 : -1);
                for (int i{0}; i < mh - d; ++i) {
                    *pixel_right = rgba;
                    pixel_right += s_->get_handle()->w;
                }                
            }            
        }    

        // inline auto draw_s(const int_type x, const int_type y, const int_type w, const int_type h, const Uint32 rgba) -> void {

        //     int_type sx, sy, mw, mh;

        //     // Starting X
        //     if (0 > x && 0 <= x + w - 1) {  // Remember that we're comparing x2, so we need to deduct -1
        //         sx = 0;
        //         mw = w + x;

        //     } else if (x + w - 1 < 0 || x >= s_->get_handle()->w) {
        //         return;

        //     } else {
        //         sx = x;
        //         mw = w;
        //     }

        //     // Starting Y
        //     if (0 > y && 0 <= y + h - 1) {
        //         sy = 0;
        //         mh = h + y;

        //     } else if (y + h - 1 < 0 || y >= s_->get_handle()->h) {
        //         return;
                
        //     } else {
        //         sy = y;
        //         mh = h;
        //     }

        //     // Modified Width
        //     if (sx + mw >= s_->get_handle()->w) mw -= sx + mw - s_->get_handle()->w;

        //     // Modified Height
        //     if (sy + mh >= s_->get_handle()->h) mh -= sy + mh - s_->get_handle()->h;


        //     auto *upper_left = (static_cast<Uint32 *>(s_->get_handle()->pixels) + sx) + (sy * s_->get_handle()->w);
            
        //     // Draw Top
        //     if(y == sy) {
        //         auto *pixel_top = upper_left;
        //         for (int i{0}; i < mw; ++i) *pixel_top++ = rgba;
        //     }
            
        //     // Draw Bottom
        //     if (y + h - 1 < s_->get_handle()->h) {
        //         auto *pixel_bottom = upper_left + ((mh - 1) * s_->get_handle()->w);
        //         for (int i{0}; i < mw; ++i) *pixel_bottom++ = rgba;
        //     }
            
        //     // Draw Left
        //     if (x == sx) {
        //         auto *pixel_left = upper_left + (y == sy ? s_->get_handle()->w : 0);
        //         auto d = (y + h - 1 < s_->get_handle()->h ? 2 : 1) + (y == sy ? 0 : -1);
        //         for (int i{0}; i < mh - d; ++i) {
        //             *pixel_left = rgba;
        //             pixel_left += s_->get_handle()->w;
        //         }
        //     }

        //     // Draw Right
        //     if (x + w - 1 < s_->get_handle()->w) {
        //         auto *pixel_right = upper_left + (y == sy ? s_->get_handle()->w : 0) + mw - 1;
        //         auto d = (y + h - 1 < s_->get_handle()->h ? 2 : 1) + (y == sy ? 0 : -1);
        //         for (int i{0}; i < mh - d; ++i) {
        //             *pixel_right = rgba;
        //             pixel_right += s_->get_handle()->w;
        //         }                
        //     }            
        // }            
    };
}
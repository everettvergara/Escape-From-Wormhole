#pragma once

#include "game/engine/surface.hpp" 
#include "game/gfx/palette.hpp"


namespace g80::game::gfx {

    using namespace g80::game::engine;

    class rect {

    private:

        surface *s_;

    public:

        rect(surface *s) : s_(s) {
        }

        inline auto draw(const point &p, const int_type w, const int_type h, const Uint32 rgba) -> void {
            auto *pixel_top     = (static_cast<Uint32 *>(s_->get_handle()->pixels) + p.x) + (p.y * s_->get_handle()->w);
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

        inline auto draw(const point &p, const int_type w, const int_type h, const Uint32 rgba, const Uint32 mask) -> void {
            auto *pixel_top     = (static_cast<Uint32 *>(s_->get_handle()->pixels) + p.x) + (p.y * s_->get_handle()->w);
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

        inline auto draw(const point &p, const int_type w, const int_type h, const palette_gradient &pal, const int ix_from, const int ix_to) -> void {
            auto *pixel_top     = (static_cast<Uint32 *>(s_->get_handle()->pixels) + p.x) + (p.y * s_->get_handle()->w);
            auto *pixel_bottom  = h > 0 ? pixel_top + ((h - 1) * s_->get_handle()->w) :
                                        pixel_top + ((h + 1) * s_->get_handle()->w);
            auto *pixel_left    = w > 0 ? pixel_top + s_->get_handle()->w : pixel_top - s_->get_handle()->w;
            auto *pixel_right   = w > 0 ? pixel_top + s_->get_handle()->w + w - 1 : (pixel_top - s_->get_handle()->w) + (w + 1);

            auto aw = w > 0 ? w : -w;
            auto iw = w > 0 ? 1 : -1;
            fp_type ix = ix_from;
            fp_type ix_inc = static_cast<fp_type>(1.0 * (ix_to - ix_from) / (aw == 0 ? 1 : aw));
            for(int i{0}; i < aw; ++i) {
                *pixel_top = pal[ix];
                *pixel_bottom = pal[ix];
                pixel_top += iw;
                pixel_bottom += iw;
                ix += ix_inc;
            }

            auto ah = h > 0 ? h : -h;
            auto ih = h > 0 ? s_->get_handle()->w : -s_->get_handle()->w;
            ix = ix_from;
            ix_inc = static_cast<fp_type>(1.0 * (ix_to - ix_from) / ((ah - 2) == 0 ? 1 : ah - 2));
            for(int i{0}; i < ah - 2; ++i) {
                *pixel_left = pal[ix];;
                *pixel_right = pal[ix];;
                pixel_left += ih;
                pixel_right += ih;
                ix += ix_inc;
            }
        }    

        inline auto draw_s(point p, int_type w, int_type h, const Uint32 rgba) -> void {
            
            {
                int_type x1 = p.x;
                int_type y1 = p.y;
                int_type x2 = p.x + w + (w >= 0 ? -1 : 1);
                int_type y2 = p.y + h + (w >= 0 ? -1 : 1);
                p.x = std::min(x1, x2);
                p.y = std::min(y1, y2);
                w = std::max(x1, x2) - p.x + 1;
                h = std::max(y1, y2) - p.y + 1;
            }

            int_type sx, sy, mw, mh;

            // Starting X
            if (0 > p.x && 0 <= p.x + w - 1) {
                sx = 0;
                mw = w + p.x;

            } else if (p.x + w - 1 < 0 || p.x >= s_->get_handle()->w) {
                return;

            } else {
                sx = p.x;
                mw = w;
            }

            // Starting Y
            if (0 > p.y && 0 <= p.y + h - 1) {
                sy = 0;
                mh = h + p.y;

            } else if (p.y + h - 1 < 0 || p.y >= s_->get_handle()->h) {
                return;
                
            } else {
                sy = p.y;
                mh = h;
            }

            // Modified Width
            if (sx + mw >= s_->get_handle()->w) mw -= sx + mw - s_->get_handle()->w;

            // Modified Height
            if (sy + mh >= s_->get_handle()->h) mh -= sy + mh - s_->get_handle()->h;


            auto *upper_left = (static_cast<Uint32 *>(s_->get_handle()->pixels) + sx) + (sy * s_->get_handle()->w);
            
            // Draw Top
            if(p.y == sy) {
                auto *pixel_top = upper_left;
                for (int i{0}; i < mw; ++i) *pixel_top++ = rgba;
            }
            
            // Draw Bottom
            if (p.y + h - 1 < s_->get_handle()->h) {
                auto *pixel_bottom = upper_left + ((mh - 1) * s_->get_handle()->w);
                for (int i{0}; i < mw; ++i) *pixel_bottom++ = rgba;
            }
            
            // Draw Left
            if (p.x == sx) {
                auto *pixel_left = upper_left + (p.y == sy ? s_->get_handle()->w : 0);
                auto d = (p.y + h - 1 < s_->get_handle()->h ? 2 : 1) + (p.y == sy ? 0 : -1);
                for (int i{0}; i < mh - d; ++i) {
                    *pixel_left = rgba;
                    pixel_left += s_->get_handle()->w;
                }
            }

            // Draw Right
            if (p.x + w - 1 < s_->get_handle()->w) {
                auto *pixel_right = upper_left + (p.y == sy ? s_->get_handle()->w : 0) + mw - 1;
                auto d = (p.y + h - 1 < s_->get_handle()->h ? 2 : 1) + (p.y == sy ? 0 : -1);
                for (int i{0}; i < mh - d; ++i) {
                    *pixel_right = rgba;
                    pixel_right += s_->get_handle()->w;
                }                
            }            
        }            

        inline auto draw_s(point p, int_type w, int_type h, const Uint32 rgba, const Uint32 mask) -> void {
            {
                int_type x1 = p.x;
                int_type y1 = p.y;
                int_type x2 = p.x + w + (w >= 0 ? -1 : 1);
                int_type y2 = p.y + h + (w >= 0 ? -1 : 1);
                p.x = std::min(x1, x2);
                p.y = std::min(y1, y2);
                w = std::max(x1, x2) - p.x + 1;
                h = std::max(y1, y2) - p.y + 1;
            }

            int_type sx, sy, mw, mh;

            // Starting X
            if (0 > p.x && 0 <= p.x + w - 1) {
                sx = 0;
                mw = w + p.x;

            } else if (p.x + w - 1 < 0 || p.x >= s_->get_handle()->w) {
                return;

            } else {
                sx = p.x;
                mw = w;
            }

            // Starting Y
            if (0 > p.y && 0 <= p.y + h - 1) {
                sy = 0;
                mh = h + p.y;

            } else if (p.y + h - 1 < 0 || p.y >= s_->get_handle()->h) {
                return;
                
            } else {
                sy = p.y;
                mh = h;
            }

            // Modified Width
            if (sx + mw >= s_->get_handle()->w) mw -= sx + mw - s_->get_handle()->w;

            // Modified Height
            if (sy + mh >= s_->get_handle()->h) mh -= sy + mh - s_->get_handle()->h;

            auto *upper_left = (static_cast<Uint32 *>(s_->get_handle()->pixels) + sx) + (sy * s_->get_handle()->w);
            
            // Draw Top
            if(p.y == sy) {
                auto tmask = mask >> ((sx - p.x) % 32);
                auto *pixel_top = upper_left;
                for (int i{0}; i < mw; ++i) {
                    *pixel_top = tmask & 1 ? rgba : 
                    *pixel_top; ++pixel_top;
                    tmask >>= 1;
                    tmask = !tmask ? mask : tmask;
                }
            }
            
            // Draw Bottom
            if (p.y + h - 1 < s_->get_handle()->h) {
                auto tmask = mask >> ((sx - p.x) % 32);
                auto *pixel_bottom = upper_left + ((mh - 1) * s_->get_handle()->w);
                for (int i{0}; i < mw; ++i) {
                    *pixel_bottom = tmask & 1 ? rgba : *pixel_bottom; 
                    ++pixel_bottom;
                    tmask >>= 1;
                    tmask = !tmask ? mask : tmask;
                }
            }
            
            // Draw Left
            if (p.x == sx) {
                auto tmask = mask >> ((sy - p.y) % 32);
                auto *pixel_left = upper_left + (p.y == sy ? s_->get_handle()->w : 0);
                auto d = (p.y + h - 1 < s_->get_handle()->h ? 2 : 1) + (p.y == sy ? 0 : -1);
                for (int i{0}; i < mh - d; ++i) {
                    *pixel_left = tmask & 1 ? rgba : *pixel_left;
                    pixel_left += s_->get_handle()->w;
                    tmask >>= 1;
                    tmask = !tmask ? mask : tmask;
                }
            }

            // Draw Right
            if (p.x + w - 1 < s_->get_handle()->w) {
                auto tmask = mask >> ((sy - p.y) % 32);
                auto *pixel_right = upper_left + (p.y == sy ? s_->get_handle()->w : 0) + mw - 1;
                auto d = (p.y + h - 1 < s_->get_handle()->h ? 2 : 1) + (p.y == sy ? 0 : -1);
                for (int i{0}; i < mh - d; ++i) {
                    *pixel_right = tmask & 1 ? rgba : *pixel_right;
                    pixel_right += s_->get_handle()->w;
                    tmask >>= 1;
                    tmask = !tmask ? mask : tmask;
                }                
            }            
        }

        inline auto draw_s(point p, int_type w, int_type h, const palette_gradient &pal, const int ix_from, const int ix_to) -> void {
            
            {
                int_type x1 = p.x;
                int_type y1 = p.y;
                int_type x2 = p.x + w + (w >= 0 ? -1 : 1);
                int_type y2 = p.y + h + (w >= 0 ? -1 : 1);
                p.x = std::min(x1, x2);
                p.y = std::min(y1, y2);
                w = std::max(x1, x2) - p.x + 1;
                h = std::max(y1, y2) - p.y + 1;
            }

            int_type sx, sy, mw, mh;

            // Starting X
            if (0 > p.x && 0 <= p.x + w - 1) {
                sx = 0;
                mw = w + p.x;

            } else if (p.x + w - 1 < 0 || p.x >= s_->get_handle()->w) {
                return;

            } else {
                sx = p.x;
                mw = w;
            }

            // Starting Y
            if (0 > p.y && 0 <= p.y + h - 1) {
                sy = 0;
                mh = h + p.y;

            } else if (p.y + h - 1 < 0 || p.y >= s_->get_handle()->h) {
                return;
                
            } else {
                sy = p.y;
                mh = h;
            }

            // Modified Width
            if (sx + mw >= s_->get_handle()->w) mw -= sx + mw - s_->get_handle()->w;

            // Modified Height
            if (sy + mh >= s_->get_handle()->h) mh -= sy + mh - s_->get_handle()->h;


            auto *upper_left = (static_cast<Uint32 *>(s_->get_handle()->pixels) + sx) + (sy * s_->get_handle()->w);
            
            // Draw Top
            if(p.y == sy) {
                fp_type ix_inc = static_cast<fp_type>(1.0 * (ix_to - ix_from) / (w == 0 ? 1 : w));
                fp_type ix = ix_from + ix_inc * (sx - p.x);
                auto *pixel_top = upper_left;
                for (int i{0}; i < mw; ++i) {*pixel_top++ = pal[ix]; ix += ix_inc;} 
            }
            
            // Draw Bottom
            if (p.y + h - 1 < s_->get_handle()->h) {
                fp_type ix_inc = static_cast<fp_type>(1.0 * (ix_to - ix_from) / (w == 0 ? 1 : w));
                fp_type ix = ix_from + ix_inc * (sx - p.x);
                auto *pixel_bottom = upper_left + ((mh - 1) * s_->get_handle()->w);
                for (int i{0}; i < mw; ++i) {*pixel_bottom++ = pal[ix]; ix += ix_inc;}
            }
            
            // Draw Left
            if (p.x == sx) {
                auto *pixel_left = upper_left + (p.y == sy ? s_->get_handle()->w : 0);
                auto d = (p.y + h - 1 < s_->get_handle()->h ? 2 : 1) + (p.y == sy ? 0 : -1);
                fp_type ix_inc = static_cast<fp_type>(1.0 * (ix_to - ix_from) / (h == 0 ? 1 : h));
                fp_type ix = ix_from + ix_inc * (sy - p.y);
                for (int i{0}; i < mh - d; ++i) {
                    *pixel_left = pal[ix];
                    pixel_left += s_->get_handle()->w;
                    ix += ix_inc;
                }
            }

            // Draw Right
            if (p.x + w - 1 < s_->get_handle()->w) {
                auto *pixel_right = upper_left + (p.y == sy ? s_->get_handle()->w : 0) + mw - 1;
                auto d = (p.y + h - 1 < s_->get_handle()->h ? 2 : 1) + (p.y == sy ? 0 : -1);
                fp_type ix_inc = static_cast<fp_type>(1.0 * (ix_to - ix_from) / ((h - d)== 0 ? 1 : h - d));
                fp_type ix = ix_from + ix_inc * (sy - p.y);
                for (int i{0}; i < mh - d; ++i) {
                    *pixel_right = pal[ix];
                    pixel_right += s_->get_handle()->w;
                    ix += ix_inc;
                }                
            }            
        }            


    };
}
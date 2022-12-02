#pragma once

#include "game/engine/surface.hpp" 
#include "game/gfx/palette.hpp"

namespace g80::game::gfx {

    using namespace g80::game::engine;
    
    class line {
    
    private:
        surface *s_;

    private:
        enum SCREEN_PLANE{TOP_LEFT = 0, TOP = 1, TOP_RIGHT = 2, LEFT = 3, ON_SCREEN = 4, RIGHT = 5, BOTTOM_LEFT = 6, BOTTOM = 7, BOTTOM_RIGHT = 8};
        auto get_screen_plane(const point &p) const -> SCREEN_PLANE;
        auto recalc_line_points(point &p1, point &p2, const SCREEN_PLANE sp1, const SCREEN_PLANE sp2) -> bool;

    public:
        line(surface *s);
        auto draw(const point &p1, const point &p2, const Uint32 rgba) -> void;
        auto draw(const point &p1, const point &p2, const palette_gradient &pal, const int ix_from, const int ix_to) -> void;
        auto draw(const point &p1, const point &p2, const Uint32 rgba, const Uint32 mask) -> void;
        auto draw_s(point p1, point p2, const Uint32 rgba) -> void;
        // Bug: mask should be adjusted accordingly when points are recalculated
        auto draw_s(point p1, point p2, const Uint32 rgba, const Uint32 mask) -> void;
        auto draw_s(point p1, point p2, const palette_gradient &pal, const int ix_from, const int ix_to) -> void;
    };

    line::line(surface *s) : s_(s) {
    }

    auto line::get_screen_plane(const point &p) const -> SCREEN_PLANE {
        if(p.x >= 0) [[likely]] {
            if(p.x < s_->get_handle()->w) [[likely]] {
                if(p.y >= 0) [[likely]] {
                    if(p.y < s_->get_handle()->h) [[likely]] return ON_SCREEN;
                    else return BOTTOM;
                } else return TOP;
            } else {
                if(p.y < 0) return TOP_RIGHT;
                else if(p.y >= s_->get_handle()->h) return BOTTOM_RIGHT;
                else return RIGHT;
            }
        } else {
            if(p.y < 0) return TOP_LEFT;
            else if(p.y >= s_->get_handle()->h) return BOTTOM_LEFT;
            else return LEFT;
        }
    }

    auto line::recalc_line_points(point &p1, point &p2, const SCREEN_PLANE sp1, const SCREEN_PLANE sp2) -> bool {
        fp_type h = p2.y - p1.y;
        fp_type w = p2.x - p1.x;

        auto get_x_at_y_equals = [&](const point &p, const int_type y_equals) -> int_type {
            if(w == 0) return p.x;
            fp_type m = h / w;
            fp_type b = p.y - (m * p.x);
            return static_cast<int_type>((y_equals - b) / m);
        };

        auto get_y_at_x_equals = [&](const point &p, const int_type x_equals) -> int_type {
            if(h == 0) return p.y;
            fp_type m = h / w;
            fp_type b = p.y - (m * p.x);
            return static_cast<int_type>(m * x_equals + b);
        };

        auto recalc_point_at_bound = [&](point &p, SCREEN_PLANE screen_plane) -> void {

            auto is_x_at_top = [&]() -> bool {if(auto tx = get_x_at_y_equals(p, 0); 
                                                s_->is_point_within_bounds(tx, 0)) {p.x = tx; p.y = 0; return true;} 
                                                return false;};
            auto is_x_at_bottom = [&]() -> bool {if(auto tx = get_x_at_y_equals(p, s_->get_hb()); 
                                                    s_->is_point_within_bounds(tx, s_->get_hb())) {p.x = tx; p.y = s_->get_hb(); return true;} 
                                                    return false;};
            auto get_x_at_top = [&]() -> void {p.x = get_x_at_y_equals(p, 0); p.y = 0;};
            auto get_x_at_bottom = [&]() -> void {p.x = get_x_at_y_equals(p, s_->get_hb()); p.y = s_->get_hb();};
            auto get_y_at_left = [&]() -> void {p.y = get_y_at_x_equals(p, 0); p.x = 0;};
            auto get_y_at_right = [&]() -> void {p.y = get_y_at_x_equals(p, s_->get_wb()); p.x = s_->get_wb();};
            auto check_top_left = [&]() -> void {if(is_x_at_top()) return; get_y_at_left(); return;};
            auto check_top_right = [&]() -> void {if(is_x_at_top()) return; get_y_at_right(); return;};
            auto check_bottom_left = [&]() -> void {if(is_x_at_bottom()) return; get_y_at_left(); return;};
            auto check_bottom_right = [&]() -> void {if(is_x_at_bottom()) return; get_y_at_right(); return;};

            switch(screen_plane) {
                case TOP_LEFT: check_top_left(); break;
                case TOP: get_x_at_top(); break;
                case TOP_RIGHT: check_top_right(); break;
                case BOTTOM_LEFT: check_bottom_left(); break;
                case BOTTOM_RIGHT: check_bottom_right(); break;
                case BOTTOM: get_x_at_bottom(); break;
                case LEFT: get_y_at_left(); break;
                case RIGHT: get_y_at_right(); break;
                default: break;
            }
        };

        if(sp1 != ON_SCREEN) {
            recalc_point_at_bound(p1, sp1);
            if(get_screen_plane(p1) != ON_SCREEN) return false;
        }

        if(sp2 != ON_SCREEN) {
            recalc_point_at_bound(p2, sp2);
            if(get_screen_plane(p2) != ON_SCREEN) return false;
        }

        return true;
    }

    auto line::draw(const point &p1, const point &p2, const Uint32 rgba) -> void {
        auto d = p2 - p1;
        auto ad = d.abs();
        int_type sdx = d.x < 0 ? -1 : 1;
        int_type sdy = d.y < 0 ? -s_->get_handle()->w : s_->get_handle()->w;
        Uint32 *pixel_buffer = static_cast<Uint32 *>(s_->get_handle()->pixels) + p1.y * s_->get_handle()->w + p1.x;
        auto draw_line = [&](int_type abs_g, int_type abs_l, int_type sig_g, int_type sig_l) -> void {
            for (int_type i = 0, t = abs_l; i <= abs_g; ++i, t += abs_l) {
                *pixel_buffer = rgba;
                if (t >= abs_g) {
                    pixel_buffer += sig_l;
                    t -= abs_g;
                }
                pixel_buffer += sig_g;
            }
        };

        if (ad.x >= ad.y) draw_line(ad.x, ad.y, sdx, sdy);
        else draw_line(ad.y, ad.x, sdy, sdx);
    }

    auto line::draw(const point &p1, const point &p2, const palette_gradient &pal, const int ix_from, const int ix_to) -> void {
        auto d = p2 - p1;
        auto ad = d.abs();
        int_type sdx = d.x < 0 ? -1 : 1;
        int_type sdy = d.y < 0 ? -s_->get_handle()->w : s_->get_handle()->w;
        Uint32 *pixel_buffer = static_cast<Uint32 *>(s_->get_handle()->pixels) + p1.y * s_->get_handle()->w + p1.x;
        auto draw_line = [&](int_type abs_g, int_type abs_l, int_type sig_g, int_type sig_l, fp_type ix_inc) -> void {
            fp_type ix = ix_from;
            for (int_type i = 0, t = abs_l; i <= abs_g; ++i, t += abs_l) {
                *pixel_buffer = pal[ix];
                if (t >= abs_g) {
                    pixel_buffer += sig_l;
                    t -= abs_g;
                }
                pixel_buffer += sig_g;
                ix += ix_inc;
            }
        };

        if (ad.x >= ad.y) {
            fp_type ix_inc = static_cast<fp_type>(1.0 * (ix_to - ix_from) / (ad.x == 0 ? 1 : ad.x));
            draw_line(ad.x, ad.y, sdx, sdy, ix_inc);
        } else {
            fp_type ix_inc = static_cast<fp_type>(1.0 * (ix_to - ix_from) / (ad.y == 0 ? 1 : ad.y));
            draw_line(ad.y, ad.x, sdy, sdx, ix_inc);
        }
    }

    auto line::draw(const point &p1, const point &p2, const Uint32 rgba, const Uint32 mask) -> void {
        auto d = p2 - p1;
        auto ad = d.abs();
        int_type sdx = d.x < 0 ? -1 : 1;
        int_type sdy = d.y < 0 ? -s_->get_handle()->w : s_->get_handle()->w;
        Uint32 *pixel_buffer = static_cast<Uint32 *>(s_->get_handle()->pixels) + p1.y * s_->get_handle()->w + p1.x;
        auto draw_line = [&](int_type abs_g, int_type abs_l, int_type sig_g, int_type sig_l) -> void {
            auto tmask = mask;
            decltype(tmask) tctr = 0;
            for (int_type i = 0, t = abs_l; i <= abs_g; ++i, t += abs_l) {
                *pixel_buffer = ((tmask >> tctr) & 1) ? rgba : *pixel_buffer;
                if (t >= abs_g) {
                    pixel_buffer += sig_l;
                    t -= abs_g;
                }
                pixel_buffer += sig_g;
                tctr += (tctr == 32) ? -32 : +1;
            }
        };

        if (ad.x >= ad.y) draw_line(ad.x, ad.y, sdx, sdy);
        else draw_line(ad.y, ad.x, sdy, sdx);
    }

    auto line::draw_s(point p1, point p2, const Uint32 rgba) -> void {
        auto sp1 = get_screen_plane(p1);
        auto sp2 = get_screen_plane(p2);
        if(sp1 != ON_SCREEN || sp2 != ON_SCREEN) [[unlikely]] 
            if(!recalc_line_points(p1, p2, sp1, sp2)) return;
        draw(p1, p2, rgba);
    }    

    auto line::draw_s(point p1, point p2, const Uint32 rgba, const Uint32 mask) -> void {
        auto sp1 = get_screen_plane(p1);
        auto sp2 = get_screen_plane(p2);
        if(sp1 != ON_SCREEN || sp2 != ON_SCREEN) [[unlikely]] 
            if(!recalc_line_points(p1, p2, sp1, sp2)) return;
        draw(p1, p2, rgba, mask);
    }    

    auto line::draw_s(point p1, point p2, const palette_gradient &pal, const int ix_from, const int ix_to) -> void {
        auto sp1 = get_screen_plane(p1);
        auto sp2 = get_screen_plane(p2);
        if(sp1 != ON_SCREEN || sp2 != ON_SCREEN) [[unlikely]] 
            if(!recalc_line_points(p1, p2, sp1, sp2)) return;
        draw(p1, p2, pal, ix_from, ix_to);
    }    

}


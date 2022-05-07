#ifndef _PROPULSION_HPP_
#define _PROPULSION_HPP_

#include <vector>
#include "Commons.hpp"

#include "EmptyAllocator.hpp"


namespace g80 {

    struct LinePoint {

        Point p1, p2;
        Sint32 dx, dy, sdx, sdy, adx, ady, t{0}, i{0};

        auto set(const Point &a1, const Point &a2) -> void {
            p1 = {a1};
            p2 = {a2};
            dx = {p2.x - p1.x};
            dy = {p2.y - p1.y};
            sdx = {dx < 0 ? -1 : 1};
            sdy = {dy < 0 ? -1 : 1};
            adx = {dx < 0 ? dx * -1 : dx};
            ady = {dy < 0 ? dy * -1 : dy};

            i = 0;
            if (adx >= ady) {    
                t = ady;
            } else {
                t = adx;
            }            
        }

        auto next() -> bool {
            if (adx >= ady) {    
                if (i > adx) return false;
                if (t >= adx) {
                    p1.y += sdy;
                    t -= adx;
                }
                p1.x +=sdx;
                t += ady;
            } else {
                if (i > ady) return false;
                if (t >= ady) {
                    p1.x += sdx;
                    t -= ady;
                }
                p1.y += sdy;
                t += adx;
            }
            ++i;
            return true;
        }
    };

    class Propulsion {
    public:
        Propulsion(Dim size) : burst_list_(size) {}

        auto add_burst(const Point &p1, const Point &p2) -> void {
            if (free_ < burst_list_.size() - 1) {
                burst_list_[free_].set(p1, p2);
                ++free_;
            }
        }

        auto next() -> void {
            for (Dim i = 0; i < free_; ++i) {
                // if (!burst_list_[i].next()) {
                //     std::swap(burst_list_[i], burst_list_[free_]);
                // }
            }
        }

        auto get_free_() const -> Dim {
            return free_;
        }

        auto get_size_() const -> Dim {
            return burst_list_.size();
        }

        inline auto operator[](Dim ix) -> LinePoint & {
            return burst_list_[ix];
        }

    private:
        Dim free_{0};
        std::vector<LinePoint, EmptyAllocator<LinePoint>> burst_list_;

    };
}

#endif 
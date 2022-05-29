#ifndef PROPULSION_MOTION_HPP
#define PROPULSION_MOTION_HPP

// This Propulsion Motion is Specific to Wormhole
    
#include <vector>
#include <SDL.h>
#include "TrigCache.hpp"
#include "LineMotion.hpp"
#include "LineWithAccelMotion.hpp"
#include "LCMRND.hpp"

namespace g80 {
/*

    Flow: blasts from <inner radius> will
    be projected to the <outer radius> 
            
              __ <inner radius>
             |/_|-------------- <center> ----------------- <origin>
             /  
            / <inner_outer_dist>
       ____/
      |  _/|------------------  
      |____|<outer radius> 

    Inner outer distance decreases as the inner radius approaches origin.    

*/


    template<typename T>
    class PropulsionMotion {
    public:
        PropulsionMotion() {}
        
        auto set_propulsion_motion(
            const Point<Sint32> &center, 
            const Sint32 inner_radius, 
            const Sint32 outer_radius, 
            const Sint32 inner_radius_dist_from_center,
            const Sint32 outer_radius_dist_from_center,
            const Sint32 blasts_n,
            const CosCache<T> cosine,
            const SinCache<T> sine,
            const Sint32 aix,
            const Sint32 aox) -> void {

            center_ = {center}; 
            inner_radius_ = {inner_radius}; 
            outer_radius_ = {outer_radius};
            inner_radius_dist_from_center_ = {inner_radius_dist_from_center};
            outer_radius_dist_from_center_ = {outer_radius_dist_from_center};
            f_ = {static_cast<T>(outer_radius_ / inner_radius_)};

            blasts_.reserve(blasts_n);
            for (Sint32 i = 0; i < blasts_n; ++i) {
                blasts_.emplace_back();

                Point<Sint32> p, t;
                auto raix = lcm_rnd() % cosine.get_size();
                auto rinner_radius = 1 + lcm_rnd() % inner_radius_; 
                auto rinner_radiusf = rinner_radius * f_;
                p.x = get_inner_radius_center(cosine, sine, aix).x + rinner_radius * cosine[raix]; 
                p.y = get_inner_radius_center(cosine, sine, aix).y + rinner_radius * sine[raix]; 
                t.x = get_outer_radius_center(cosine, sine, aix).x + rinner_radiusf * cosine[raix]; 
                t.y = get_outer_radius_center(cosine, sine, aix).y + rinner_radiusf * sine[raix]; 

                blasts_[i].line_with_accel_motion_set(p, t, 1 + lcm_rnd() % 10, 2);
            }
        }

        inline auto get_inner_radius_center(const CosCache<T> &cosine, const SinCache<T> &sine, const Sint32 aix) -> Point<Sint32> {
            return Point<Sint32>(center_.x + inner_radius_dist_from_center_ * cosine[aix], center_.y + inner_radius_dist_from_center_ * sine[aix] );
        }

        inline auto get_outer_radius_center(const CosCache<T> &cosine, const SinCache<T> &sine, const Sint32 aix) -> Point<Sint32> {
            return Point<Sint32>(center_.x + outer_radius_dist_from_center_ * cosine[aix], center_.y + outer_radius_dist_from_center_ * sine[aix] );
        }

        auto next(const CosCache<T> &cosine, const SinCache<T> &sine, const Sint32 aix, const Sint32 aox/*, const Sint32 a_origin_ix*/) -> void {

            // aox - a_origin_ix)
            T lerp = 1.0f * (aox >= cosine.get_size() / 2 ? cosine.get_size() - aox : aox) / cosine.get_size();
            auto couter_radius_dist_from_center = inner_radius_dist_from_center_ + lerp * (outer_radius_dist_from_center_ - inner_radius_dist_from_center_);

            for (auto &b : blasts_) {
                if (!b.next()) {
                    Point<Sint32> p, t;
                    auto raix = lcm_rnd() % cosine.get_size();
                    auto rinner_radius = 1 + lcm_rnd() % inner_radius_; 
                    auto rinner_radiusf = rinner_radius * f_;
                    p.x = get_inner_radius_center(cosine, sine, aix).x + rinner_radius * cosine[raix]; 
                    p.y = get_inner_radius_center(cosine, sine, aix).y + rinner_radius * sine[raix]; 

                    t.x = (center_.x + couter_radius_dist_from_center * cosine[aix]) + rinner_radiusf * cosine[raix];
                    t.y = (center_.y + couter_radius_dist_from_center * sine[aix])+ rinner_radiusf * sine[raix]; 

                    b.line_with_accel_motion_set(p, t,  1 + lcm_rnd() % 10, 2);
                }
            }
        }

        inline auto get_center() -> Point<Sint32> {return center_;}
        inline auto get_inner_radius() -> Sint32 {return inner_radius_;}
        inline auto get_outer_radius() -> Sint32 {return outer_radius_;}
        inline auto get_inner_radius_dist_from_center() -> Sint32 {return inner_radius_dist_from_center_;}
        inline auto get_outer_radius_dist_from_center() -> Sint32 {return outer_radius_dist_from_center_;}

        inline auto get_blasts() const-> const std::vector<LineWithAccelMotion<T>> & {return blasts_;}

    private:
        Point<Sint32> center_;
        Sint32 inner_radius_, outer_radius_, inner_radius_dist_from_center_, outer_radius_dist_from_center_;
        std::vector<LineWithAccelMotion<T>> blasts_;
        T f_;
    };

}

#endif
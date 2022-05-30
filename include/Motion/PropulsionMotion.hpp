#ifndef PROPULSION_MOTION_HPP
#define PROPULSION_MOTION_HPP

// This Propulsion Motion is Specific to Wormhole Module
    
#include <vector>
#include <SDL.h>
#include "TrigCache.hpp"
#include "LineMotion.hpp"
#include "LineWithAccelMotion.hpp"
#include "LCMRND.hpp"

namespace g80 {
/*

    Flow:
    Blasts from <inner radius> will
    be projected to the <outer radius> 
            
              __ <inner radius>
             |/_| <-------------- <center> ----------------- <origin>
             /  
            / <inner_outer_dist>
       ____/
      |  _/|------------------  
      |____|<outer radius> 

    Inner outer distance decreases as the inner radius approaches origin.    

*/
    template<typename F>
    using Blasts = std::vector<LineWithAccelMotion<F>>;

    template<typename F>
    class PropulsionMotion {
    public:
        PropulsionMotion(
            Sint32 sz_blast_steps, 
            Sint32 sz_blast_trail) :
            sz_blast_steps_{sz_blast_steps}, 
            sz_blast_trail_{sz_blast_trail} {}
        
        auto set(
            const Point<Sint32> &center, 
            const Sint32 inner_radius, 
            const Sint32 outer_radius, 
            const Sint32 inner_radius_dist_from_center,
            const Sint32 outer_radius_dist_from_center,
            const Sint32 blasts_n,
            const CosCache<F> cosine,
            const SinCache<F> sine,
            const Sint32 aix,
            const Sint32 aox) -> void {

            center_ = {center}; 
            inner_radius_ = {inner_radius}; 
            outer_radius_ = {outer_radius};
            inner_radius_dist_from_center_ = {inner_radius_dist_from_center};
            outer_radius_dist_from_center_ = {outer_radius_dist_from_center};
            outer_inner_ratio_ = {static_cast<F>(outer_radius_ / inner_radius_)};

            blasts_.reserve(blasts_n);
            for (Sint32 i = 0; i < blasts_n; ++i) {
                blasts_.emplace_back();

                // TODO: Combine this part with next;
                Point<Sint32> p, t;
                auto rnd_inner_angle_ix = lcm_rnd() % cosine.get_size();
                auto rnd_inner_radius = 1 + lcm_rnd() % inner_radius_; 
                auto rnd_inner_radiusf = rnd_inner_radius * outer_inner_ratio_;
                p.x = get_inner_radius_center(cosine, sine, aix).x + rnd_inner_radius * cosine[rnd_inner_angle_ix]; 
                p.y = get_inner_radius_center(cosine, sine, aix).y + rnd_inner_radius * sine[rnd_inner_angle_ix]; 
                t.x = get_outer_radius_center(cosine, sine, aix).x + rnd_inner_radiusf * cosine[rnd_inner_angle_ix]; 
                t.y = get_outer_radius_center(cosine, sine, aix).y + rnd_inner_radiusf * sine[rnd_inner_angle_ix]; 

                blasts_[i].line_with_accel_motion_set(p, t, 1 + lcm_rnd() % sz_blast_steps_, sz_blast_trail_);
            }
        }

        inline auto get_inner_radius_center(const CosCache<F> &cosine, const SinCache<F> &sine, const Sint32 aix) -> Point<Sint32> {
            return Point<Sint32>(center_.x + inner_radius_dist_from_center_ * cosine[aix], center_.y + inner_radius_dist_from_center_ * sine[aix] );
        }

        inline auto get_outer_radius_center(const CosCache<F> &cosine, const SinCache<F> &sine, const Sint32 aix) -> Point<Sint32> {
            return Point<Sint32>(center_.x + outer_radius_dist_from_center_ * cosine[aix], center_.y + outer_radius_dist_from_center_ * sine[aix] );
        }

        auto next(
            const CosCache<F> &cosine, 
            const SinCache<F> &sine, 
            const Sint32 inner_angle_ix, 
            const Sint32 origin_angle_ix) -> void {

            auto trig_cache_half = cosine.get_size() >> 1;
            
            // todo: compute outer angle
            //
            //  outer_angle = f(deg) = k * deg ^ 2
            //  k = trig_cache_half / (deg * deg)

            // T k = 1.0f ; // * trig_cache_half / (trig_cache_half * trig_cache_half);
            Sint32 outer_angle_ix = 1.025f * inner_angle_ix; // k * inner_angle_ix * inner_angle_ix;
            // SDL_Log("%.6f %d %d", k, outer_angle_ix, inner_angle_ix);
            auto reouter_inner_ratio_outer_angle_ix = outer_angle_ix - origin_angle_ix;
            if (reouter_inner_ratio_outer_angle_ix < 0) reouter_inner_ratio_outer_angle_ix = cosine.get_size() + reouter_inner_ratio_outer_angle_ix;
            
            F lerp = 1.0f * (reouter_inner_ratio_outer_angle_ix >= trig_cache_half ? cosine.get_size() - reouter_inner_ratio_outer_angle_ix : reouter_inner_ratio_outer_angle_ix) / trig_cache_half;
            auto couter_radius_dist_from_center = inner_radius_dist_from_center_ + lerp * (outer_radius_dist_from_center_ - inner_radius_dist_from_center_);



            for (auto &b : blasts_) {
                if (!b.next()) {
                    Point<Sint32> blast_from, blast_to;
                    auto rnd_inner_angle_ix = lcm_rnd() % cosine.get_size();
                    auto rnd_inner_radius = 1 + lcm_rnd() % inner_radius_; 
                    auto rnd_outer_radius = rnd_inner_radius * outer_inner_ratio_;
                    blast_from.x = (center_.x + inner_radius_dist_from_center_ * cosine[inner_angle_ix]) + rnd_inner_radius * cosine[rnd_inner_angle_ix];
                    blast_from.y = (center_.y + inner_radius_dist_from_center_ * sine[inner_angle_ix]) + rnd_inner_radius * sine[rnd_inner_angle_ix];
                    blast_to.x = (center_.x + couter_radius_dist_from_center * cosine[outer_angle_ix]) + rnd_outer_radius * cosine[rnd_inner_angle_ix];
                    blast_to.y = (center_.y + couter_radius_dist_from_center * sine[outer_angle_ix]) + rnd_outer_radius * sine[rnd_inner_angle_ix]; 
                    b.line_with_accel_motion_set(blast_from, blast_to,  1 + lcm_rnd() % sz_blast_steps_, sz_blast_trail_);
                }
            }
        }

        inline auto get_center() -> Point<Sint32> {return center_;}
        inline auto get_inner_radius() -> Sint32 {return inner_radius_;}
        inline auto get_outer_radius() -> Sint32 {return outer_radius_;}
        inline auto get_inner_radius_dist_from_center() -> Sint32 {return inner_radius_dist_from_center_;}
        inline auto get_outer_radius_dist_from_center() -> Sint32 {return outer_radius_dist_from_center_;}

        inline auto get_blasts() const-> const Blasts<F> & {return blasts_;}

    private:
        Sint32 sz_blast_steps_{10}, sz_blast_trail_{2};
        Point<Sint32> center_;
        Sint32 inner_radius_, outer_radius_, inner_radius_dist_from_center_, outer_radius_dist_from_center_;
        Blasts<F> blasts_;
        F outer_inner_ratio_;
    };

}

#endif
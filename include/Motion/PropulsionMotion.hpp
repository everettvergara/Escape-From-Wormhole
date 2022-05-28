#ifndef PROPULSION_MOTION_HPP
#define PROPULSION_MOTION_HPP

// This Propulsion Motion is Specific to Wormhole
    
#include <vector>
#include <SDL.h>
#include "TrigCache.hpp"
#include "LineMotion.hpp"
#include "LCMRND.hpp"

namespace g80 {

    class PropulsionMotion {
    public:
        PropulsionMotion(Sint32 blasts_n) : blasts_n_(blasts_n) {}
        
        template<typename T>
        auto set_propulsion_motion(
            const Point<Sint32> &center, 
            const Sint32 irad, 
            const Sint32 orad, 
            const Sint32 irad_dist,
            const Sint32 orad_dist,
            const CosCache<T> cosine,
            const SinCache<T> sine) -> void {

            center_ = {center}; 
            irad_ = {irad}; 
            orad_ = {orad};
            irad_dist_ = {irad_dist};
            orad_dist_ = {orad_dist};

            blasts_.reserve(blasts_n_);
            for (Sint32 i = 0; i < blasts_n_; ++i) {
                blasts_.emplace_back();

                Point<Sint32> p, t;
                auto raix = lcm_rnd() % cosine.get_size();
                auto rirad = 1 + lcm_rnd() % irad_; 
                p.x = get_irad_center(cosine, sine, raix).x + rirad * cosine[raix]; 
                p.y = get_irad_center(cosine, sine, raix).y + rirad * sine[raix]; 
                t.x = get_orad_center(cosine, sine, raix).x + rirad * cosine[raix]; 
                t.y = get_orad_center(cosine, sine, raix).y + rirad * sine[raix]; 

                blasts_[i].line_motion_set(p, t, 20, 2);
            }
        }

        template<typename T>
        inline auto get_irad_center(const CosCache<T> &cosine, const SinCache<T> &sine, const Sint32 aix) -> Point<Sint32> {
            return Point<Sint32>(center_.x + irad_dist_ * cosine[aix], center_.y + irad_dist_ * sine[aix] );
        }

        template<typename T>
        inline auto get_orad_center(const CosCache<T> &cosine, const SinCache<T> &sine, const Sint32 aix) -> Point<Sint32> {
            return Point<Sint32>(center_.x + orad_dist_ * cosine[aix], center_.y + orad_dist_ * sine[aix] );
        }

        template<typename T>
        auto next(const CosCache<T> &cosine, const SinCache<T> &sine) -> void {
            for (auto &b : blasts_) {
                if (!b.next()) {
                    Point<Sint32> p, t;
                    auto raix = lcm_rnd() % cosine.get_size();
                    auto rirad = 1 + lcm_rnd() % irad_; 
                    p.x = get_irad_center(cosine, sine, raix).x + rirad * cosine[raix]; 
                    p.y = get_irad_center(cosine, sine, raix).y + rirad * sine[raix]; 
                    t.x = get_orad_center(cosine, sine, raix).x + rirad * cosine[raix]; 
                    t.y = get_orad_center(cosine, sine, raix).y + rirad * sine[raix]; 

                    b.line_motion_set(p, t, 20, 2);
                }
            }
        }

        inline auto get_center() -> Point<Sint32> {return center_;}
        inline auto get_irad() -> Sint32 {return irad_;}
        inline auto get_orad() -> Sint32 {return orad_;}
        inline auto get_irad_dist() -> Sint32 {return irad_dist_;}
        inline auto get_orad_dist() -> Sint32 {return orad_dist_;}
        inline auto get_blasts() const-> const std::vector<LineMotion<float>> & {return blasts_;}

    private:
        Point<Sint32> center_;
        Sint32 irad_, orad_, irad_dist_, orad_dist_;
        Sint32 blasts_n_;
        std::vector<LineMotion<float>> blasts_;
    };

}

#endif
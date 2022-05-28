#ifndef PROPULSION_MOTION_HPP
#define PROPULSION_MOTION_HPP

// This Propulsion Motion is Specific to Wormhole
    
#include <SDL.h>
#include "TrigCache.hpp"

namespace g80 {

    class PropulsionMotion {
    public:
        PropulsionMotion() {}
        auto set_propulsion_motion(
            const Point<Sint32> &center, 
            const Sint32 irad, 
            const Sint32 orad, 
            const Sint32 irad_dist,
            const Sint32 orad_dist) -> void {

            center_ = {center}; 
            irad_ = {irad}; 
            orad_ = {orad};
            irad_dist_ = {irad_dist};
            orad_dist_ = {orad_dist};

        }

        template<typename T>
        inline auto get_irad(const CosCache<T> &cosine, const SinCache<T> &sine, const Sint32 aix) -> Point<Sint32> {
            return Point<Sint32>(center_.x + irad_ * cosine[aix]);
        }

    private:
        Point<Sint32> center_;
        Sint32 irad_, orad_, irad_dist_, orad_dist_;
    };

}

#endif
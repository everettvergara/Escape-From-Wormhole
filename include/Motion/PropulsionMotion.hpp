#ifndef PROPULSION_MOTION_HPP
#define PROPULSION_MOTION_HPP

// This Propulsion Motion is Specific to Wormhole
    
#include <SDL.h>

namespace g80 {

    class PropulsionMotion {
    public:
        PropulsionMotion(const Point<Sint32> &center, const Sint32 irad, const Sint32 orad) :
        center_(center), irad_(irad), orad_(orad) {

        }
    private:
        Point<Sint32> center_;
        Sint32 irad_, orad_;
    }

}

#endif
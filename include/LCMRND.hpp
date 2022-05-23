#ifndef _LCMRND_HPP_
#define _LCMRND_HPP_

#include <SDL.h>

namespace g80 {

    constexpr Sint32 MAX_LCM_RND = 2147483647;

    inline auto lcm_rnd() -> Sint32 {
        static std::time_t now = time(&now);
        static Uint32 seed = now;
        static Uint32 a = 1103515245;
        static Uint32 c = 12345;
        static Uint32 m = (static_cast<Uint32>(MAX_LCM_RND) + 1);
        static Uint32 rand = seed;
        return static_cast<Sint32>(rand = (rand * a + c) % m);
    }
}

#endif

#ifndef _SINCOS_HPP_
#define _SINCOS_HPP_

#include "Commons.hpp"
#include <vector>
#include <EmptyAllocator.hpp>

namespace g80 {

    template<typename FT>
    using AngleValues = std::vector<FT, EmptyAllocator<FT>>;

    template<typename FT>
    class TrigCache {

    public:
        TrigCache(Dim N) : N_(N) {
            angle_values_.reserve(N_);
        } 

    private:
        Dim N_;
        AngleValues angle_values_;
    };
}

#endif 
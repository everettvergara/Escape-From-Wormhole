#ifndef _CIRCLEMOTION_HPP_
#define _CIRCLEMOTION_HPP_

#include "PointMotion.hpp"
#include "TrigCache.hpp"

namespace g80 {

    // todo: remove pointmotion

    template<typename T>
    class CircleMotion : public PointMotion<T> {
    public:
        CircleMotion() : PointMotion<T>() {}
        ~CircleMotion() {}

        auto circle_motion_set(
            const Point<T> &p, 
            const Sint32 radius,
            const Sint32 sz_steps,
            const Sint32 sz_trail,
            const Sint32 start_ix, 
            const Sint32 end_ix, 
            const CosCache<T> &cosine_cache,
            const SinCache<T> &sine_cache) : 
                center_(p){
            
            this->set(Point<T>{
                center_.x + radius * cosine_cache[start_ix], 
                center_.y + radius * sine_cache[start_ix]}, 
                sz_steps, sz_trail);
            inc_ = 1.0f * (end_angle - start_angle) / sz_steps;
        }

        auto next() -> bool {
            // if (this->tail_step_ == this->sz_steps_) return false;

            // if (this->head_step_ < this->sz_steps_) {
            //     this->head_ += inc_;
            //     ++this->head_step_;
            // }

            // if (this->tail_step_++ >= 0)
            //     this->tail_ += inc_;

            return true;
        }

    private:
        Point<T> center_;
        float inc_;
    };
}

#endif
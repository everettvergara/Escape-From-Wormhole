#ifndef _LINEMOTION_HPP_
#define _LINEMOTION_HPP_

#include "PointMotion.hpp"

namespace g80 {

    // TODO: CHECK IF steps will be removed and be replaced by accel
    template<typename T>
    class LineMotion : public PointMotion<T> {
    public:
        LineMotion() : PointMotion<T>() {};

        auto line_motion_set(
            const Point<T> &start_point, 
            const Point<T> &end_point, 
            const Sint32 sz_steps,
            const Sint32 sz_trail) {
            
            this->set(start_point, sz_steps, sz_trail);

            start_point_ = start_point;

            // Accel x,y = k * s^2
            Point<T> delta {end_point - start_point};
            k_ = delta / (this->sz_steps_ * this->sz_steps_);
        }

        auto next() -> bool {
            if (this->tail_step_ == this->sz_steps_) return false;

            if (this->head_step_ < this->sz_steps_) {
                float step_sq = this->head_step_ * this->head_step_; 
                this->head_ = start_point_ + k_ * step_sq;
                ++this->head_step_;
            }

            if (this->tail_step_++ >= 0) {
                float tail_step_sq = this->tail_step_ * this->tail_step_; 
                this->tail_ = start_point_ + k_ * tail_step_sq;
            }

            return true;
        }

    private:
        Point<T> start_point_, k_;
    };
}

#endif
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
            Point<T> delta {end_point - start_point};
            head_inc_.x = delta.x / this->sz_steps_;
            head_inc_.y = delta.y / this->sz_steps_;
            tail_inc_ = head_inc_;
        }

        auto next() -> bool {
            if (this->step_ == this->sz_steps_) return false;

            this->head_ += head_inc_;
            
            if (this->step_++ >= 0) {
                this->tail_ += tail_inc_; 
            }

            // SDL_Log("%.2f %.2f, %.2f, %.2f", this->tail_step_, this->step_size_, this->head_.x, this->head_.y);
            return true;
        }

    private:
        Point<T> head_inc_, tail_inc_;
    };
}

#endif
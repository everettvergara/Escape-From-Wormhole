#ifndef _LINEMOTION_HPP_
#define _LINEMOTION_HPP_

#include "PointMotion.hpp"

namespace g80 {

    template<typename T>
    class LineMotion : public PointMotion<T> {
    public:
        LineMotion() : PointMotion<T>() {}
        ~LineMotion() {}

        auto line_motion_set(
            const Point<T> &start_point, 
            const Point<T> &end_point, 
            const Sint32 sz_steps,
            const Sint32 sz_trail) {
            
            this->set(start_point, sz_steps, sz_trail);

            Point<T> delta = end_point - start_point;
            inc_ = delta / sz_steps;
        }

        auto next() -> bool {
            if (this->tail_step_ == this->sz_steps_) return false;

            if (this->head_step_ < this->sz_steps_) {
                this->head_ += inc_;
                ++this->head_step_;
            }

            if (this->tail_step_++ >= 0)
                this->tail_ += inc_;


            // SDL_Log("%.2f %.2f", this->tail_.x, this->tail_.y);
            return true;
        }

    private:
        Point<T> inc_;
    };
}

#endif
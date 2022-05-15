#ifndef _LINEMOTION_HPP_
#define _LINEMOTION_HPP_

#include "PointMotion.hpp"

namespace g80 {

    template<typename T>
    class LineMotion : public PointMotion<T> {
    public:
        LineMotion() : PointMotion<T>() {};

        auto line_motion_set(
            const Point<T> &start_point, 
            const Point<T> &end_point, 
            const T step_size, 
            const T trail_size,
            const T accel = 1) {
            
            this->set(start_point, step_size, trail_size);
            
            Point<T> delta {end_point - start_point};

            head_inc_.x = delta.x / this->step_size_;
            head_inc_.y = delta.y / this->step_size_;
            tail_inc_ = head_inc_;
            
            accel_ = accel;
        }

        auto next() -> bool {
            
            if (this->tail_step_ == this->step_size_) return false;
            
            if (this->current_step_ < this->step_size_) {
                this->head_ += head_inc_;
                head_inc_ *= accel_;
                
                ++this->current_step_;
            }
        
            if (this->tail_step_++ >= 0) {
                this->tail_ += tail_inc_;
                tail_inc_ *= accel_;                
            }

            SDL_Log("%.2f, %.2f to %.2f, %.2f", this->tail_.x, this->tail_.y, this->head_.x, this->head_.y);
            return true;
        }

    private:
        T x_inc_, y_inc_;
        Point<T> head_inc_, tail_inc_;
        T accel_;
    };
}

#endif
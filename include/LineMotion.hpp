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
            const T trail_size,
            const T accel = 0.0f) {
            
            this->set(start_point, trail_size);
            
            Point<T> delta {end_point - start_point};

            head_inc_.x = start_point.x + delta.x / this->step_size_;
            head_inc_.y = start_point.y + delta.y / this->step_size_;
            tail_inc_ = head_inc_;
            
            accel_ = delta * 0.0005f; // 0.0f; // 0.0005f;
        }

        auto next() -> bool {
            if (this->tail_step_ > this->step_size_) return false;

            this->head_ += head_inc_;
            head_inc_ += accel_;
            
            // tail_step_ += 
            if (this->tail_step_++ >= 0) {
                this->tail_ += tail_inc_;
                tail_inc_ += accel_;                
            }
            
            SDL_Log("%.2f %.2f, %.2f, %.2f", this->tail_step_, this->step_size_, this->head_.x, this->head_.y);
            return true;
        }

    private:
        T x_inc_, y_inc_;
        Point<T> head_inc_, tail_inc_, accel_;
    };
}

#endif
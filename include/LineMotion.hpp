#ifndef _LINEMOTION_HPP_
#define _LINEMOTION_HPP_

#include "PointMotion.hpp"

namespace g80 {

    template<typename T>
    class LineMotion : public PointMotion<T> {
    public:
        LineMotion() : PointMotion<T>() {};

        auto line_motion_set(const Point<T> &start_point, const Point<T> &end_point, Sint32 step_size, Sint32 trail_size) {
            
            this->set(start_point, step_size, trail_size);
            
            Point<T> delta {end_point - start_point};
            x_inc_ = delta.x / this->step_size_;
            y_inc_ = delta.y / this->step_size_;
        }

        auto next() -> bool {
            
            if (this->tail_step_ == this->step_size_) return false;
            
            if (this->current_step_ < this->step_size_) {
                this->head_.x += x_inc_;
                this->head_.y += y_inc_;
                ++this->current_step_;
            }
        
            if (this->tail_step_++ >= 0) {
                this->tail_.x += x_inc_;
                this->tail_.y += y_inc_;                
            }

            return true;
        }

    private:
        T x_inc_, y_inc_;
    };
}

#endif
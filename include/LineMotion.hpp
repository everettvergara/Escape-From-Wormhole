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
            start_ = start_point;
            Point<T> delta {end_point - start_point};
            // head_inc_.x = delta.x / this->sz_steps_;
            // head_inc_.y = delta.y / this->sz_steps_;
            // tail_inc_ = head_inc_;

            // Accelaration 
            // e = 2
            // Accel in x,y = k * s^e;
            // 
            // Compute for k:
            
            float step_sq =  this->sz_steps_ * this->sz_steps_;
            k_x_ = delta.x / step_sq;
            k_y_ = delta.y / step_sq;

            // k = xy / (s^e);
            
        }

        auto next() -> bool {
            if (this->tail_step_ == this->sz_steps_) return false;

            
            float step_sq = this->head_step_ * this->head_step_; 
            this->head_.x = start_.x + k_x_ * step_sq;
            this->head_.y = start_.y + k_y_ * step_sq;
            ++this->head_step_;

            if (this->tail_step_++ >= 0) {
                float tail_step_sq = this->tail_step_ * this->tail_step_; 
                this->tail_.x = start_.x + k_x_ * tail_step_sq;
                this->tail_.y = start_.y + k_y_ * tail_step_sq;                
            }

            SDL_Log("%.2f, %.2f", this->head_.x, this->head_.y);
            return true;
        }

    private:
        Point<T> start_;
        float k_x_, k_y_;
    };
}

#endif
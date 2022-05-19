#ifndef _LINEWITHACCELMOTION_HPP_
#define _LINEWITHACCELMOTION_HPP_

#include "PointMotion.hpp"

namespace g80 {

    template<typename T>
    class LineWithAccelMotion {
    public:
        LineWithAccelMotion() {}
        ~LineWithAccelMotion() {}

        auto line_with_accel_motion_set(
            const Point<T> &start_point, 
            const Point<T> &end_point, 
            const Sint32 sz_steps,
            const Sint32 sz_trail) {
            
            head_ = {start_point};
            tail_ = {start_point};
            sz_steps_ = {sz_steps};
            tail_step_ = {-sz_trail};
            head_step_ = {0};
            start_point_ = start_point;

            Point<T> delta {end_point - start_point};
            k_ = delta / (sz_steps_ * sz_steps_);
        }

        auto next() -> bool {
            if (tail_step_ == sz_steps_) return false;

            if (head_step_ < sz_steps_) {
                float step_sq = head_step_ * head_step_; 
                head_ = start_point_ + k_ * step_sq;
                ++head_step_;
            }

            if (tail_step_++ >= 0) {
                float tail_step_sq = tail_step_ * tail_step_; 
                tail_ = start_point_ + k_ * tail_step_sq;
            }

            return true;
        }

        inline auto get_head() const -> const Point<T> & {return head_;}
        inline auto get_tail() const -> const Point<T> & {return tail_;}
        inline auto get_head_step() const -> Sint32 {return head_step_;}
        inline auto get_tail_step() const -> Sint32 {return tail_step_;}
        inline auto get_size_of_step() const -> Sint32 {return sz_steps_;}

    private:
        Point<T> head_, tail_;
        Sint32 sz_steps_, tail_step_, head_step_;
        Point<T> start_point_, k_;
    };
}

#endif
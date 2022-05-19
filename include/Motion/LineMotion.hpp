#ifndef _LINEMOTION_HPP_
#define _LINEMOTION_HPP_

#include "Point.hpp"

namespace g80 {

    template<typename T>
    class LineMotion {
    public:
        LineMotion() {}
        ~LineMotion() {}

        auto line_motion_set(
            const Point<T> &start_point, 
            const Point<T> &end_point, 
            const Sint32 sz_steps,
            const Sint32 sz_trail) {
            
            head_ = {start_point};
            tail_ = {start_point};
            sz_steps_ = {sz_steps};
            tail_step_ = {-sz_trail};
            head_step_ = {0};

            Point<T> delta = end_point - start_point;
            inc_ = delta / sz_steps;
        }

        auto next() -> bool {
            if (tail_step_ == sz_steps_) return false;

            if (head_step_ < sz_steps_) {
                head_ += inc_;
                ++head_step_;
            }

            if (tail_step_++ >= 0)
                tail_ += inc_;

            return true;
        }
        
        inline auto get_head() const -> const Point<T> & {return head_;}
        inline auto get_tail() const -> const Point<T> & {return tail_;}
        inline auto get_head_step() const -> Sint32 {return head_step_;}
        inline auto get_tail_step() const -> Sint32 {return tail_step_;}
        inline auto get_size_of_step() const -> Sint32 {return sz_steps_;}

    private:
        Point<T> head_, tail_;
        Point<T> inc_;
        Sint32 sz_steps_, tail_step_, head_step_;
    };
}

#endif
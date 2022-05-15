#ifndef _POINTMOTION_HPP_
#define _POINTMOTION_HPP_

#include "Point.hpp"

namespace g80 {

    template<typename T>
    class PointMotion {
    public:
        PointMotion(const Point<T> &start_point, const Sint32 step_size, const Sint32 trail_size) : 
            head_(start_point),
            tail_(start_point),
            step_size_(step_size), trail_size_(trail_size), tail_step_(-trail_size_) {}

        virtual auto reset() -> void {};
        virtual auto next() -> bool {return true;};

        auto get_head() const -> const Point<T> & {return head_;}
        auto get_tail() const -> const Point<T> & {return tail_;}

    protected:
        Point<T> head_;
        Point<T> tail_;
        Sint32 step_size_, step_{0};
        Sint32 trail_size_;
        Sint32 current_step_{0}, tail_step_;
    };

    template<typename T>
    class LineMotion : public PointMotion<T> {
    public:
        LineMotion(const Point<T> &start_point, const Point<T> &end_point, Sint32 step_size, Sint32 trail_size) : 
            PointMotion<T>(start_point, step_size, trail_size),
            delta_(end_point - start_point) {
            x_inc_ = delta_.x / this->step_size_;
            y_inc_ = delta_.y / this->step_size_;
        }

        auto next() -> bool {
            // if (step_ == this->step_size_) return false;
            this->head_.x += x_inc_;
            this->head_.y += y_inc_;
            return true;
        }

    private:
        Point<float> delta_;
        float x_inc_, y_inc_;
    };
}

#endif
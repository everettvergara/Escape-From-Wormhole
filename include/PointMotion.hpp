#ifndef _POINTMOTION_HPP_
#define _POINTMOTION_HPP_

#include <type_traits>
#include "Point.hpp"

namespace g80 {

    template<typename T>
    class PointMotion {
    static_assert(
        std::is_same<T, float>::value ||
        std::is_same<T, double>::value ||
        std::is_same<T, long double>::value, "Type must be float, double or long double only.");

    public:
        PointMotion() {};

        virtual auto next() -> bool {return true;};

        auto get_head() const -> const Point<T> & {return head_;}
        auto get_tail() const -> const Point<T> & {return tail_;}

    protected:
        Point<T> head_, tail_;
        Sint32 step_size_, current_step_{0}, tail_step_{0};

        auto set(const Point<T> &start_point, const Sint32 step_size, const Sint32 trail_size) -> void {
            head_ = {start_point};
            tail_ = {start_point};
            step_size_ = {step_size};
            tail_step_ = {-trail_size};
        }
    };

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
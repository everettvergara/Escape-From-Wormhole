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

        virtual auto next() -> bool {
            return true;
        };

        auto get_head() const -> const Point<T> & {return head_;}
        auto get_tail() const -> const Point<T> & {return tail_;}

    protected:
        Point<T> head_, tail_;
        Sint32 sz_steps_, tail_step_, head_step_;
        
        auto set(const Point<T> &start_point, const Sint32 sz_steps, const Sint32 sz_trail) -> void {
            head_ = {start_point};
            tail_ = {start_point};
            sz_steps_ = {sz_steps};
            tail_step_ = {-sz_trail};
            head_step_ = {0};
        }
    };
}

#endif
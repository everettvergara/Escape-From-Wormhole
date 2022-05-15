#ifndef _POINTMOTION_HPP_
#define _POINTMOTION_HPP_

#include "Point.hpp"

namespace g80 {

    template<typename T>
    class PointMotion {
    public:
        PointMotion(Sint32 body_size) : body_size_(body_size) {}

        virtual auto reset() -> void;
        virtual auto next() -> void;
        virtual auto prev() -> void;

        auto get_head() const -> const Point<T> & {return head_;}
        auto get_tail() const -> const Point<T> & {return tail_;}

    private:
        Point<T> head_;
        Point<T> tail_;
        Sint32 body_size_;
    };
}

#endif
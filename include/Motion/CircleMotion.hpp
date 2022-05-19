#ifndef _CIRCLEMOTION_HPP_
#define _CIRCLEMOTION_HPP_

#include "PointMotion.hpp"
#include "TrigCache.hpp"

namespace g80 {

    // todo: remove pointmotion

    template<typename T>
    class CircleMotion : public PointMotion<T> {
    public:
        CircleMotion() : PointMotion<T>() {}
        ~CircleMotion() {}

        auto circle_motion_set(
            const Point<T> &p, 
            const Sint32 radius,
            const Sint32 sz_steps,
            const Sint32 sz_trail,
            const Sint32 start_ix, 
            const Sint32 end_ix, 
            const CosCache<T> &cosine_cache,
            const SinCache<T> &sine_cache) : 
                center_(p){

            head_ = Point<T>{center_.x + radius * cosine_cache[start_ix], center_.y + radius * sine_cache[start_ix]};
            tail_ = {head_};
            sz_steps_ = {sz_steps};
            tail_step_ = {-sz_trail};
            head_step_ = {0};
          
            inc_ = 1.0f * (end_angle - start_angle) / sz_steps;
        }

        auto next(const CosCache<T> &cosine_cache, const SinCache<T> &sine_cache) -> bool {
            // if (this->tail_step_ == this->sz_steps_) return false;

            // if (this->head_step_ < this->sz_steps_) {
            //     this->head_ += inc_;
            //     ++this->head_step_;
            // }

            // if (this->tail_step_++ >= 0)
            //     this->tail_ += inc_;

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
        Point<T> center_;
        float inc_;
    };
}

#endif
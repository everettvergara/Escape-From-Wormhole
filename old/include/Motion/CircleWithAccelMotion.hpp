#ifndef _CIRCLEWITHACCELMOTION_HPP_
#define _CIRCLEWITHACCELMOTION_HPP_

#include "Point.hpp"
#include "TrigCache.hpp"

namespace g80 {

    // todo: remove pointmotion

    template<typename T>
    class CircleWithAccelMotion {
    public:
        CircleWithAccelMotion() {}
        ~CircleWithAccelMotion() {}

        auto circle_with_accel_motion_set(
            const Point<T> &p, 
            const Sint32 radius,
            const Sint32 sz_steps,
            const Sint32 sz_trail,
            const Sint32 start_ix, 
            const Sint32 end_ix, 
            const CosCache<T> &cosine_cache,
            const SinCache<T> &sine_cache) {

            center_ = {p};
            radius_ = {radius};

            head_ = Point<T>{center_.x + radius * cosine_cache[start_ix], center_.y + radius * sine_cache[start_ix]};
            tail_ = {head_};
            sz_steps_ = {sz_steps};
            tail_step_ = {-sz_trail};
            head_step_ = {0};
            
            k_ = 1.0f * (end_ix - start_ix) / (sz_steps * sz_steps);
        }

        auto next(const CosCache<T> &cosine_cache, const SinCache<T> &sine_cache) -> bool {
            if (this->tail_step_ == this->sz_steps_) return false;

            float size = cosine_cache.get_size();

            if (this->head_step_ < this->sz_steps_) {
                
                float angle = k_ * (head_step_ * head_step_);

                if (angle >= size) angle = angle - size;
                else if (angle < 0.0f) angle = size + angle;

                this->head_.x = center_.x + radius_ * cosine_cache[static_cast<Sint32>(angle)];
                this->head_.y = center_.y + radius_ * sine_cache[static_cast<Sint32>(angle)];

                ++this->head_step_;
            }

            if (this->tail_step_++ >= 0) {
                float angle = k_ * (tail_step_ * tail_step_);

                if (angle >= size) angle = angle - size;
                else if (angle < 0.0f) angle = size + angle;

                this->tail_.x = center_.x + radius_ * cosine_cache[static_cast<Sint32>(angle)];
                this->tail_.y = center_.y + radius_ * sine_cache[static_cast<Sint32>(angle)];
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
        Point<T> center_;
        Sint32 radius_;
        T k_;
    };
}

#endif
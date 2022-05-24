#ifndef LISSAJOUS_MOTION_HPP
#define LISSAJOUS_MOTION_HPP

#include "Point.hpp"
#include "TrigCache.hpp"

namespace g80 {

    template<typename T>
    struct Lissajous {
        Point<T> p;
        T radius_x, radius_y;
        T angle_x, angle_y;
        T angle_x_end, angle_y_end;
    };

    template<typename T>
    class LissajousMotion {
    public:
        LissajousMotion() {}
        ~LissajousMotion() {}

        auto lissajous_motion_set(
            const Lissajous &lisa,
            const Sint32 sz_steps,
            const Sint32 sz_trail,
            const CosCache<T> &cosine_cache,
            const SinCache<T> &sine_cache) : 
            lisa_(lisa) {

            head_ = Point<T>{
                lisa_.p.x + lisa_.radius_x * cosine_cache[angle_x], 
                lisa_.p.y + lisa_.radius_y * sine_cache[angle_y]};

            tail_ = {head_};
            sz_steps_ = {sz_steps};
            tail_step_ = {-sz_trail};
            head_step_ = {0};

            inc_x_ = (lisa_.angle_x_end - lisa_.angle_x) / sz_steps;
            inc_y_ = (lisa_.angle_y_end - lisa_.angle_y) / sz_steps;
        }

        auto next(const CosCache<T> &cosine_cache, const SinCache<T> &sine_cache) -> bool {
            if (this->tail_step_ == this->sz_steps_) return false;

            float size = cosine_cache.get_size();

            if (this->head_step_ < this->sz_steps_) {
                lisa_.angle_x += inc_x_;
                lisa_.angle_y += inc_y_;

                if (lisa_.angle_x >= size) lisa_.angle_x = lisa_.angle_x - size;
                else if (lisa_.angle_x < 0.0f) lisa_.angle_x = size + lisa_.angle_x;
                if (lisa_.angle_y >= size) lisa_.angle_y = lisa_.angle_y - size;
                else if (lisa_.angle_y < 0.0f) lisa_.angle_y = size + lisa_.angle_y;

                this->head_.x = lisa.p.x + lisa.radius_x * cosine_cache[static_cast<Sint32>(head_angle_)];
                this->head_.y = lisa.p.y + lisa.radius_y * sine_cache[static_cast<Sint32>(head_angle_)];

                ++this->head_step_;
            }

            // if (this->tail_step_++ >= 0) {
            //     tail_angle_ += inc_;

            //     if (tail_angle_ >= size) tail_angle_ = tail_angle_ - size;
            //     else if (tail_angle_ < 0.0f) tail_angle_ = size + tail_angle_;

            //     this->tail_.x = center_.x + radius_ * cosine_cache[static_cast<Sint32>(tail_angle_)];
            //     this->tail_.y = center_.y + radius_ * sine_cache[static_cast<Sint32>(tail_angle_)];
            // }

            return true;
        }

        // inline auto get_head() const -> const Point<T> & {return head_;}
        // inline auto get_tail() const -> const Point<T> & {return tail_;}
        // inline auto get_head_step() const -> Sint32 {return head_step_;}
        // inline auto get_tail_step() const -> Sint32 {return tail_step_;}
        // inline auto get_size_of_step() const -> Sint32 {return sz_steps_;}


    private:
        Lissajous lisa_;
        Point<T> head_, tail_;
        Sint32 sz_steps_, tail_step_, head_step_;
        T inc_x_, inc_y_;
    };
}

#endif
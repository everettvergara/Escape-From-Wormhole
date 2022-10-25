#pragma once

#include <cstdint>
#include <cassert>
#include <tuple>


namespace g80::video {

    template<typename T>
    class base_point {
        static_assert(
            std::is_same_v<T, int8_t> || std::is_same_v<T, uint8_t> || 
            std::is_same_v<T, int16_t> || std::is_same_v<T, uint16_t> || 
            std::is_same_v<T, int32_t> || std::is_same_v<T, uint32_t> || 
            std::is_same_v<T, int64_t> || std::is_same_v<T, uint64_t> || 
            std::is_same_v<T, float> || std::is_same_v<T, double> || 
            std::is_same_v<T, long double>, "Type not allowed as point"); 

    private:
        T x_, y_;

    public:

        base_point(T x, T y) : 
            x_(x), y_(y) {
        }

        // template<typename U>
        // auto const & () -> base_point<U> {
        //     return base_point<U>()
        // }

        // template<typename U>
        // friend base_point(const base_point<U> &r) : 
        //     x_(static_cast<T>(r.x_)), y_(static_cast<T>(r.y_)) {
        // }

        inline auto set_x(T x) -> void {
            x_ = {x};
        }

        inline auto set_y(T y) -> void {
            y_ = {y};
        }

        inline auto set_xy(T x, T y) -> void {
            set_x(x);
            set_y(y);
        }

        inline auto get_x() -> T {
            return x_;
        }
        
        inline auto get_y() -> T {
            return y_;
        }

        inline auto get_xy() -> std::tuple<T, T> {
            return {get_x(), get_y()};
        }

    };
}
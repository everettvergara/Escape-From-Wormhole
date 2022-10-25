#pragma once

#include <cstdint>
#include <cassert>
#include <tuple>


namespace g80::video {

    template<typename T>
    class base_point {

        static_assert(
            std::is_same_v<T, int8_t>::value || std::is_same_v<T, uint8_t>::value || 
            std::is_same_v<T, int16_t>::value || std::is_same_v<T, uint16_t>::value || 
            std::is_same_v<T, int32_t>::value || std::is_same_v<T, uint32_t>::value || 
            std::is_same_v<T, int64_t>::value || std::is_same_v<T, uint64_t>::value || 
            std::is_same_v<T, float>::value || std::is_same_v<T, double>::value || 
            std::is_same_v<T, long double>::value, "Type not allowed as point"); 

    private:
        T x_, y_;

    public:

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
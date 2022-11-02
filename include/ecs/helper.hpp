#pragma once

#include <type_traits>

namespace g80::ecs {

    class entity;
    class component;

    template<typename E>
    auto get_next_component_type_id() -> size_t {
        static_assert(std::is_base_of_v<entity, E>, "Type must be derived from entity!");
        static size_t next_component_type_id{0};
        return next_component_type_id++;
    }

    template<typename E, typename C> 
    auto get_component_type_id() -> size_t {
        static_assert(std::is_base_of_v<entity, E>, "Type must be derived from entity!");
        static_assert(std::is_base_of_v<component, C>, "Type must be derived from component!");

        static size_t component_type_id{get_next_component_type_id<E>()};
        return component_type_id;
    }

}
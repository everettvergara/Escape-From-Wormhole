#pragma once

namespace g80::ecs {

    template<typename E>
    auto get_next_component_type_id() -> size_t {
        static size_t next_component_type_id{0};
        return next_component_type_id++;
    }

    template<typename E, typename C> 
    auto get_component_type_id() -> size_t {
        static size_t component_type_id{get_next_component_type_id<E>()};
        return component_type_id;
    }


}
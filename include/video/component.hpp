#pragma once 

#include <memory>

namespace g80::game {


    auto get_next_component_type_id() -> size_t {
        static size_t next_component_type_id{0};
        return next_component_type_id++;
    }
    
    template<typename T> auto get_component_id() -> size_t {
        static size_t component_type_id{get_next_component_type_id()};
        return component_type_id;
    }

    class component {



    };

}
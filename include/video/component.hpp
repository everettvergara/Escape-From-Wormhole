#pragma once 

#include <memory>

namespace g80::game {


    auto get_next_component_type_id() -> size_t {
        static size_t next_component_type_id{0};
        return next_component_type_id++;
    }
    
    template<typename T> auto get_component_type_id() -> size_t {
        static size_t component_type_id{get_next_component_type_id()};
        return component_type_id;
    }

    class entity;

    class component {
    private:
        entity *entity_;
    public:
        component(entity *e) : entity_(e) {}
        virtual void init() = 0;
        virtual void update() = 0;
        virtual void render() = 0;
        virtual ~component() = 0;
    };

}
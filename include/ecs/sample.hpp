#pragma once

#include "ecs/entity.hpp"
#include "ecs/component.hpp"

namespace g80::ecs {

    class hp : public component {
    private:
        size_t current_;
        size_t max_;
    public:
        hp(entity *e, size_t def_hp) : component(e), current_(def_hp), max_(def_hp) {}
        auto init() -> void override {}
        auto update() -> void override {}
        auto render() -> void override {}
    };

    class strength : public component {
    public:
        strength(entity *e) : component(e) {}
        auto init() -> void override {}
        auto update() -> void override {}
        auto render() -> void override {}        
    };

    class power : public component {
    public:
        power(entity *e) : component(e) {}
        auto init() -> void override {}
        auto update() -> void override {}
        auto render() -> void override {}
    };


    class player : public entity {
    private:
    public:
        player() {
            entity::add_component_type<player, hp>(this, 100UL);
            entity::add_component_type<player, strength>(this);
            entity::add_component_type<player, power>(this);
        }
    };

    class enemy : public entity {
    private:
    public:
        enemy() {}
    };    

}
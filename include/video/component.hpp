#pragma once 


#include <memory>
#include <vector>

namespace g80::game {

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


    class entity {
    private:
        std::vector<std::unique_ptr<component>> components_;
        std::vector<size_t> component_types_;

    public:

        // entity() {}
        virtual ~entity() {}
        virtual auto init() -> void {for(auto &c : components_) c->init();}
        virtual auto update() -> void {for(auto &c : components_) c->update();}
        virtual auto render() -> void {for(auto &c : components_) c->render();}

        // template<typename E, typename C, typename ...A> 
        // auto add_component_type(A &&...a) -> C& {
        //     auto &p = components_.emplace_back(make_unique<C>(this, std::forward<A>(a)...));
        //     component_types_.emplace_back();
        // }
    };

    class hp : public component {
    public:
        hp(entity *e) : component(e) {}
    };

    class strength : public component {
    public:
        strength(entity *e) : component(e) {}
    };

    class power : public component {
    public:
        power(entity *e) : component(e) {}
    };


    class player : public entity {
    private:
    public:
        player() {}
    };

    class enemy : public entity {
    private:
    public:
        enemy() {}
    };    
}
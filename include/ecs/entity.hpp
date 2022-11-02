#pragma once 


#include <memory>
#include <vector>
#include "helper.hpp"
#include "component.hpp"

namespace g80::ecs {

    class entity {

    // Helper functions intended to be called in the 
    // init / constructor of entities
    protected:
        template<typename E>
        static auto get_next_component_type_id() -> size_t {
            static_assert(std::is_base_of_v<entity, E>, "Type must be derived from entity!");
            static size_t next_component_type_id{0};
            return next_component_type_id++;
        }

        template<typename E, typename C> 
        static auto get_component_type_id() -> size_t {
            static_assert(std::is_base_of_v<entity, E>, "Type must be derived from entity!");
            static_assert(std::is_base_of_v<component, C>, "Type must be derived from component!");
            static size_t component_type_id{get_next_component_type_id<E>()};
            return component_type_id;
        }

        template<typename E, typename C, typename ...A> 
        static auto add_component_type(E *e, A &&...a) -> C * {
            auto cid = get_component_type_id<E, C>();
            if(cid != e->get_components().size()) return nullptr;
            auto &c = e->get_components().emplace_back(std::make_unique<C>(e, std::forward<A>(a)...));
            return dynamic_cast<C *>(c.get());
        }    

        template<typename E, typename C>
        inline auto get_component_type(E *e) -> C * {
            return dynamic_cast<C *>(&(*e->get_components().at(get_component_type_id<E, C>())));
        }

    private:
        std::vector<std::unique_ptr<component>> components_;
    public:
        entity() = default;
        entity(const entity &) = delete;
        entity(entity &&) = delete;
        auto operator=(const entity &) -> entity & = delete;
        auto operator=(entity &&) -> entity & = delete;
        virtual ~entity() = default;
        virtual auto init() -> void {for(auto &c : components_) c->init();}
        virtual auto update() -> void {for(auto &c : components_) c->update();}
        virtual auto render() -> void {for(auto &c : components_) c->render();}

        inline auto get_components() -> std::vector<std::unique_ptr<component>> & {
            return components_;
        }


    };


}
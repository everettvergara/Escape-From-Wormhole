#pragma once 


#include <memory>
#include <vector>

namespace g80::game {


    auto get_next_component_type_id() -> size_t {
        static size_t next_component_type_id{0};
        return next_component_type_id++;
    }
    
    template<typename T> 
    auto get_component_type_id() -> size_t {
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

    class entity {
    private:
        std::vector<std::unique_ptr<component>> components_;
        std::vector<size_t> component_types_;
    public:
        entity() {
            // reserve components_.
            // add_component_type
        }

        template<typename T, typename ...A> 
        auto add_component_type(A &&...a) -> T& {
            auto &p = components_.emplace_back(make_unique<T>(this, std::forward<A>(a)...));
            component_types_.emplace_back();
        }
    };

}
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
        virtual ~component() = default;
    };


    class entity {
    private:
        std::vector<std::unique_ptr<component>> components_;
        std::vector<size_t> component_types_;

    protected:
        template<typename E, typename C, typename ...A> 
        auto add_component_type(E *e, A &&...a) -> C * {
            auto cid = get_component_type_id<E, C>();
            if(cid != components_.size()) return nullptr;
            auto &c = components_.emplace_back(std::make_unique<C>(e, std::forward<A>(a)...));
            return dynamic_cast<C *>(c.get());
        }

    public:

        // entity() {}
        virtual ~entity() {}
        virtual auto init() -> void {for(auto &c : components_) c->init();}
        virtual auto update() -> void {for(auto &c : components_) c->update();}
        virtual auto render() -> void {for(auto &c : components_) c->render();}

        inline auto get_components() -> std::vector<std::unique_ptr<component>> &{
            return components_;
        }

        template<typename E, typename C>
        inline auto get_component_type() -> C * {
            return dynamic_cast<C *>(components_[get_component_type_id<E, C>()]);
        }

    };

    class hp : public component {
    public:
        hp(entity *e) : component(e) {}
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
            add_component_type<player, hp>(this);
            add_component_type<player, strength>(this);
            add_component_type<player, power>(this);
        }
    };

    class enemy : public entity {
    private:
    public:
        enemy() {}
    };    

}
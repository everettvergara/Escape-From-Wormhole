#pragma once 

namespace g80::ecs {
    
    class entity;

    class component {
    private:
        entity *entity_;
    public:
        component(entity *e) : entity_(e) {}
        component(const component &) = delete;
        component(component &&) = delete;
        auto operator=(const component &) -> entity & = delete;
        auto operator=(component &&) -> entity & = delete;
        virtual ~component() = default;

        virtual void init() {};
        virtual void render() {};
        virtual void update() {};
    };

}
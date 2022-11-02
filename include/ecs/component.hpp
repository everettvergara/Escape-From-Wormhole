#pragma once 

namespace g80::ecs {
    
    class entity;

    class component {
    private:
        entity *entity_;
    public:
        component(entity *e) : entity_(e) {}
        virtual void init() = default;
        virtual void render() = default;
        virtual void update() = default;
        virtual ~component() = default;
    };

}
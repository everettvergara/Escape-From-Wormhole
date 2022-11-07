#include <iostream>
#include <SDL.h>
#define GFX_SAFE_MODE
#include "game/engine/config.hpp"
#include "game/worm/demo.hpp"


// #include <vector>
// #include <memory>
// #include "ecs/sample.hpp"

auto main(int argc, char *argv[]) -> int {

    using namespace g80::game::worm;
    video::init();
    config c{"Hello World"};
    demo worm;
    worm.create_window(c);
    worm.run(c.MSPF);
    video::quit();


    // ECS Test
    // ---+
    // using namespace g80::ecs;
    // std::vector<std::unique_ptr<entity>> game_objs;
    // game_objs.reserve(100);
    // auto &p = game_objs.emplace_back(std::make_unique<player>());

    return 0;
}

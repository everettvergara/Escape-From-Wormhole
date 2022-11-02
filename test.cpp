#include <iostream>
#include <SDL.h>
#include "video/config.hpp"
#include "video/video.hpp"


#include <memory>
#include "ecs/sample.hpp"

auto main(int argc, char *argv[]) -> int {

    // using namespace g80::video;
    // video::init();
    // video worm;
    // video::quit();

    using namespace g80::ecs;

    std::unique_ptr<entity> game_obj {std::make_unique<player>()};
    return 0;
}

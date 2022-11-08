#include "game/engine/config.hpp"
#include "game/worm/demo.hpp"

auto main(int argc, char *argv[]) -> int {

    using namespace g80::game::worm;
    video::init();
    config c{"Hello World"};
    demo worm;
    worm.create_window(c);
    worm.run(c.MSPF);
    video::quit();

    return 0;
}

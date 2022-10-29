#include <iostream>
#include "video/video.hpp"

auto main(int argc, char *argv[]) -> int {

    using namespace g80::video;
    video efw;

    video::init();

    video::quit();

    return 0;
}
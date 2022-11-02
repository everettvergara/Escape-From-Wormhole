#include <iostream>
#include <SDL.h>
#include "video/config.hpp"
#include "video/video.hpp"


#include <memory>
#include "video/component.hpp"

auto main(int argc, char *argv[]) -> int {

    // using namespace g80::video;
    // video::init();
    // video worm;
    // video::quit();

    using namespace g80::game;

    std::unique_ptr<entity> game_obj {std::make_unique<player>()};

    // std::cout << "player_hp_id: " << get_component_type_id<player, hp>() << "\n";
    // std::cout << "player_strength_id: " << get_component_type_id<player, strength>() << "\n";
    // std::cout << "player_power_id: " << get_component_type_id<player, power>() << "\n";
    // std::cout << "enemy_hp_id: " << get_component_type_id<enemy, hp>() << "\n";
    // std::cout << "enemy_power_id: " << get_component_type_id<enemy, power>() << "\n";
    // std::cout << "enemy_strength_id: " << get_component_type_id<enemy, strength>() << "\n";

    // add_component_type<entity, hp>(*p);

    game_obj->add_component_type<player, hp>(dynamic_cast<player *>(&*game_obj));

    return 0;
}

#include "tdd/ts_scenario.hpp"
#include "tdd/process.hpp"

auto main() -> int {

    using namespace g80::worm::tdd;

    process proc(L"TDD Prelim Check");
    proc.add_scenario(std::make_unique<ts_scenario>(L"TDD Library Check"));
    proc.run();

    return 0;
}
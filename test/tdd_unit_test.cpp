#include <cstdint>
#include "video/ts_base_point.hpp"
#include "tdd/process.hpp"

auto main() -> int {

    using namespace g80::worm::tdd;

    process proc(L"TDD Unit Test");
    proc.add_scenario(std::make_unique<ts_base_point<int64_t>>(L"Class: base_point<int64_t> check"));
    // proc.add_scenario(std::make_unique<ts_base_point<int32_t>>(L"Class: base_point<int32_t> check"));
    // proc.add_scenario(std::make_unique<ts_base_point<uint64_t>>(L"Class: base_point<uint64_t> check"));
    // proc.add_scenario(std::make_unique<ts_base_point<uint32_t>>(L"Class: base_point<uint32_t> check"));
    // proc.add_scenario(std::make_unique<ts_base_point<float>>(L"Class: base_point<float> check"));
    // proc.add_scenario(std::make_unique<ts_base_point<double>>(L"Class: base_point<double> check"));
    // proc.add_scenario(std::make_unique<ts_base_point<long double>>(L"Class: base_point<long double> check"));
    proc.run();

    return 0;
}
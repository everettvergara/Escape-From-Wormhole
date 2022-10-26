#pragma once

#include "scenario.hpp"
#include "script.hpp"

namespace g80::worm::tdd {

    using namespace g80::tdd;

    class ts_scenario : public scenario {
    private:

        auto always_true() -> bool {return true;}
        auto always_false() -> bool {return false == false;}

    public:

        ts_scenario(const wchar_t *name) : scenario(name) {
            add_script(script(L"Always True", std::bind(&ts_scenario::always_true, this)));
        }
    };
}
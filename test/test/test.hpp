#pragma once

#include "../../../include/test/scenario.hpp"
#include "../../../include/test/script.hpp"

namespace g80::worm::tdd {
    class test : public g80::test::scenario {
    private:

        auto always_true() -> bool {return true;}
        auto always_false() -> bool {return false == false;}

    public:

        test(const wchar_t *name) : g80::test::scenario(name) {
            add_script(g80::test::script(L"Always True", std::bind(&test::always_true, this)));
        }
    };
}
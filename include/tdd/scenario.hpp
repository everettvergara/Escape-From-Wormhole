#pragma once

#include <functional>
#include <vector>
#include "script.hpp"

namespace g80::tdd {
    class scenario {
    private:
        const wchar_t       *name_;
        std::vector<script> scripts_;

    protected:
        auto add_script(script &&s) -> void {scripts_.emplace_back(std::move(s));}

    public:
        scenario(const wchar_t *name) : name_(name) {}
        virtual ~scenario() = default;
        inline auto get_name() -> const wchar_t * {return name_;}
        inline auto get_scripts() -> const std::vector<script> & {return scripts_;}
    };
}
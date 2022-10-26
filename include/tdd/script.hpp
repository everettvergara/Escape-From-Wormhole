#pragma once

#include <functional>

namespace g80::tdd {
    struct script {
        const wchar_t                   *name;
        std::function<auto () -> bool>  fn;

        script(const wchar_t *n, std::function<auto () -> bool> &&f) : name(n), fn(std::move(f)) {}
        script(const script &r) : name(r.name), fn(r.fn) {}
        script(script &&r) : name(r.name), fn(std::move(r.fn)) {}
        auto operator=(const script &r) -> script & = delete;
        auto operator=(script &&r) -> script & = delete;
    };
}
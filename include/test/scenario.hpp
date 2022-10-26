#pragma once

#include <functional>
#include <vector>

namespace g80::test {

    struct script {
        const wchar_t                   *name;
        std::function<auto () -> bool>  fn;
    };

    class scenario {
    
    private:
        const wchar_t       *name_;
        std::vector<script> scripts_;

    public:
        scenario(const wchar_t *name) : name_(name) {}
        virtual ~scenario() = default;
        inline auto get_name() -> const wchar_t * {return name_;}
        inline auto get_scripts() -> const std::vector<script> & {return scripts_;}
    };
}
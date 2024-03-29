#pragma once


#include <memory>
#include <vector>
#include <iostream>
#include <chrono>
#include <iomanip>
#include "scenario.hpp"
#include "common.hpp"
#include "console/color.hpp"

namespace g80::tdd {

    class process {
    private:
        const wchar_t                           *name_;
        std::vector<std::unique_ptr<scenario>>  scenarios_;

    public:
        process(const wchar_t *name) : name_(name) {}
        inline auto get_name() -> const wchar_t * {return name_;}
        inline auto get_scenarios() -> const std::vector<std::unique_ptr<scenario>> & {return scenarios_;}
        auto add_scenario(std::unique_ptr<scenario> &&s) -> void {scenarios_.emplace_back(std::move(s));}
        
        auto run() -> std::tuple<size_t, size_t> {
            std::wcout << "\nTesting " << name_ << " - {" << scenarios_.size() << " scenario/s}\n";

            size_t ototal{0}, ptotal{0}, no{1};
            for(auto &scenario : scenarios_) {
                std::wcout << "\n[" << no++ << "/" << scenarios_.size() << "] " << scenario->get_name() << " - {" << scenario->get_scripts().size() << " script/s}" << std::endl;
                ototal += scenario->get_scripts().size();
                for(auto &script : scenario->get_scripts()) {
                    auto start{std::chrono::high_resolution_clock::now()};
                    auto passed = script.fn();
                    auto elapsed{std::chrono::high_resolution_clock::now() - start};
                    ptotal += passed;
                    std::wcout  << "[" << (passed ? PASSED_TEXT : FAILED_TEXT) << ":" 
                                << std::setw(10) << std::setfill(L' ') << std::right 
                                << elapsed.count()
                                << std::setw(0) << std::left << "ns] " << script.name << "" << std::endl;
                }
            }

            using namespace g80::console::color;
            std::wcout  << "\n\nResult Summary\n"
                        << "Passed: " << FORE_COLOR_GREEN << ptotal << RESET << "\n"
                        << "Failed: " << FORE_COLOR_RED << (ototal - ptotal) << RESET << "\n"
                        << "Total: " << ototal << "\n" << std::endl;

            return {ototal, ptotal};
        }        
    };
}
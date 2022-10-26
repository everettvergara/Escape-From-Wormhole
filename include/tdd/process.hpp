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
            std::wcout << "\nTesting " << name_ << "\n" << std::endl;

            size_t ototal{0}, ptotal{0}, no{1};
            for(auto &scenario : scenarios_) {
                std::wcout << "[" << no++ << "/" << scenarios_.size() << "] " << scenario->get_name() << std::endl;
                for(auto &script : scenario->get_scripts()) {
                    auto start{std::chrono::high_resolution_clock::now()};
                    auto passed = script.fn();
                    auto elapsed{std::chrono::high_resolution_clock::now() - start};
                    ptotal += passed;
                    std::wcout  << "[" << (passed ? PASSED_TEXT : FAILED_TEXT) << ":" 
                                << std::setw(10) << std::setfill(L' ') << std::right 
                                << elapsed.count()
                                << std::setw(0) << std::left << "ns] " << name_ << "." << std::endl;
                }
                ototal += scenarios_.size();
            }

            using namespace g80::console::color;
            std::wcout  << "\n\nResult Summary\n"
                        << FORE_COLOR_GREEN << std::left << std::setw(9) << "Passed" << RESET << ":" << FORE_COLOR_GREEN << std::setw(15) << std::right << ptotal << "\n"
                        << FORE_COLOR_RED << std::left << std::setw(9) << "Failed" << RESET << ":" << FORE_COLOR_RED << std::setw(15) << std::setfill(L' ') << std::right << ototal - ptotal << "\n"
                        << RESET << std::left << std::setw(9) << "Total" << ":" << std::setw(15) << std::setfill(L' ') << std::right << ototal << "\n" << std::endl;

            return {ototal, ptotal};
        }        
    };
}
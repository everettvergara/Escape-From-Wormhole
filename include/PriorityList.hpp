#ifndef PRIORITY_LIST_HPP
#define PRIORITY_LIST_HPP

#include <iostream>
#include <vector>

/*
    PriorityList pl(3, 5);
    pl.debug();
    pl.add(0, 0);
    pl.add(0, 2);
    pl.add(0, 4);
    
    auto group = 0;
    auto cur = pl.get_next_after(group);
    while (cur != pl.get_tail_group_ix(group)) {
        std::cout << pl.get_node_from_nix(cur) << "\n";
        cur = pl.get_next_after(cur);
    }

*/   
s
namespace g80 {

    class PriorityList {
    public:
        PriorityList(size_t sz_group, size_t sz_node) : 
            sz_group_(sz_group), sz_node_(sz_node) {

            size_t list_size = sz_group_ * 2 + sz_node_;
            next_.reserve(list_size);
            prev_.reserve(list_size);

            // Init Head
            auto tix = get_tail_group_ix(0);
            for (size_t i = 0; i < sz_group; ++i) {
                next_.emplace_back(tix + i);
                prev_.emplace_back(i);
            }
            
            // Init Tail
            for (size_t i = tix; i < tix + sz_group; ++i) {
                next_.emplace_back(i);
                prev_.emplace_back(i - tix);
            }

            // Init Nodes
            auto nix = get_node_ix(0);
            for (size_t i = nix; i < nix + sz_node; ++i) {
                next_.emplace_back(i);
                prev_.emplace_back(i);
            }
        }

        inline auto get_node_from_nix(const size_t nix) -> const size_t {return nix - (sz_group_ << 1);}

        inline auto get_next_after(const size_t nix) -> const size_t {return next_[nix];}
        inline auto get_tail_group_ix(const size_t group) -> const size_t {return sz_group_ + group;}
        inline auto get_node_ix(const size_t node) -> const size_t {return (sz_group_ << 1) + node;}
        inline auto is_node_connected(const size_t node) -> const bool {auto nix = get_node_ix(node); return next_[nix] != nix;}
        inline auto is_nix_connected(const size_t nix) -> const bool {return next_[nix] != nix;}


        inline auto add(const size_t gix, const size_t node) -> void {
            auto nix = get_node_ix(node);
            add_nix(gix, nix);
        }

        inline auto add_nix(const size_t gix, const size_t nix) -> void {
            if (is_nix_connected(nix)) del_nix(nix);
            next_[nix] = next_[gix];
            prev_[nix] = gix;
            prev_[next_[gix]] = nix;
            next_[gix] = nix;
        }

        inline auto del(const size_t node) -> void {
            auto nix = get_node_ix(node);
            del_nix(nix);
        }

        inline auto del_nix(const size_t nix) -> void {
            prev_[next_[nix]] = prev_[nix];
            next_[prev_[nix]] = next_[nix];
            next_[nix] = nix;
            prev_[nix] = nix;
        }

        auto debug() -> void {
            
            std::cout << "next_:\n";            
            for (size_t i = 0; i < next_.size(); ++i) std::cout << "\t" << i;
            std::cout << "\n";
            for (size_t i = 0; i < next_.size(); ++i) std::cout << "\t" << next_[i];

            std::cout << "\nprev_:\n";            
            for (size_t i = 0; i < prev_.size(); ++i) std::cout << "\t" << i;
            std::cout << "\n";
            for (size_t i = 0; i < prev_.size(); ++i) std::cout << "\t" << prev_[i];

            std::cout << "\n" << std::endl;
        }

    private:

        // How it works?
        //
        // list_[i] 10 nodes, 3 groups
        //
        //      0   1   2   3   4   5   6   7   8   9   10  11  12  13  14
        //      h0  h1  h2  t0  t1  t2  n0  n1  n2  n3  n4  n5  n6  n7  n8
        // n:   t0  t1  t2  t0  t1  t2  n0  n1  n2  n3  n4  n5  n6  n7  n8
        // p:   h0  h1  h2  h0  h1  h2  n0  n1  n2  n3  n4  n5  n6  n7  n8

        // add (h, n), n = groups + 1 + n
        //
        //  add(0, 0) h = 0, n = 6
        // 

        size_t sz_group_, sz_node_;
        std::vector<size_t> next_;
        std::vector<size_t> prev_;
    };
}

#endif 
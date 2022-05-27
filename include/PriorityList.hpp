#ifndef PRIORITY_LIST_HPP
#define PRIORITY_LIST_HPP

#include <iostream>
#include <vector>
#include <SDL.h>

namespace g80 {

    class PriorityList {
    public:
        PriorityList(size_t sz_group, size_t sz_node) : 
            sz_group_(sz_group), sz_node_(sz_node) {

            size_t list_size = sz_group_ * 2 + sz_node_;
            next_.reserve(list_size);
            prev_.reserve(list_size);

            // Init Head
            auto tix = get_tail_ix(0);
            for (size_t i = 0; i < sz_group; ++i) {
                next_.emplace_back(tix + i);
                prev_.emplace_back(tix);
            }
            
            // Init Tail
            for (size_t i = tix; i < tix + sz_group; ++i) {
                next_.emplace_back(i);
                prev_.emplace_back(i - tix);
            }
        }

        inline auto get_tail_ix(const size_t tail) -> const size_t {return sz_group_ + tail;}
        inline auto get_node_ix(const size_t node) -> const size_t {return (sz_group_ << 1) + node;}

        auto add(const size_t gix, const size_t node) -> void {
            auto nix = get_node_ix(node);

            //
            // n:    head --> new --> node --> tail <-            //
            // p: -> head <-- new <-- node <-- tail   
            // 

            // Add nix to head
            next_[nix] = next_[gix];
            prev_[nix] = gix;
            prev_[next_[gix]] = nix
            next_[gix] = nix;
        }

        auto del(size_t list_ix) -> void {
            //list_prev_[list_ix] = 
        }


        auto debug() -> void {
            
            // std::cout << "IXS_:\n";            
            // for (size_t i = 0; i < ixs_.size(); ++i) std::cout << "\t" << i;
            // std::cout << "\n";
            // for (size_t i = 0; i < ixs_.size(); ++i) std::cout << "\t" << ixs_[i];

            // std::cout << "\n";
            // std::cout << "LIST_:\n";            
            // for (size_t i = 0; i < list_.size(); ++i) std::cout << "\t" << i;
            // std::cout << "\n";
            // for (size_t i = 0; i < list_.size(); ++i) std::cout << "\t" << list_[i];

            // std::cout << "\n";
            // std::cout << "PREV_LIST_:\n";            
            // for (size_t i = 0; i < list_prev_.size(); ++i) std::cout << "\t" << i;
            // std::cout << "\n";
            // for (size_t i = 0; i < list_prev_.size(); ++i) std::cout << "\t" << list_prev_[i];

            // std::cout << "\n" << std::endl;
        }

    private:

        // How it works?
        //
        // list_[i] 10 nodes, 3 groups
        //
        //      0   1   2   3   4   5   6   7   8   9   10  11  12  13  14
        //      h0  h1  h2  t0  t1  t2  n0  n1  n2  n3  n4  n5  n6  n7  n8
        // n:   t0  t1  t2  t0  t1  t2  
        // p:   h0  h1  h2  h0  h1  h2

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
#ifndef PRIORITY_LIST_HPP
#define PRIORITY_LIST_HPP

#include <vector>
#include <SDL.h>

namespace g80 {

    class PriorityList {
    public:
        PriorityList(size_t max_ix, size_t max_list) : 
            max_ix_(max_ix),
            max_list_(max_list) {

            ixs_.reserve(max_ix + 1);
            list_.reserve(max_list_ + 1);
            list_prev_.reserve(max_list_ + 1);
            list_ix_.reserve(max_list_ + 1);

            for (size_t i = 0; i <= max_ix_; ++i) ixs_.emplace_back(max_list_);
            for (size_t i = 0; i <= max_list_; ++i) list_.emplace_back(max_list_);
            for (size_t i = 0; i <= max_list_; ++i) list_prev_.emplace_back(i);
            for (size_t i = 0; i <= max_list_; ++i) list_ix_.emplace_back(max_ix_);
        }

        auto add(size_t ix, size_t list_ix) -> void {
            list_[list_ix] = ixs_[ix];
            list_prev[ixs_[ix]] = list_ix;
            ixs_[ix] = list_ix;
            list_prev_[list_ix] = list_ix;
        }

    private:
        const size_t max_ix_, max_list_;
        
        // How it works?
        //
        // ixs[i]:
        //  0   1   2   3   4   5   IN
        //  |   LN  LN  LN  LN  LN  LN
        //  v
        //
        //  list[i]
        //  0   1   2   3   4   5   6   7   8   9   LN
        //  1-> 3 ----> 5 ----> LN  LN  LN  LN  LN  LN
        //          LN      LN
        //
        //  list_prev[i]
        //  0   0   2   1   4   3   6   7   8   9   LN
        //
        //
        //  list_ix[i]
        //  0   1   2   3   4   5   6   7   8   9   LN
        //  0   0   IN  0   IN  0   IN  IN  IN  IN  IN   
        //
        
        
        std::vector<size_t> ixs_;
        std::vector<size_t> list_;
        std::vector<size_t> list_prev_;
        // std::vector<size_t> list_ix_;
        
    };
}

#endif 
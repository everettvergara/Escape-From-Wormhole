#ifndef PRIORITY_LIST_HPP
#define PRIORITY_LIST_HPP

#include <vector>
#include <SDL.h>

namespace g80 {

    class PriorityList {
    public:
        PriorityList(size_t max_ixs) : max_ixs_(max_ixs) {

            for (size_t i = 0; i < max_ixs_; ++i) {

            }
        }

    private:
        const size_t max_ixs_;
        
        // How it works?
        //
        // ixs[i]:
        //  0   1   2   3   4   5   IN
        //  |
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
        
        
        const std::vector<size_t> ixs_;
        const std::vector<size_t> list_;
        const std::vector<size_t> list_prev_;
        const std::vector<size_t> list_ix_;
        
    };
}

#endif 
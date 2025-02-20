//
// Created by cchau on 2/18/2025.
//

#ifndef PLAYGROUND_HEAPUTIL_H
#define PLAYGROUND_HEAPUTIL_H

#include <vector>

class HeapUtil {
    /**
     * Returns the minimum possible total number of stones remaining
     * after applying k removal operations.
     *
     * @param piles The vector of piles, where piles[i] is the number
     *              of stones in the i-th pile.
     * @param k     The exact number of operations to apply.
     * @return      The sum of the piles after k operations.
     */
public:
    int minStoneSum(std::vector<int>& piles, int k);
};


#endif //PLAYGROUND_HEAPUTIL_H

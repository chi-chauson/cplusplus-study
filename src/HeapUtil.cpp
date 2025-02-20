//
// Created by cchau on 2/18/2025.
//

#include "HeapUtil.h"

#include <queue>
#include <cmath>

int HeapUtil::minStoneSum(std::vector<int> &piles, int k) {
    // Create a max-heap (default is max-heap for int in C++)
    std::priority_queue<int> maxHeap;

    // Push all pile values onto the max-heap
    for (int pile : piles) {
        maxHeap.push(pile);
    }

    // Perform k operations
    for (int i = 0; i < k; i++) {
        // Extract the largest pile
        int largestPile = maxHeap.top();
        maxHeap.pop();

        // Remove floor(largestPile / 2) stones
        largestPile = largestPile - (largestPile / 2);

        // Push the updated pile back into the heap
        maxHeap.push(largestPile);
    }

    // Compute the total number of stones left
    int totalStones = 0;
    while (!maxHeap.empty()) {
        totalStones += maxHeap.top();
        maxHeap.pop();
    }

    return totalStones;
}

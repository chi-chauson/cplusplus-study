//
// Created by cchau on 12/25/2024.
//

#ifndef PLAYGROUND_PREFIXSUM_H
#define PLAYGROUND_PREFIXSUM_H

#include <vector>

class PrefixSum {
public:
    std::vector<int> runningSum(const std::vector<int>& nums);
    int minStartValue(std::vector<int>& nums);
    std::vector<int> getAverages(std::vector<int>& nums, int k);
};


#endif //PLAYGROUND_PREFIXSUM_H

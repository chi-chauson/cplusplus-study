//
// Created by cchau on 12/25/2024.
//

#include "PrefixSum.h"

std::vector<int> PrefixSum::runningSum(const std::vector<int> &nums) {
    std::vector<int> sums(nums.size());
    sums[0] = nums[0];

    for (size_t i = 1; i < nums.size(); ++i) {
        sums[i] = sums[i - 1] + nums[i];
    }

    return sums;
}

int PrefixSum::minStartValue(std::vector<int> &nums) {
    std::vector<int> prefixSums(nums.size(), 0);
    prefixSums[0] = nums[0];
    int min_sum = std::min(0, prefixSums[0]);
    for (size_t i = 1; i < nums.size(); ++i) {
        prefixSums[i] = prefixSums[i - 1] + nums[i];
        if (prefixSums[i] < min_sum) {
            min_sum = prefixSums[i];
        }
    }
    return 1 - min_sum;
}

std::vector<int> PrefixSum::getAverages(std::vector<int> &nums, int k) {
    int n = nums.size();
    std::vector<int> outputs(n, -1); // Initialize all elements to -1

    if (k == 0) {
        // If k is 0, the average is the element itself
        return nums;
    }

    // Compute prefix sums
    std::vector<long long> prefix(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        prefix[i + 1] = prefix[i] + static_cast<long long>(nums[i]);
    }

    // Iterate through each index to compute the k-radius average
    for (int i = 0; i < n; ++i) {
        int left = i - k;
        int right = i + k;
        if (left >= 0 && right < n) {
            long long sum = prefix[right + 1] - prefix[left];
            int average = static_cast<int>(sum / (2L * k + 1));
            outputs[i] = average;
        }
    }

    return outputs;
}

//
// Created by cchau on 12/29/2024.
//

#include <unordered_map>
#include <stack>
#include "Monotonic.h"

std::vector<int> Monotonic::nextGreaterElement(std::vector<int> &nums1, std::vector<int> &nums2) {
    std::unordered_map<int, int> nextGreater;
    std::stack<int> stack;

    for (int num : nums2) {
        while (!stack.empty() && num > stack.top()) {
            nextGreater[stack.top()] = num;
            stack.pop();
        }
        stack.push(num);
    }

    std::vector<int> result(nums1.size());
    for (size_t i = 0; i < nums1.size(); ++i) {
        result[i] = nextGreater.count(nums1[i]) ? nextGreater[nums1[i]] : -1;
    }
    return result;
}

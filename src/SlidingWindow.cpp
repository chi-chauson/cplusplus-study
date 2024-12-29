//
// Created by cchau on 12/25/2024.
//
#include <limits>
#include "SlidingWindow.h"

double SlidingWindow::findMaxAverage(const std::vector<int> &nums, int k) {
    // Initialize pointers and variables
    int left = 0;
    double ans = std::numeric_limits<double>::lowest(); // Initialize to the smallest possible double
    double curr = 0.0; // Current window sum

    // Iterate over the array with the right pointer
    for (int right = 0; right < nums.size(); right++) {
        // Add the current element to the window sum
        curr += nums[right];

        // If the window size exceeds k, remove the leftmost element
        while (right - left + 1 > k) {
            curr -= nums[left];
            left++;
        }

        // When the window size is exactly k, update the maximum average
        if (right - left + 1 == k) {
            double currentAverage = curr / k;
            if (currentAverage > ans) {
                ans = currentAverage;
            }
        }
    }

    return ans;
}

int SlidingWindow::longestOnes(const std::vector<int> &nums, int k) {
    int left = 0;
    int maxLength = 0;
    int numOfZeros = 0;

    for (int right = 0; right < nums.size(); ++right) {
        if (nums[right] == 0) {
            numOfZeros++;
        }

        // Shrink the window from the left if number of zeros exceeds k
        while (numOfZeros > k) {
            if (nums[left] == 0) {
                numOfZeros--;
            }
            left++;
        }

        // Update the maximum window size
        maxLength = std::max(maxLength, right - left + 1);
    }

    return maxLength;
}

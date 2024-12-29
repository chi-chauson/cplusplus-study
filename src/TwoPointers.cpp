//
// Created by cchau on 12/24/2024.
//

#include "TwoPointers.h"

using namespace std;

void TwoPointers::reverseString(std::vector<char> &s) {
    if (s.empty()) {
        // Nothing to reverse for empty vector
        return;
    }

    int left = 0;
    int right = static_cast<int>(s.size()) - 1;

    while (left < right) {
        // Swap the characters at positions left and right
        char temp = s[left];
        s[left] = s[right];
        s[right] = temp;

        // Move towards the center
        left++;
        right--;
    }
}

vector<int> TwoPointers::sortedSquares(vector<int> &nums) {
    int n = nums.size();
    std::vector<int> result(n);

    int left = 0;
    int right = n - 1;
    int position = n - 1;

    while (left <= right) {
        int leftSquare = nums[left] * nums[left];
        int rightSquare = nums[right] * nums[right];

        if (leftSquare > rightSquare) {
            result[position] = leftSquare;
            left++;
        } else {
            result[position] = rightSquare;
            right--;
        }
        position--;
    }

    return result;
}

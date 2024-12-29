//
// Created by cchau on 12/26/2024.
//

#include "Hashing.h"
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

bool Hashing::checkIfPangram(const std::string &sentence) {
    if (sentence.empty() || sentence.length() < 26) {
        return false;
    }

    std::unordered_set<char> seenLetters;
    for (char c : sentence) {
        seenLetters.insert(c);
    }

    return seenLetters.size() == 26;
}

int Hashing::missingNumber(const std::vector<int> &nums) {
    std::unordered_set<int> numSet;
    for (int num : nums) {
        numSet.insert(num);
    }

    int n = nums.size();
    for (int i = 0; i <= n; ++i) {
        if (numSet.find(i) == numSet.end()) {
            return i;
        }
    }

    return -1; // Should not happen given the problem constraints
}

int Hashing::countElements(const std::vector<int> &arr) {
    std::unordered_set<int> numSet;
    for (int num : arr) {
        numSet.insert(num);
    }

    int count = 0;
    for (int num : arr) {
        if (numSet.count(num + 1)) { // Use count() for checking existence
            count++;
        }
    }

    return count;
}

int Hashing::largestUniqueNumber(const std::vector<int> &nums) {
    std::unordered_map<int, int> freq;

    // Count frequency of each element
    for (int num : nums) {
        freq[num]++;
    }

    int largestUnique = -1;
    // Find the largest number that appears exactly once
    for (const auto& [value, count] : freq) {
        if (count == 1 && value > largestUnique) {
            largestUnique = value;
        }
    }

    return largestUnique;
}

int Hashing::maxNumberOfBalloons(const std::string &text) {
    std::unordered_map<char, int> freq;

    // Count characters in text
    for (char c : text) {
        freq[c]++;
    }

    // Need to form "balloon"
    // b -> 1, a -> 1, l -> 2, o -> 2, n -> 1
    int countB = freq['b'];
    int countA = freq['a'];
    int countL = freq['l'];
    int countO = freq['o'];
    int countN = freq['n'];

    // The number of "balloon"s is limited by
    // min(
    //   countB,
    //   countA,
    //   countL/2,
    //   countO/2,
    //   countN
    // )
    int maxBalloons = std::min({
                                       countB,
                                       countA,
                                       countL / 2,
                                       countO / 2,
                                       countN
                               });

    return maxBalloons;
}

int Hashing::findMaxLength(const std::vector<int> &nums) {
    // Key: running sum, Value: first index of that sum
    std::unordered_map<int, int> sumIndexMap;
    // Initialize with sum = 0 at index = -1
    sumIndexMap[0] = -1;

    int runningSum = 0;
    int maxLength = 0;

    for (int i = 0; i < (int)nums.size(); i++) {
        // 0 => -1, 1 => +1
        if (nums[i] == 0) {
            runningSum -= 1;
        } else {
            runningSum += 1;
        }

        // If we've seen this sum before, check the subarray length
        if (sumIndexMap.find(runningSum) != sumIndexMap.end()) {
            int firstIndex = sumIndexMap[runningSum];
            int length = i - firstIndex;
            maxLength = std::max(maxLength, length);
        } else {
            // Otherwise store the current index for this sum
            sumIndexMap[runningSum] = i;
        }
    }

    return maxLength;
}

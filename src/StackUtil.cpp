//
// Created by cchau on 12/28/2024.
//

#include "StackUtil.h"
#include <sstream>
#include <deque>

std::string StackUtil::simplifyPath(const std::string &path) {
    if (path.empty()) {
        return "/";
    }

    std::deque<std::string> stack;
    std::stringstream ss(path);
    std::string token;

    while (std::getline(ss, token, '/')) {
        if (token == "." || token.empty()) {
            continue;
        } else if (token == "..") {
            if (!stack.empty()) {
                stack.pop_back();
            }
        } else {
            stack.push_back(token);
        }
    }

    std::string simplifiedPath;
    if (stack.empty()) {
        return "/";
    }

    while (!stack.empty()) {
        simplifiedPath += "/" + stack.front(); // Append instead of prepend
        stack.pop_front();
    }

    return simplifiedPath;
}

std::string StackUtil::makeGood(const std::string &s) {
    if (s.empty() || s.length() <= 1) {
        return s;
    }

    std::deque<char> deque;

    for (char c : s) {
        if (!deque.empty() && std::abs(deque.back() - c) == 32) {
            deque.pop_back();
        } else {
            deque.push_back(c);
        }
    }

    return std::string(deque.begin(), deque.end());
}

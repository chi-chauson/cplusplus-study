//
// Created by cchau on 2/15/2025.
//

#include "ImplicitGraph.h"

// --------------------
// openLock Implementation
// --------------------
int ImplicitGraph::openLock(const std::vector<std::string> &deadends, const std::string &target) {
    // If "0000" is itself a deadend, we cannot even start.
    std::unordered_set<std::string> seen(deadends.begin(), deadends.end());
    if (seen.find("0000") != seen.end()) {
        return -1;
    }

    // BFS setup
    std::queue<LockPair> queue;
    queue.push({"0000", 0});
    seen.insert("0000");

    // Standard BFS
    while (!queue.empty()) {
        auto [node, steps] = queue.front();
        queue.pop();

        // If we reach the target, return the number of steps
        if (node == target) {
            return steps;
        }

        // Check all neighbors (states one move away)
        for (const auto &nbr: neighbors(node)) {
            if (seen.find(nbr) == seen.end()) {
                seen.insert(nbr);
                queue.push({nbr, steps + 1});
            }
        }
    }

    // Target was not found
    return -1;
}

std::vector<std::string> ImplicitGraph::neighbors(const std::string &node) {
    std::vector<std::string> ans;
    // For each digit in the 4-digit code
    for (int i = 0; i < 4; ++i) {
        int digit = node[i] - '0';
        // Two possible moves: +1 or -1 (mod 10)
        for (int change: {-1, 1}) {
            int newDigit = (digit + change + 10) % 10;
            // Construct the new state
            std::string newState = node;
            newState[i] = static_cast<char>('0' + newDigit);
            ans.push_back(newState);
        }
    }
    return ans;
}

// --------------------
// calcEquation Implementation
// --------------------
std::vector<double> ImplicitGraph::calcEquation(const std::vector<std::vector<std::string>> &equations,
                                                const std::vector<double> &values,
                                                const std::vector<std::vector<std::string>> &queries) {
    // Build the graph based on the given equations
    for (size_t i = 0; i < equations.size(); ++i) {
        const std::string &numerator = equations[i][0];
        const std::string &denominator = equations[i][1];
        double val = values[i];

        // Insert into graph
        graph[numerator][denominator] = val;
        graph[denominator][numerator] = (val == 0.0 ? 0.0 : 1.0 / val);
    }

    // For each query, use DFS to find the ratio if possible
    std::vector<double> ans;
    ans.reserve(queries.size());
    for (const auto &q: queries) {
        ans.push_back(answerQuery(q[0], q[1]));
    }

    return ans;
}

double ImplicitGraph::answerQuery(const std::string &start, const std::string &end) {
    // If the start node isn't even in the graph, no info => -1
    if (graph.find(start) == graph.end()) {
        return -1.0;
    }

    // DFS stack (or could use recursion)
    std::stack<FactorPair> st;
    std::unordered_set<std::string> visited;

    st.push({start, 1.0});
    visited.insert(start);

    while (!st.empty()) {
        auto [node, ratio] = st.top();
        st.pop();

        // Found the target node
        if (node == end) {
            return ratio;
        }

        // Explore neighbors
        if (graph.find(node) != graph.end()) {
            for (const auto &[neighbor, weight]: graph[node]) {
                if (visited.find(neighbor) == visited.end()) {
                    visited.insert(neighbor);
                    st.push({neighbor, ratio * weight});
                }
            }
        }
    }

    // No path found
    return -1.0;
}
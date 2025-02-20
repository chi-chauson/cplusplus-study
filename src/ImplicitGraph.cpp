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

int ImplicitGraph::minMutation(const std::string &startGene, const std::string &endGene,
                               const std::vector <std::string> &bank) {
    // If start == end, no mutations are needed
    if (startGene == endGene) {
        return 0;
    }

    // Convert bank to set for O(1) lookups
    std::unordered_set<std::string> bankSet(bank.begin(), bank.end());

    // If endGene not in bank, no valid path (assuming endGene != startGene here)
    if (bankSet.find(endGene) == bankSet.end()) {
        return -1;
    }

    // Possible characters for each position
    static const std::vector<char> chars = {'A', 'C', 'G', 'T'};

    // Standard BFS
    std::queue<std::string> queue;
    queue.push(startGene);

    // Keep track of visited nodes to avoid revisiting
    std::unordered_set<std::string> visited;
    visited.insert(startGene);

    int mutations = 0; // BFS "level"

    while (!queue.empty()) {
        int size = static_cast<int>(queue.size());
        // Process the current level fully
        for (int i = 0; i < size; i++) {
            std::string current = queue.front();
            queue.pop();

            if (current == endGene) {
                return mutations;
            }

            // Try to mutate one character at a time
            for (int pos = 0; pos < (int)current.size(); pos++) {
                for (char c : chars) {
                    if (current[pos] == c) {
                        continue;
                    }
                    // Generate new gene
                    std::string mutated = current;
                    mutated[pos] = c;

                    // Check if it is valid and not visited
                    if (bankSet.find(mutated) != bankSet.end() &&
                        visited.find(mutated) == visited.end())
                    {
                        visited.insert(mutated);
                        queue.push(mutated);
                    }
                }
            }
        }
        // Increment mutation count after processing one BFS level
        mutations++;
    }

    // If we exit the loop, endGene was not reachable
    return -1;
}

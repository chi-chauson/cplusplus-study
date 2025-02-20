//
// Created by cchau on 2/15/2025.
//

#ifndef PLAYGROUND_IMPLICITGRAPH_H
#define PLAYGROUND_IMPLICITGRAPH_H


#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>

struct LockPair {
    std::string node;
    int steps;
};

struct FactorPair {
    std::string node;
    double ratio;
};

class ImplicitGraph {
public:
    // The core graph storage for calcEquation
    std::unordered_map<std::string, std::unordered_map<std::string, double>> graph;

    // Solves the "open lock" problem using BFS.
    // deadends: List of "deadend" states where you cannot proceed.
    // target: The lock combination you want to achieve.
    // returns: Minimum number of steps to reach target (or -1 if impossible).
    int openLock(const std::vector<std::string> &deadends, const std::string &target);

    // Calculates division results for queries like a / b using previously provided equations.
    // equations: Each inner vector has two strings [numerator, denominator].
    // values: The numeric ratios for each equation in `equations`.
    // queries: Each inner vector has two strings [numerator, denominator].
    // returns: Vector of results for each query, or -1 if no connection.
    std::vector<double> calcEquation(const std::vector<std::vector<std::string>> &equations,
                                     const std::vector<double> &values,
                                     const std::vector<std::vector<std::string>> &queries);

    int minMutation(const std::string& startGene,
                    const std::string& endGene,
                    const std::vector<std::string>& bank);

private:
    // Returns the neighbors of a given lock state.
    // For each of the 4 digits, you can move the wheel up or down by 1.
    std::vector<std::string> neighbors(const std::string &node);

    // Helper for calcEquation to answer a single query using DFS.
    // returns: The ratio from start to end, or -1 if no path.
    double answerQuery(const std::string &start, const std::string &end);
};


#endif //PLAYGROUND_IMPLICITGRAPH_H

//
// Created by cchau on 1/1/2025.
//
#include <unordered_map>
#include <stack>
#include "GraphUtil.h"

using namespace std;

bool GraphUtil::validPath(int n, const vector<vector<int>> &edges, int source, int destination) {
    if (source == destination) {
        return true;
    }

    // Build adjacency list using unordered_map
    unordered_map<int, vector<int>> graph;
    for (const auto& edge : edges) {
        int u = edge[0];
        int v = edge[1];
        graph[u].emplace_back(v);
        graph[v].emplace_back(u);
    }

    // Initialize visited vector
    vector<bool> visited(n, false);
    stack<int> stack;

    // Start DFS from source
    stack.push(source);
    visited[source] = true;

    while (!stack.empty()) {
        int current = stack.top();
        stack.pop();

        for (const int& neighbor : graph[current]) {
            if (neighbor == destination) {
                return true;
            }
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                stack.push(neighbor);
            }
        }
    }

    return false;
}

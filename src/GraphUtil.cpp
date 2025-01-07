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
    for (const auto &edge: edges) {
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

        for (const int &neighbor: graph[current]) {
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

int GraphUtil::numIslands(vector<std::vector<char>> &grid) {
    if (grid.empty() || grid[0].empty()) {
        return 0;
    }

    int numberOfIslands = 0;
    int rows = grid.size();
    int cols = grid[0].size();

    // Iterate through each cell in the grid
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            // If the cell is land ('1'), perform DFS to mark the entire island
            if (grid[row][col] == '1') {
                ++numberOfIslands;
                dfsIsland(grid, row, col, rows, cols);
            }
        }
    }

    return numberOfIslands;
}

/**
* Iterative Depth-First Search to mark all connected land cells starting from (startRow, startCol).
*
* @param grid      the 2D grid
* @param startRow  starting row index
* @param startCol  starting column index
* @param rows      total number of rows in the grid
* @param cols      total number of columns in the grid
*/

void GraphUtil::dfsIsland(std::vector<std::vector<char>> &grid, int startRow, int startCol, int rows, int cols) {
    // Define directions: up, down, left, right
    std::vector<std::pair<int, int>> directions = {
            {-1, 0}, // Up
            {1,  0},  // Down
            {0,  -1}, // Left
            {0,  1}   // Right
    };

    // Initialize stack with the starting cell
    std::stack<std::pair<int, int>> stack;
    stack.emplace(startRow, startCol);
    grid[startRow][startCol] = '0'; // Mark as visited

    while (!stack.empty()) {
        auto [currentRow, currentCol] = stack.top();
        stack.pop();

        // Explore all four adjacent directions
        for (const auto &direction: directions) {
            int newRow = currentRow + direction.first;
            int newCol = currentCol + direction.second;

            // Check boundaries and if the cell is land
            if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols && grid[newRow][newCol] == '1') {
                stack.emplace(newRow, newCol);
                grid[newRow][newCol] = '0'; // Mark as visited
            }
        }
    }
}

void GraphUtil::dfsCountComponents(int startNode, const std::vector<std::vector<int>> &adjacencyList, std::vector<bool> &visited) {
    std::stack<int> nodeStack;
    nodeStack.push(startNode);
    visited[startNode] = true;

    while (!nodeStack.empty()) {
        int currentNode = nodeStack.top();
        nodeStack.pop();

        for (const int& neighbor : adjacencyList[currentNode]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                nodeStack.push(neighbor);
            }
        }
    }
}

int GraphUtil::countComponents(int n, const std::vector<std::vector<int>> &edges) {
    // Handle edge case where there are no nodes
    if (n == 0) return 0;

    // Build the adjacency list
    std::vector<std::vector<int>> adjacencyList(n, std::vector<int>());
    for (const auto& edge : edges) {
        int u = edge[0];
        int v = edge[1];
        adjacencyList[u].push_back(v);
        adjacencyList[v].push_back(u);
    }

    // Initialize visited array
    std::vector<bool> visited(n, false);
    int connectedComponents = 0;

    // Iterate through all nodes
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            connectedComponents++;
            dfsCountComponents(i, adjacencyList, visited);
        }
    }

    return connectedComponents;
}

int GraphUtil::maxAreaOfIsland(vector<std::vector<int>> &grid) {
    if (grid.empty() || grid[0].empty()) return 0;

    int maxArea = 0;
    int rows = grid.size();
    int cols = grid[0].size();

    // Directions: up, down, left, right
    std::vector<std::pair<int, int>> directions = {
            {-1, 0}, {1, 0}, {0, -1}, {0, 1}
    };

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (grid[r][c] == 1) {
                int currentArea = 0;
                std::stack<std::pair<int, int>> stk;
                stk.push({r, c});
                grid[r][c] = 0; // Mark as visited

                while (!stk.empty()) {
                    auto [current_r, current_c] = stk.top();
                    stk.pop();
                    currentArea++;

                    for (const auto& dir : directions) {
                        int new_r = current_r + dir.first;
                        int new_c = current_c + dir.second;

                        if (new_r >= 0 && new_r < rows &&
                            new_c >= 0 && new_c < cols &&
                            grid[new_r][new_c] == 1) {
                            stk.push({new_r, new_c});
                            grid[new_r][new_c] = 0; // Mark as visited
                        }
                    }
                }

                maxArea = std::max(maxArea, currentArea);
            }
        }
    }

    return maxArea;
}

bool GraphUtil::isValid(int r, int c, int rows, int cols) {
    return (r >= 0 && r < rows && c >= 0 && c < cols);
}


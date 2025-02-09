//
// Created by cchau on 1/1/2025.
//
#include <unordered_map>
#include <stack>
#include <queue>
#include <array>
#include <utility>
#include <algorithm>
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

bool GraphUtil::isValid(int r, int c, int rows, int cols) const {
    return (r >= 0 && r < rows && c >= 0 && c < cols);
}

int GraphUtil::dfsReachableNodes(int current, const std::vector<std::vector<int>> &adj, const std::unordered_set<int> &restrictedSet,
                                 std::vector<bool> &visited) {
    // Mark the current node as visited
    visited[current] = true;

    // Initialize count with the current node
    int count = 1;

    // Iterate through all neighbors
    for (const int& neighbor : adj[current]) {
        // If the neighbor is not visited and not restricted, continue DFS
        if (!visited[neighbor] && restrictedSet.find(neighbor) == restrictedSet.end()) {
            count += dfsReachableNodes(neighbor, adj, restrictedSet, visited);
        }
    }

    return count;
}

int GraphUtil::reachableNodes(int n, const vector<std::vector<int>> &edges, const vector<int> &restricted) {
    // Initialize adjacency list
    std::vector<std::vector<int>> adj(n, std::vector<int>());
    for (const auto& edge : edges) {
        int a = edge[0];
        int b = edge[1];
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    // Convert restricted array to a set for O(1) lookups
    std::unordered_set<int> restrictedSet(restricted.begin(), restricted.end());

    // Initialize visited array
    std::vector<bool> visited(n, false);

    // Start DFS from node 0
    return dfsReachableNodes(0, adj, restrictedSet, visited);
}

int GraphUtil::shortestPathBinaryMatrix(const vector<std::vector<int>> &grid) {
    int n = grid.size();

    // If the start or end cell is blocked, return -1
    if (grid.empty() || grid[0][0] != 0 || grid[n - 1][n - 1] != 0) {
        return -1;
    }

    // Directions: up, down, left, right, and the four diagonals
    const std::vector<std::pair<int, int>> directions = {
            {-1,  0}, // Up
            { 1,  0}, // Down
            { 0, -1}, // Left
            { 0,  1}, // Right
            {-1, -1}, // Up-Left
            {-1,  1}, // Up-Right
            { 1, -1}, // Down-Left
            { 1,  1}  // Down-Right
    };

    // Initialize visited matrix
    std::vector<std::vector<bool>> visited(n, std::vector<bool>(n, false));
    std::queue<std::tuple<int, int, int>> q; // (row, col, path_length)

    // Start BFS from (0,0) with path length 1
    q.emplace(0, 0, 1);
    visited[0][0] = true;

    while (!q.empty()) {
        auto [row, col, pathLength] = q.front();
        q.pop();

        // If we've reached the destination, return the path length
        if (row == n - 1 && col == n - 1) {
            return pathLength;
        }

        // Explore all 8 directions
        for (const auto& dir : directions) {
            int newRow = row + dir.first;
            int newCol = col + dir.second;

            // Check boundaries and if the cell is unvisited and clear
            if (isValidWithSize(newRow, newCol, n) && !visited[newRow][newCol] && grid[newRow][newCol] == 0) {
                q.emplace(newRow, newCol, pathLength + 1);
                visited[newRow][newCol] = true;
            }
        }
    }

    // If destination is not reachable
    return -1;
}

bool GraphUtil::isValidWithSize(int row, int col, int n) const {
    return row >= 0 && row < n && col >= 0 && col < n;
}

int GraphUtil::nearestExit(vector<std::vector<char>> &maze, const vector<int> &entrance) {
    if (maze.empty() || maze[0].empty()) {
        return -1;
    }

    int m = static_cast<int>(maze.size());
    int n = static_cast<int>(maze[0].size());

    // Directions: up, down, left, right
    std::vector<std::array<int, 2>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    // Create a queue for BFS; each element holds {row, col, distance}
    std::queue<std::array<int, 3>> q;
    q.push({entrance[0], entrance[1], 0});

    // Mark the entrance as visited by replacing '.' with '+'
    maze[entrance[0]][entrance[1]] = '+';

    while (!q.empty()) {
        auto [row, col, distance] = q.front();
        q.pop();

        for (auto& dir : directions) {
            int newRow = row + dir[0];
            int newCol = col + dir[1];

            // 1) Ensure we stay in bounds
            if (newRow < 0 || newRow >= m || newCol < 0 || newCol >= n) {
                continue;
            }

            // 2) Skip walls or already visited cells
            if (maze[newRow][newCol] == '+') {
                continue;
            }

            // 3) Check if it's on the border -> found an exit
            if (isBorderCell(newRow, newCol, m, n)) {
                return distance + 1;
            }

            // Mark visited and push to queue
            maze[newRow][newCol] = '+';
            q.push({newRow, newCol, distance + 1});
        }
    }

    // If no exit found, return -1
    return -1;
}

bool GraphUtil::isBorderCell(int row, int col, int m, int n) {
    return (row == 0 || row == m - 1 || col == 0 || col == n - 1);
}

int GraphUtil::snakesAndLadders(const vector<std::vector<int>> &board) {
    int n = board.size();
    // We will create an array "cells" of size (n*n + 1).
    // cells[label] = (row, col) in the board.
    std::vector<std::pair<int,int>> cells(n*n + 1);

    std::vector<int> columns(n);
    for (int i = 0; i < n; ++i) {
        columns[i] = i;
    }

    // Label squares 1..n*n in boustrophedon style
    int label = 1;
    for (int row = n - 1; row >= 0; --row) {
        for (int col : columns) {
            cells[label++] = {row, col};
        }
        std::reverse(columns.begin(), columns.end());
    }

    // dist[x] = minimum number of moves to reach square x; -1 if unvisited
    std::vector<int> dist(n*n + 1, -1);
    dist[1] = 0;

    std::queue<int> q;
    q.push(1);

    while (!q.empty()) {
        int curr = q.front();
        q.pop();

        for (int step = 1; step <= 6; ++step) {
            int next = curr + step;
            if (next > n*n) break;

            auto [r, c] = cells[next];
            int destination = (board[r][c] != -1) ? board[r][c] : next;

            if (dist[destination] == -1) {
                dist[destination] = dist[curr] + 1;
                q.push(destination);
            }
        }
    }
    return dist[n*n];
}




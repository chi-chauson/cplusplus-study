//
// Created by cchau on 1/1/2025.
//

#ifndef PLAYGROUND_GRAPHUTIL_H
#define PLAYGROUND_GRAPHUTIL_H

#include <vector>
#include <unordered_set>

class GraphUtil {
public:
    bool validPath(int n, const std::vector<std::vector<int>>& edges, int source, int destination);
    int numIslands(std::vector<std::vector<char>>& grid);
    int countComponents(int n, const std::vector<std::vector<int>>& edges);
    /**
     * Returns the maximum area of an island in the given binary grid.
     * An island is a group of 1's connected 4-directionally.
     *
     * @param grid the binary matrix representing the grid
     * @return the maximum area of an island, or 0 if there is no island
     */
    int maxAreaOfIsland(std::vector<std::vector<int>>& grid);
    int reachableNodes(int n, const std::vector<std::vector<int>>& edges, const std::vector<int>& restricted);
    /**
     * Finds the length of the shortest clear path in a binary matrix from the top-left
     * cell (0, 0) to the bottom-right cell (n-1, n-1). A clear path consists of cells
     * with value 0, and movement is allowed in 8 directions.
     *
     * @param grid the n x n binary matrix
     * @return the length of the shortest clear path, or -1 if no such path exists
     */
    int shortestPathBinaryMatrix(const std::vector<std::vector<int>>& grid);

    /**
     * Returns the number of steps in the shortest path from the entrance
     * to the nearest exit in the maze.
     *
     * @param maze      A 2D vector of '.' and '+' characters.
     * @param entrance  A vector<int> with size 2: [entranceRow, entranceCol].
     * @return          The shortest number of steps to an exit, or -1 if none exists.
     */
    int nearestExit(std::vector<std::vector<char>>& maze, const std::vector<int>& entrance);

private:
    void dfsIsland(std::vector<std::vector<char>> &grid, int startRow, int startCol, int rows, int cols);
    void dfsCountComponents(int startNode, const std::vector <std::vector<int>> &adjacencyList, std::vector<bool> &visited);
    /**
     * Checks if the given cell is within the grid boundaries.
     *
     * @param r     current row
     * @param c     current column
     * @param rows  total number of rows in the grid
     * @param cols  total number of columns in the grid
     * @return true if the cell is within bounds, false otherwise
     */
    bool isValid(int r, int c, int rows, int cols) const;
    /**
     * Checks if the given cell coordinates are within the grid boundaries.
     *
     * @param row the row index
     * @param col the column index
     * @param n the size of the grid
     * @return true if the cell is within bounds, false otherwise
     */
    bool isValidWithSize(int row, int col, int n) const;

    /**
     * Checks if a cell is on the border of the maze.
     */
    bool isBorderCell(int row, int col, int m, int n);

    int dfsReachableNodes(int current, const std::vector<std::vector<int>>& adj, const std::unordered_set<int>& restrictedSet, std::vector<bool>& visited);
};


#endif //PLAYGROUND_GRAPHUTIL_H

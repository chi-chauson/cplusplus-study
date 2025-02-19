//
// Created by cchau on 1/1/2025.
//
#include "GraphUtil.h"
#include <gtest/gtest.h>
using namespace std;

// Assuming GraphUtil class is defined as above

class GraphUtilTest : public ::testing::Test {
protected:
    GraphUtil graphUtil;
};

// Test 1: Triangle Graph - Path Exists
TEST_F(GraphUtilTest, TriangleGraphPathExists) {
    int n = 3;
    vector<vector<int>> edges = { {0,1}, {1,2}, {2,0} };
    int source = 0;
    int destination = 2;
    EXPECT_TRUE(graphUtil.validPath(n, edges, source, destination));
}

// Test 2: Disconnected Graph - Path Does Not Exist
TEST_F(GraphUtilTest, DisconnectedGraphPathDoesNotExist) {
    int n = 6;
    vector<vector<int>> edges = { {0,1}, {0,2}, {3,5}, {5,4}, {4,3} };
    int source = 0;
    int destination = 5;
    EXPECT_FALSE(graphUtil.validPath(n, edges, source, destination));
}

// Test 3: Single Vertex - Source Equals Destination
TEST_F(GraphUtilTest, SingleVertexSameSourceDestination) {
    int n = 1;
    vector<vector<int>> edges = {};
    int source = 0;
    int destination = 0;
    EXPECT_TRUE(graphUtil.validPath(n, edges, source, destination));
}

// Test 4: Single Vertex - Source Does Not Equal Destination
TEST_F(GraphUtilTest, SingleVertexDifferentSourceDestination) {
    int n = 2;
    vector<vector<int>> edges = {};
    int source = 0;
    int destination = 1;
    EXPECT_FALSE(graphUtil.validPath(n, edges, source, destination));
}

// Test 5: Large Connected Graph - Path Exists
TEST_F(GraphUtilTest, LargeConnectedGraphPathExists) {
    int n = 100000;
    vector<vector<int>> edges;
    edges.reserve(n - 1);
    for(int i = 0; i < n - 1; ++i) {
        edges.push_back({i, i + 1});
    }
    int source = 0;
    int destination = n - 1;
    EXPECT_TRUE(graphUtil.validPath(n, edges, source, destination));
}

// Test 6: Large Disconnected Graph - Path Does Not Exist
TEST_F(GraphUtilTest, LargeDisconnectedGraphPathDoesNotExist) {
    int n = 100000;
    vector<vector<int>> edges;
    edges.reserve(n - 2);
    for(int i = 0; i < n - 2; ++i) {
        edges.push_back({i, i + 1});
    }
    // Note: Node n-1 is disconnected
    int source = 0;
    int destination = n - 1;
    EXPECT_FALSE(graphUtil.validPath(n, edges, source, destination));
}

// Test 7: Graph with No Edges - Source Equals Destination
TEST_F(GraphUtilTest, GraphWithNoEdgesSourceEqualsDestination) {
    int n = 5;
    vector<vector<int>> edges = {};
    int source = 3;
    int destination = 3;
    EXPECT_TRUE(graphUtil.validPath(n, edges, source, destination));
}

// Test 8: Graph with No Edges - Source Does Not Equal Destination
TEST_F(GraphUtilTest, GraphWithNoEdgesSourceNotEqualsDestination) {
    int n = 5;
    vector<vector<int>> edges = {};
    int source = 1;
    int destination = 4;
    EXPECT_FALSE(graphUtil.validPath(n, edges, source, destination));
}

// Test 9: Direct Edge Exists Between Source and Destination
TEST_F(GraphUtilTest, PathExistsDirectEdge) {
    int n = 4;
    vector<vector<int>> edges = { {0,1}, {1,2}, {2,3} };
    int source = 1;
    int destination = 2;
    EXPECT_TRUE(graphUtil.validPath(n, edges, source, destination));
}

// Test 10: Indirect Path Exists Through Multiple Nodes
TEST_F(GraphUtilTest, PathExistsIndirectEdge) {
    int n = 5;
    vector<vector<int>> edges = { {0,1}, {1,2}, {2,3}, {3,4} };
    int source = 0;
    int destination = 4;
    EXPECT_TRUE(graphUtil.validPath(n, edges, source, destination));
}

// Test 11: Path Does Not Exist Between Different Components
TEST_F(GraphUtilTest, PathDoesNotExistBetweenComponents) {
    int n = 7;
    vector<vector<int>> edges = { {0,1}, {1,2}, {2,3}, {4,5}, {5,6} };
    int source = 3;
    int destination = 5;
    EXPECT_FALSE(graphUtil.validPath(n, edges, source, destination));
}

// Test 12: Graph with Cycle - Path Exists
TEST_F(GraphUtilTest, GraphWithCyclePathExists) {
    int n = 4;
    vector<vector<int>> edges = { {0,1}, {1,2}, {2,0}, {2,3} };
    int source = 3;
    int destination = 0;
    EXPECT_TRUE(graphUtil.validPath(n, edges, source, destination));
}

// Test 13: Graph with Multiple Paths - Path Exists
TEST_F(GraphUtilTest, GraphWithMultiplePaths) {
    int n = 5;
    vector<vector<int>> edges = { {0,1}, {0,2}, {1,3}, {2,3}, {3,4} };
    int source = 0;
    int destination = 4;
    EXPECT_TRUE(graphUtil.validPath(n, edges, source, destination));
}

// Test 14: Single Edge Graph - No Path Exists
TEST_F(GraphUtilTest, NoPathInSingleEdgeGraph) {
    int n = 3;
    vector<vector<int>> edges = { {0,1} };
    int source = 0;
    int destination = 2;
    EXPECT_FALSE(graphUtil.validPath(n, edges, source, destination));
}

// Test 15: Path to Self in Larger Graph
TEST_F(GraphUtilTest, PathToSelfInLargerGraph) {
    int n = 10;
    vector<vector<int>> edges = { {0,1}, {1,2}, {2,3}, {3,4}, {5,6}, {6,7}, {7,8}, {8,9} };
    int source = 5;
    int destination = 5;
    EXPECT_TRUE(graphUtil.validPath(n, edges, source, destination));
}

// Test Case 1: All cells are land, expecting one island
TEST_F(GraphUtilTest, AllLand_SingleIsland) {
    std::vector<std::vector<char>> grid = {
            {'1', '1', '1'},
            {'1', '1', '1'},
            {'1', '1', '1'}
    };
    EXPECT_EQ(graphUtil.numIslands(grid), 1) << "All cells are land, should be one island.";
}

// Test Case 2: All cells are water, expecting zero islands
TEST_F(GraphUtilTest, AllWater_NoIslands) {
    std::vector<std::vector<char>> grid = {
            {'0', '0', '0'},
            {'0', '0', '0'},
            {'0', '0', '0'}
    };
    EXPECT_EQ(graphUtil.numIslands(grid), 0) << "All cells are water, should be zero islands.";
}

// Test Case 3: Multiple disconnected land cells, each representing separate islands
TEST_F(GraphUtilTest, DisconnectedLands_MultipleIslands) {
    std::vector<std::vector<char>> grid = {
            {'1', '0', '1'},
            {'0', '1', '0'},
            {'1', '0', '1'}
    };
    EXPECT_EQ(graphUtil.numIslands(grid), 5) << "Five separate land cells, each should be its own island.";
}

// Test Case 4: Example 1 from the problem statement, expecting one island
TEST_F(GraphUtilTest, ExampleOne_SingleLargeIsland) {
    std::vector<std::vector<char>> grid = {
            {'1','1','1','1','0'},
            {'1','1','0','1','0'},
            {'1','1','0','0','0'},
            {'0','0','0','0','0'}
    };
    EXPECT_EQ(graphUtil.numIslands(grid), 1) << "Example 1: Should have one island.";
}

// Test Case 5: Example 2 from the problem statement, expecting three islands
TEST_F(GraphUtilTest, ExampleTwo_MultipleIslands) {
    std::vector<std::vector<char>> grid = {
            {'1','1','0','0','0'},
            {'1','1','0','0','0'},
            {'0','0','1','0','0'},
            {'0','0','0','1','1'}
    };
    EXPECT_EQ(graphUtil.numIslands(grid), 3) << "Example 2: Should have three islands.";
}

// Test Case 6: Single land cell, expecting one island
TEST_F(GraphUtilTest, SingleLandCell_OneIsland) {
    std::vector<std::vector<char>> grid = {
            {'1'}
    };
    EXPECT_EQ(graphUtil.numIslands(grid), 1) << "Single land cell should count as one island.";
}

// Test Case 7: Single water cell, expecting zero islands
TEST_F(GraphUtilTest, SingleWaterCell_NoIslands) {
    std::vector<std::vector<char>> grid = {
            {'0'}
    };
    EXPECT_EQ(graphUtil.numIslands(grid), 0) << "Single water cell should count as zero islands.";
}

// Test Case 8: Non-rectangular grid (Outside problem constraints, skipped)
//TEST_F(GraphUtilTest, NonRectangularGrid_Skipped) {
//    // Note: C++ vectors of vectors can have varying lengths, but the problem assumes a rectangular grid.
//    // This test is included for robustness but is not executed.
//    // To implement, you would need to handle varying row sizes, which is beyond the problem's constraints.
//    GTEST_SKIP() << "Non-rectangular grids are outside the problem's constraints.";
//}

// Test Case 9: Large grid with sparse islands, expecting three islands
TEST_F(GraphUtilTest, LargeGrid_SparseIslands) {
    // Initialize a 300x300 grid filled with '0's
    std::vector<std::vector<char>> grid(300, std::vector<char>(300, '0'));

    // Place some islands
    grid[0][0] = '1';       // Island 1
    grid[299][299] = '1';   // Island 2
    grid[150][150] = '1';   // Island 3
    grid[150][151] = '1';   // Connected to Island 3
    grid[150][152] = '1';   // Connected to Island 3

    EXPECT_EQ(graphUtil.numIslands(grid), 3) << "Large grid with three separate islands.";
}

// Test Case 1: Disconnected Graph with Two Components
TEST_F(GraphUtilTest, DisconnectedGraphWithTwoComponents) {
    int n = 5;
    std::vector<std::vector<int>> edges = { {0, 1}, {1, 2}, {3, 4} };
    int expected = 2;
    EXPECT_EQ(expected, graphUtil.countComponents(n, edges))
                        << "Disconnected graph should have 2 connected components.";
}

// Test Case 2: Fully Connected Graph with One Component
TEST_F(GraphUtilTest, FullyConnectedGraphWithOneComponent) {
    int n = 5;
    std::vector<std::vector<int>> edges = { {0, 1}, {1, 2}, {2, 3}, {3, 4} };
    int expected = 1;
    EXPECT_EQ(expected, graphUtil.countComponents(n, edges))
                        << "Fully connected graph should have 1 connected component.";
}

// Test Case 3: Single Node Graph
TEST_F(GraphUtilTest, SingleNodeGraph) {
    int n = 1;
    std::vector<std::vector<int>> edges = {};
    int expected = 1;
    EXPECT_EQ(expected, graphUtil.countComponents(n, edges))
                        << "Single node graph should have 1 connected component.";
}

// Test Case 4: Multiple Nodes with No Edges
TEST_F(GraphUtilTest, MultipleNodesWithNoEdges) {
    int n = 4;
    std::vector<std::vector<int>> edges = {};
    int expected = 4;
    EXPECT_EQ(expected, graphUtil.countComponents(n, edges))
                        << "Graph with no edges should have 4 connected components.";
}

// Test Case 5: Multiple Components with Pairs
TEST_F(GraphUtilTest, MultipleComponentsWithPairs) {
    int n = 10;
    std::vector<std::vector<int>> edges = { {0, 1}, {2, 3}, {4, 5}, {6, 7}, {8, 9} };
    int expected = 5;
    EXPECT_EQ(expected, graphUtil.countComponents(n, edges))
                        << "Graph should have 5 connected components.";
}

// Test Case 6: Complex Graph with Cycles and Multiple Components
TEST_F(GraphUtilTest, ComplexGraphWithCyclesAndMultipleComponents) {
    int n = 7;
    std::vector<std::vector<int>> edges = { {0, 1}, {1, 2}, {2, 0}, {3, 4}, {5, 6} };
    int expected = 3;
    EXPECT_EQ(expected, graphUtil.countComponents(n, edges))
                        << "Complex graph should have 3 connected components.";
}

// Test Case 7: Graph with a Cycle
TEST_F(GraphUtilTest, GraphWithCycle) {
    int n = 4;
    std::vector<std::vector<int>> edges = { {0, 1}, {1, 2}, {2, 0}, {2, 3} };
    int expected = 1;
    EXPECT_EQ(expected, graphUtil.countComponents(n, edges))
                        << "Graph with a cycle should have 1 connected component.";
}

// Test Case 8: Graph with Isolated Nodes
TEST_F(GraphUtilTest, GraphWithIsolatedNodes) {
    int n = 6;
    std::vector<std::vector<int>> edges = { {0, 1}, {2, 3} };
    int expected = 4;
    EXPECT_EQ(expected, graphUtil.countComponents(n, edges))
                        << "Graph with isolated nodes should have 4 connected components.";
}

// Test Case 9: Empty Graph (No Nodes)
TEST_F(GraphUtilTest, EmptyGraph) {
    int n = 0;
    std::vector<std::vector<int>> edges = {};
    int expected = 0;
    EXPECT_EQ(expected, graphUtil.countComponents(n, edges))
                        << "Empty graph should have 0 connected components.";
}

// Test Case 10: Graph with Single Edge
TEST_F(GraphUtilTest, GraphWithSingleEdge) {
    int n = 2;
    std::vector<std::vector<int>> edges = { {0, 1} };
    int expected = 1;
    EXPECT_EQ(expected, graphUtil.countComponents(n, edges))
                        << "Graph with a single edge should have 1 connected component.";
}

// Test Case 11: Large Graph with Multiple Components
TEST_F(GraphUtilTest, LargeGraphWithMultipleComponents) {
    int n = 1000;
    std::vector<std::vector<int>> edges;
    // Creating 500 disconnected pairs
    for (int i = 0; i < 1000; i += 2) {
        edges.push_back({i, i + 1});
    }
    int expected = 500;
    EXPECT_EQ(expected, graphUtil.countComponents(n, edges))
                        << "Large graph should have 500 connected components.";
}

TEST_F(GraphUtilTest, MultipleIslands_ReturnsCorrectMaximumArea) {
    std::vector<std::vector<int>> grid = {
            {0,0,1,0,0,0,0,1,0,0,0,0,0},
            {0,0,0,0,0,0,0,1,1,1,0,0,0},
            {0,1,1,0,1,0,0,0,0,0,0,0,0},
            {0,1,0,0,1,1,0,0,1,0,1,0,0},
            {0,1,0,0,1,1,0,0,1,1,1,0,0},
            {0,0,0,0,0,0,0,0,0,0,1,0,0},
            {0,0,0,0,0,0,0,1,1,1,0,0,0},
            {0,0,0,0,0,0,0,1,1,0,0,0,0}
    };
    int expected = 6;
    EXPECT_EQ(graphUtil.maxAreaOfIsland(grid), expected);
}

TEST_F(GraphUtilTest, NoIslands_ReturnsZero) {
    std::vector<std::vector<int>> grid = {
            {0,0,0,0,0,0,0,0}
    };
    int expected = 0;
    EXPECT_EQ(graphUtil.maxAreaOfIsland(grid), expected);
}

TEST_F(GraphUtilTest, SingleCellIsland_ReturnsOne) {
    std::vector<std::vector<int>> grid = {
            {0, 1, 0},
            {0, 0, 0},
            {0, 0, 0}
    };
    int expected = 1;
    EXPECT_EQ(graphUtil.maxAreaOfIsland(grid), expected);
}

TEST_F(GraphUtilTest, EntireGridIsOneIsland_ReturnsGridSize) {
    std::vector<std::vector<int>> grid = {
            {1,1,1},
            {1,1,1},
            {1,1,1}
    };
    int expected = 9;
    EXPECT_EQ(graphUtil.maxAreaOfIsland(grid), expected);
}

TEST_F(GraphUtilTest, NonRectangularIslands_ReturnsCorrectMaximumArea) {
    std::vector<std::vector<int>> grid = {
            {1,0,1,1,0},
            {1,1,0,1,0},
            {0,1,1,0,1},
            {0,0,0,1,1}
    };
    int expected = 5;
    EXPECT_EQ(graphUtil.maxAreaOfIsland(grid), expected);
}

TEST_F(GraphUtilTest, EmptyGrid_ReturnsZero) {
    std::vector<std::vector<int>> grid = {};
    int expected = 0;
    EXPECT_EQ(graphUtil.maxAreaOfIsland(grid), expected);
}

TEST_F(GraphUtilTest, AllWaterGrid_ReturnsZero) {
    std::vector<std::vector<int>> grid = {
            {0,0,0},
            {0,0,0},
            {0,0,0}
    };
    int expected = 0;
    EXPECT_EQ(graphUtil.maxAreaOfIsland(grid), expected);
}

TEST_F(GraphUtilTest, LargeGridWithMixedIslands_ReturnsCorrectMaximumArea) {
    std::vector<std::vector<int>> grid = {
            {1, 1, 0, 0, 0, 1, 1, 1},
            {1, 1, 0, 1, 1, 1, 0, 0},
            {0, 0, 0, 1, 0, 0, 1, 1},
            {1, 0, 1, 0, 1, 1, 1, 0},
            {1, 1, 1, 0, 0, 0, 0, 1}
    };
    int expected = 7;
    EXPECT_EQ(graphUtil.maxAreaOfIsland(grid), expected);
}

// Test Case: Basic Example One
TEST_F(GraphUtilTest, BasicExampleOne) {
    int n = 7;
    std::vector<std::vector<int>> edges = {
            {0,1},{1,2},{3,1},{4,0},{0,5},{5,6}
    };
    std::vector<int> restricted = {4,5};
    int expected = 4; // Nodes [0,1,2,3]
    EXPECT_EQ(graphUtil.reachableNodes(n, edges, restricted), expected);
}

// Test Case: Basic Example Two
TEST_F(GraphUtilTest, BasicExampleTwo) {
    int n = 7;
    std::vector<std::vector<int>> edges = {
            {0,1},{0,2},{0,5},{0,4},{3,2},{6,5}
    };
    std::vector<int> restricted = {4,2,1};
    int expected = 3; // Nodes [0,5,6]
    EXPECT_EQ(graphUtil.reachableNodes(n, edges, restricted), expected);
}

// Test Case: No Restricted Nodes
TEST_F(GraphUtilTest, NoRestrictedNodes) {
    int n = 5;
    std::vector<std::vector<int>> edges = {
            {0,1},{0,2},{1,3},{1,4}
    };
    std::vector<int> restricted = {};
    int expected = 5; // All nodes are reachable
    EXPECT_EQ(graphUtil.reachableNodes(n, edges, restricted), expected);
}

// Test Case: All Except Zero Restricted
TEST_F(GraphUtilTest, AllExceptZeroRestricted) {
    int n = 3;
    std::vector<std::vector<int>> edges = {
            {0,1},{0,2}
    };
    std::vector<int> restricted = {1,2};
    int expected = 1; // Only node 0 is reachable
    EXPECT_EQ(graphUtil.reachableNodes(n, edges, restricted), expected);
}

// Test Case: Single Path with Multiple Restrictions
TEST_F(GraphUtilTest, SinglePathWithMultipleRestrictions) {
    int n = 10;
    std::vector<std::vector<int>> edges = {
            {0,1},{1,2},{2,3},{3,4},{4,5},{5,6},{6,7},{7,8},{8,9}
    };
    std::vector<int> restricted = {3,6,9};
    int expected = 3; // Nodes [0,1,2]
    EXPECT_EQ(graphUtil.reachableNodes(n, edges, restricted), expected);
}

// Test Case: Disconnected After Restrictions
TEST_F(GraphUtilTest, DisconnectedAfterRestrictions) {
    int n = 6;
    std::vector<std::vector<int>> edges = {
            {0,1},{1,2},{1,3},{3,4},{3,5}
    };
    std::vector<int> restricted = {1};
    int expected = 1; // Only node 0 is reachable
    EXPECT_EQ(graphUtil.reachableNodes(n, edges, restricted), expected);
}

// Test Case: Handle Small Grid with Specific Restrictions
TEST_F(GraphUtilTest, HandleSmallGridWithSpecificRestrictions) {
    // Constructing a small tree for clarity
    int n = 7;
    std::vector<std::vector<int>> edges = {
            {0,1}, {1,2}, {1,3}, {1,4}, {4,5}, {5,6}
    };
    std::vector<int> restricted = {4, 6}; // Restrict nodes 4 and 6
    int expected = 4; // Nodes [0,1,2,3] are reachable
    EXPECT_EQ(graphUtil.reachableNodes(n, edges, restricted), expected);
}

TEST_F(GraphUtilTest, ShortestPath_SimplePathExists) {
    std::vector<std::vector<int>> grid = {
            {0, 1},
            {1, 0}
    };
    int expected = 2;
    int actual = graphUtil.shortestPathBinaryMatrix(grid);
    EXPECT_EQ(actual, expected) << "Should return the shortest path length when a simple path exists.";
}

TEST_F(GraphUtilTest, ShortestPath_PathBlockedAtStart) {
    std::vector<std::vector<int>> grid = {
            {1, 0},
            {0, 0}
    };
    int expected = -1;
    int actual = graphUtil.shortestPathBinaryMatrix(grid);
    EXPECT_EQ(actual, expected) << "Should return -1 when the starting cell is blocked.";
}

TEST_F(GraphUtilTest, ShortestPath_PathBlockedAtEnd) {
    std::vector<std::vector<int>> grid = {
            {0, 0},
            {0, 1}
    };
    int expected = -1;
    int actual = graphUtil.shortestPathBinaryMatrix(grid);
    EXPECT_EQ(actual, expected) << "Should return -1 when the ending cell is blocked.";
}

TEST_F(GraphUtilTest, ShortestPath_NoPathExists) {
    std::vector<std::vector<int>> grid = {
            {0, 1, 1},
            {1, 1, 1},
            {1, 1, 0}
    };
    int expected = -1;
    int actual = graphUtil.shortestPathBinaryMatrix(grid);
    EXPECT_EQ(actual, expected) << "Should return -1 when no clear path exists.";
}

TEST_F(GraphUtilTest, ShortestPath_LargeGridWithPath) {
    std::vector<std::vector<int>> grid = {
            {0, 0, 0, 0},
            {1, 1, 0, 1},
            {0, 0, 0, 0},
            {0, 1, 1, 0}
    };
    int expected = 5; // Corrected expected value
    int actual = graphUtil.shortestPathBinaryMatrix(grid);
    EXPECT_EQ(actual, expected) << "Should return the correct path length in a larger grid with a valid path.";
}

TEST_F(GraphUtilTest, ShortestPath_SingleCellGrid) {
    std::vector<std::vector<int>> grid = {
            {0}
    };
    int expected = 1;
    int actual = graphUtil.shortestPathBinaryMatrix(grid);
    EXPECT_EQ(actual, expected) << "Should return 1 for a single-cell grid that is clear.";
}

TEST_F(GraphUtilTest, ShortestPath_SingleCellBlocked) {
    std::vector<std::vector<int>> grid = {
            {1}
    };
    int expected = -1;
    int actual = graphUtil.shortestPathBinaryMatrix(grid);
    EXPECT_EQ(actual, expected) << "Should return -1 for a single-cell grid that is blocked.";
}

TEST_F(GraphUtilTest, ShortestPath_PathWithDiagonalMoves) {
    std::vector<std::vector<int>> grid = {
            {0, 1, 1},
            {1, 0, 1},
            {1, 1, 0}
    };
    int expected = 3;
    int actual = graphUtil.shortestPathBinaryMatrix(grid);
    EXPECT_EQ(actual, expected) << "Should correctly account for diagonal moves in the path.";
}

// TEST 1: Multiple exits, expecting shortest path of 1 step.
TEST_F(GraphUtilTest, MultipleExitsShouldReturnOne) {
    std::vector<std::vector<char>> maze = {
            {'+', '+', '.', '+'},
            {'.', '.', '.', '+'},
            {'+', '+', '+', '.'}
    };
    std::vector<int> entrance = {1, 2}; // [row=1, col=2]

    int steps = graphUtil.nearestExit(maze, entrance);
    EXPECT_EQ(1, steps);
}

// --------------------------------------------------------------------------
// TEST 2: A single exit, expecting 2 steps.
TEST_F(GraphUtilTest, SingleExitShouldReturnTwo) {
    std::vector<std::vector<char>> maze = {
            {'+', '+', '+'},
            {'.', '.', '.'},
            {'+', '+', '+'}
    };
    std::vector<int> entrance = {1, 0};

    int steps = graphUtil.nearestExit(maze, entrance);
    EXPECT_EQ(2, steps);
}

// --------------------------------------------------------------------------
// TEST 3: No exit available. Should return -1.
TEST_F(GraphUtilTest, NoExitShouldReturnMinusOne) {
    std::vector<std::vector<char>> maze = {
            {'.', '+'}
    };
    std::vector<int> entrance = {0, 0};

    int steps = graphUtil.nearestExit(maze, entrance);
    EXPECT_EQ(-1, steps);
}

// --------------------------------------------------------------------------
// TEST 4: Entrance is on the border, but it doesn't count as an exit.
TEST_F(GraphUtilTest, MazeEntranceOnBorderButDoesntCountAsExit) {
    // Maze layout:
    // (0,0) '.'   (0,1) '.'
    // (1,0) '+'   (1,1) '.'
    //
    // The entrance is (0,0). It's on the border but is NOT an exit.
    // The nearest exit is (0,1), 1 step away.
    std::vector<std::vector<char>> maze = {
            {'.', '.'},
            {'+', '.'}
    };
    std::vector<int> entrance = {0, 0};

    int steps = graphUtil.nearestExit(maze, entrance);
    EXPECT_EQ(1, steps);
}

// --------------------------------------------------------------------------
// TEST 5: A complex maze; we just ensure it finds a path (distance > 0).
TEST_F(GraphUtilTest, ComplexMazeShouldReturnNonNegativeDistance) {
    std::vector<std::vector<char>> maze = {
            {'.', '.', '+', '.', '.'},
            {'.', '+', '+', '.', '+'},
            {'.', '.', '.', '.', '.'},
            {'+', '.', '+', '+', '.'},
            {'.', '.', '.', '+', '.'}
    };
    std::vector<int> entrance = {2, 2};

    int steps = graphUtil.nearestExit(maze, entrance);
    // Just check that it's a valid positive number, not -1
    EXPECT_GT(steps, 0) << "Should find a valid exit path in the complex maze.";
}

TEST_F(GraphUtilTest, ClassicBoardExample) {
    // Example from typical puzzle statements => 4 moves.
    std::vector<std::vector<int>> board = {
            {-1, -1, -1, -1, -1, -1},
            {-1, -1, -1, -1, -1, -1},
            {-1, -1, -1, -1, -1, -1},
            {-1, 35, -1, -1, 13, -1},
            {-1, -1, -1, -1, -1, -1},
            {-1, 15, -1, -1, -1, -1}
    };
    EXPECT_EQ(4, graphUtil.snakesAndLadders(board));
}

TEST_F(GraphUtilTest, TwoByTwoQuickJump) {
    // 2x2 board => minimal moves = 1
    std::vector<std::vector<int>> board = {
            {-1, -1},
            {-1,  3}
    };
    EXPECT_EQ(1, graphUtil.snakesAndLadders(board));
}

TEST_F(GraphUtilTest, UnreachableCase) {
    // 2x2 board, everything leads back to square 1 => can't reach 4 => -1
    std::vector<std::vector<int>> board = {
            { 1,  1},
            {-1,  1}
    };
    EXPECT_EQ(-1, graphUtil.snakesAndLadders(board));
}

TEST_F(GraphUtilTest, MinimalTwoByTwoEmpty) {
    // 2x2 board, no snakes/ladders => can roll a 3 to go from 1 to 4 in 1 move
    std::vector<std::vector<int>> board = {
            {-1, -1},
            {-1, -1}
    };
    EXPECT_EQ(1, graphUtil.snakesAndLadders(board));
}
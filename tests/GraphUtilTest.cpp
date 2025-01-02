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
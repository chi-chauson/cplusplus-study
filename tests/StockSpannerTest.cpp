//
// Created by cchau on 12/29/2024.
//
#include "gtest/gtest.h"
#include "StockSpanner.h"  // Ensure this header contains the StockSpanner class definition

// Test Case 1: Example Scenario
TEST(StockSpannerTest, Example1) {
    StockSpanner stockSpanner;
    EXPECT_EQ(stockSpanner.next(100), 1); // Span: 1
    EXPECT_EQ(stockSpanner.next(80), 1);  // Span: 1
    EXPECT_EQ(stockSpanner.next(60), 1);  // Span: 1
    EXPECT_EQ(stockSpanner.next(70), 2);  // Span: 2
    EXPECT_EQ(stockSpanner.next(60), 1);  // Span: 1
    EXPECT_EQ(stockSpanner.next(75), 4);  // Span: 4
    EXPECT_EQ(stockSpanner.next(85), 6);  // Span: 6
}

// Test Case 2: Strictly Increasing Prices
TEST(StockSpannerTest, IncreasingPrices) {
    StockSpanner stockSpanner;
    EXPECT_EQ(stockSpanner.next(10), 1); // Span: 1
    EXPECT_EQ(stockSpanner.next(20), 2); // Span: 2
    EXPECT_EQ(stockSpanner.next(30), 3); // Span: 3
    EXPECT_EQ(stockSpanner.next(40), 4); // Span: 4
    EXPECT_EQ(stockSpanner.next(50), 5); // Span: 5
}

// Test Case 3: Strictly Decreasing Prices
TEST(StockSpannerTest, DecreasingPrices) {
    StockSpanner stockSpanner;
    EXPECT_EQ(stockSpanner.next(50), 1); // Span: 1
    EXPECT_EQ(stockSpanner.next(40), 1); // Span: 1
    EXPECT_EQ(stockSpanner.next(30), 1); // Span: 1
    EXPECT_EQ(stockSpanner.next(20), 1); // Span: 1
    EXPECT_EQ(stockSpanner.next(10), 1); // Span: 1
}

// Test Case 4: Mixed Prices - Option 1 (Strictly Increasing)
TEST(StockSpannerTest, MixedPricesOption1) {
    StockSpanner stockSpanner;
    EXPECT_EQ(stockSpanner.next(31), 1); // Span: 1
    EXPECT_EQ(stockSpanner.next(41), 2); // Span: 2
    EXPECT_EQ(stockSpanner.next(48), 3); // Span: 3
    EXPECT_EQ(stockSpanner.next(59), 4); // Span: 4
    EXPECT_EQ(stockSpanner.next(79), 5); // Span: 5
    EXPECT_EQ(stockSpanner.next(80), 6); // Span: 6
    EXPECT_EQ(stockSpanner.next(94), 7); // Span: 7
}

// Test Case 5: Mixed Prices - Option 2 (Original Example)
TEST(StockSpannerTest, MixedPricesOption2) {
    StockSpanner stockSpanner;
    EXPECT_EQ(stockSpanner.next(100), 1); // Span: 1
    EXPECT_EQ(stockSpanner.next(80), 1);  // Span: 1
    EXPECT_EQ(stockSpanner.next(60), 1);  // Span: 1
    EXPECT_EQ(stockSpanner.next(70), 2);  // Span: 2
    EXPECT_EQ(stockSpanner.next(60), 1);  // Span: 1
    EXPECT_EQ(stockSpanner.next(75), 4);  // Span: 4
    EXPECT_EQ(stockSpanner.next(85), 6);  // Span: 6
}

// Test Case 6: Single Price
TEST(StockSpannerTest, SinglePrice) {
    StockSpanner stockSpanner;
    EXPECT_EQ(stockSpanner.next(1000), 1); // Span: 1
}

// Test Case 7: All Same Prices
TEST(StockSpannerTest, AllSamePrices) {
    StockSpanner stockSpanner;
    EXPECT_EQ(stockSpanner.next(50), 1); // Span: 1
    EXPECT_EQ(stockSpanner.next(50), 2); // Span: 2
    EXPECT_EQ(stockSpanner.next(50), 3); // Span: 3
    EXPECT_EQ(stockSpanner.next(50), 4); // Span: 4
    EXPECT_EQ(stockSpanner.next(50), 5); // Span: 5
}

// Test Case 8: Large Input
TEST(StockSpannerTest, LargeInput) {
    StockSpanner stockSpanner;
    int n = 10000;
    for (int i = 1; i <= n; ++i) {
        EXPECT_EQ(stockSpanner.next(i), i); // Span increases with each price
    }
}
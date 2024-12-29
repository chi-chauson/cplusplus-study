//
// Created by cchau on 12/29/2024.
//
#include "MovingAverage.h"
#include "gtest/gtest.h"

class MovingAverageTest : public ::testing::Test {
protected:
    MovingAverage *ma3; // MovingAverage object with size 3
    MovingAverage *ma5; // MovingAverage object with size 5

    void SetUp() override {
        ma3 = new MovingAverage(3);
        ma5 = new MovingAverage(5);
    }

    void TearDown() override {
        delete ma3;
        delete ma5;
    }
};

TEST_F(MovingAverageTest, SingleValue) {
    EXPECT_NEAR(1.0, ma3->next(1), 0.00001);
}

TEST_F(MovingAverageTest, WindowSizeExample) {
    EXPECT_NEAR(1.0, ma3->next(1), 0.00001);
    EXPECT_NEAR(5.5, ma3->next(10), 0.00001);
    EXPECT_NEAR(4.666666666666667, ma3->next(3), 0.00001);
    EXPECT_NEAR(6.0, ma3->next(5), 0.00001);
}

TEST_F(MovingAverageTest, LargeWindow) {
    ma5->next(1);
    ma5->next(2);
    ma5->next(3);
    ma5->next(4);
    EXPECT_NEAR(3.0, ma5->next(5), 0.00001);
    EXPECT_NEAR(4.0, ma5->next(6), 0.00001);
}

TEST_F(MovingAverageTest, NegativeValues) {
    EXPECT_NEAR(-100000.0, ma3->next(-100000), 0.00001);
    EXPECT_NEAR(-75000.0, ma3->next(-50000), 0.00001);
    EXPECT_NEAR(-50000.0, ma3->next(0), 0.00001);
}

TEST_F(MovingAverageTest, LargeValues) {
    ma3->next(100000);
    ma3->next(100000);
    EXPECT_NEAR(100000.0, ma3->next(100000), 0.00001);
}

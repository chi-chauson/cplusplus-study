//
// Created by cchau on 12/28/2024.
//
#include "StackUtil.h"
#include <gtest/gtest.h>

// Define a test fixture class if needed (optional)
class StackUtilTest : public ::testing::Test {
protected:
    StackUtil util;
};

TEST_F(StackUtilTest, Example1) {
    ASSERT_EQ("/home", util.simplifyPath("/home/"));
}

TEST_F(StackUtilTest, Example2) {
    ASSERT_EQ("/home/foo", util.simplifyPath("/home//foo/"));
}

TEST_F(StackUtilTest, Example3) {
    ASSERT_EQ("/home/user/Pictures", util.simplifyPath("/home/user/Documents/../Pictures"));
}

TEST_F(StackUtilTest, Example4) {
    ASSERT_EQ("/", util.simplifyPath("/../"));
}

TEST_F(StackUtilTest, Example5) {
    ASSERT_EQ("/.../b/d", util.simplifyPath("/.../a/../b/c/../d/./"));
}

TEST_F(StackUtilTest, EmptyPath) {
    ASSERT_EQ("/", util.simplifyPath(""));
}

TEST_F(StackUtilTest, RootPath) {
    ASSERT_EQ("/", util.simplifyPath("/"));
}

TEST_F(StackUtilTest, MultipleDots) {
    ASSERT_EQ("/....", util.simplifyPath("/..../"));
}

TEST_F(StackUtilTest, PathWithUnderscore) {
    ASSERT_EQ("/my_folder", util.simplifyPath("/my_folder/"));
}

TEST_F(StackUtilTest, ConsecutiveDots) {
    ASSERT_EQ("/...", util.simplifyPath("/hello/./../.../"));
}

TEST_F(StackUtilTest, LeadingAndTrailingSlashes) {
    ASSERT_EQ("/a/b", util.simplifyPath("///a//b/"));
}

TEST_F(StackUtilTest, DoubleDotAtRoot) {
    ASSERT_EQ("/", util.simplifyPath("/../../"));
}

TEST_F(StackUtilTest, MakeGood1) {
    EXPECT_EQ("leetcode", util.makeGood("leEeetcode"));
}

TEST_F(StackUtilTest, MakeGood2) {
    EXPECT_EQ("", util.makeGood("abBAcC"));
}

TEST_F(StackUtilTest, MakeGood3) {
    EXPECT_EQ("s", util.makeGood("s"));
}

TEST_F(StackUtilTest, MakeGood4) {
    EXPECT_EQ("", util.makeGood("Pp"));
}

TEST_F(StackUtilTest, MakeGood5) {
    EXPECT_EQ("a", util.makeGood("a"));
}

TEST_F(StackUtilTest, MakeGood6) {
    EXPECT_EQ("b", util.makeGood("b"));
}

TEST_F(StackUtilTest, MakeGood7) {
    EXPECT_EQ("", util.makeGood("Aa"));
}

TEST_F(StackUtilTest, MakeGood8) {
    EXPECT_EQ("A", util.makeGood("A"));
}

TEST_F(StackUtilTest, MakeGood9) {
    EXPECT_EQ("a", util.makeGood("a"));
}

TEST_F(StackUtilTest, MakeGoodNull) {
    EXPECT_EQ("", util.makeGood(""));
}

TEST_F(StackUtilTest, MakeGoodEmpty) {
    EXPECT_EQ("", util.makeGood(""));
}

# tests/CMakeLists.txt

# Fetch GoogleTest
include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

# Create the test executable
add_executable(StudyLibTest TwoPointersTest.cpp
        SlidingWindowTest.cpp
        PrefixSumTest.cpp
        HashingTest.cpp
        LinkedListUtilTest.cpp
        StackUtilTest.cpp
        MovingAverageTest.cpp
        MonotonicTest.cpp
        StockSpannerTest.cpp)

# Link the test executable against gtest, gtest_main, and the TwoPointers library
target_link_libraries(StudyLibTest
        gtest_main
        StudyLib
)

# Enable testing and add the test
include(GoogleTest)
gtest_discover_tests(StudyLibTest)
# src/CMakeLists.txt
add_library(StudyLib TwoPointers.cpp TwoPointers.h
        SlidingWindow.cpp
        SlidingWindow.h
        PrefixSum.cpp
        PrefixSum.h
        Hashing.cpp
        Hashing.h
        LinkedListUtil.cpp
        LinkedListUtil.h
        StackUtil.cpp
        StackUtil.h
        MovingAverage.cpp
        MovingAverage.h
        Monotonic.cpp
        Monotonic.h
        StockSpanner.cpp
        StockSpanner.h
        TreeUtil.cpp
        TreeUtil.h
        GraphUtil.cpp
        GraphUtil.h)

# You can add include directories if needed
target_include_directories(StudyLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
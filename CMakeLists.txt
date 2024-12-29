cmake_minimum_required(VERSION 3.30)
project(playground)

# Enable testing
enable_testing()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add subdirectories
add_subdirectory(src)
add_subdirectory(tests)

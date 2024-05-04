cmake_minimum_required(VERSION 3.27)
project(test)

set(CMAKE_CXX_STANDARD 17)

# Add the local Google Test directory to the list of paths to search for packages
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/gtest")

# Find the Google Test package
find_package(GTest REQUIRED)

# Include the Google Test headers
include_directories(${GTEST_INCLUDE_DIRS})

# Add the test executable
add_executable(test test.cpp)

# Link the Google Test libraries
target_link_libraries(test ${GTEST_LIBRARIES} pthread)

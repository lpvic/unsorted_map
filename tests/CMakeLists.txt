cmake_minimum_required(VERSION 3.5.0)
project(unsorted_map VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(test ./test.cpp)
set_target_properties(test PROPERTIES 
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIRECTORY}/output/lib/debug"
    LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/output/lib/debug"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/output/bin/debug"
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIRECTORY}/output/lib/release"
    LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/output/lib/release"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/output/bin/release"
)

set(GTEST_INCLUDE_DIR "${mylibs}/gtest/googletest/include")
set(GTEST_LIBRARY "${mylibs}/gtest/build/lib/libgtest.a")
set(GTEST_MAIN_LIBRARY "${mylibs}/gtest/build/lib/libgtest_main.a")
include_directories(${GTEST_INCLUDE_DIR})
find_package(GTest REQUIRED)

enable_testing()

add_executable(test_suite ./test_suite.cpp)
target_link_libraries(test_suite GTest::gtest_main)

add_test(gtests test_suite)

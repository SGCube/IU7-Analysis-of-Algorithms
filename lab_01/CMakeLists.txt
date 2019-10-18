cmake_minimum_required(VERSION 3.8)

project(bmstu_aa_lab_01)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(lab_01 main.cpp leven.cpp)

add_executable(test_01 test.cpp leven.cpp)
target_link_libraries(test_01 GTest::GTest GTest::Main)
add_test(NAME Lab01Tests COMMAND test_01)

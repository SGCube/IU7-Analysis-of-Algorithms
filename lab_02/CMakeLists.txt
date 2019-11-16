cmake_minimum_required(VERSION 3.5)

project(bmstu_aa_lab_02)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(lab_02 main.cpp mamult.cpp matrix.cpp)

add_executable(test_02 test.cpp mamult.cpp matrix.cpp)
target_link_libraries(test_02 GTest::GTest GTest::Main)
add_test(NAME Lab02Tests COMMAND test_02)

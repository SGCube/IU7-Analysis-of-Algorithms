cmake_minimum_required(VERSION 3.5)

project(bmstu_aa_lab_03)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(lab_03 main.cpp array.cpp)

add_executable(test_03 test.cpp array.cpp)
target_link_libraries(test_03 GTest::GTest GTest::Main)
add_test(NAME Lab03Tests COMMAND test_03)

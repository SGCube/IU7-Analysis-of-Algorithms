cmake_minimum_required(VERSION 3.8)

project(bmstu_aa_lab_01)

add_executable(lab_01.exe main.cpp leven.cpp)

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(test_01.exe test.cpp leven.cpp)
target_link_libraries(test_01.exe GTest::GTest GTest::Main)
add_test(NAME Lab01Tests COMMAND test_01.exe)

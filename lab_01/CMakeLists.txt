cmake_minimum_required(VERSION 3.8)

project(bmstu_aa_lab_01)

add_executable(lab_01.exe main.cpp leven.cpp)

enable_testing()
add_executable(test_01.exe test.cpp leven.cpp)
add_test(NAME test_01.exe)
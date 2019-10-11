cmake_minimum_required(VERSION 3.8)

project(bmstu_aa_lab_01)

add_executable(lab_01 main.cpp leven.cpp leven.hpp)
add_executable(lab_01_test test.cpp leven.cpp leven.hpp)
add_executable(lab_01_time time.cpp leven.cpp leven.hpp)
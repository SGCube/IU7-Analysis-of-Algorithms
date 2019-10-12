cmake_minimum_required(VERSION 3.8)

project(bmstu_aa_lab_02)

add_executable(lab_02_app.exe main.cpp mamult.cpp matrix.cpp)
add_executable(lab_02_test.exe test.cpp mamult.cpp matrix.cpp)
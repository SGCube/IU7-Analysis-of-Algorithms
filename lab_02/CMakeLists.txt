cmake_minimum_required(VERSION 3.8)

project(bmstu_aa_lab_02)

add_executable(app.exe main.cpp mamult.cpp matrix.cpp)
add_executable(test.exe test.cpp mamult.cpp matrix.cpp)
cmake_minimum_required(VERSION 3.5)

project(bmstu_aa_lab_05)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

find_library(PTHREAD_LIBRARY pthread)

add_executable(lab_05 main.cpp conveyor.cpp matrix.cpp)
target_link_libraries(lab_05 ${PTHREAD_LIBRARY})

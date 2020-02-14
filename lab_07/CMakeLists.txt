cmake_minimum_required(VERSION 3.5)

project(bmstu_aa_lab_07)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

find_library(PTHREAD_LIBRARY pthread)

add_executable(lab_07 main.cpp substr.cpp)
target_link_libraries(lab_07 ${PTHREAD_LIBRARY})

add_executable(lab_07_time time.cpp substr.cpp)
target_link_libraries(lab_07_time ${PTHREAD_LIBRARY})

add_executable(test_07 test.cpp substr.cpp)
target_link_libraries(test_07 GTest::GTest GTest::Main)
target_link_libraries(test_07 ${PTHREAD_LIBRARY})
add_test(NAME Lab07Tests COMMAND test_07)

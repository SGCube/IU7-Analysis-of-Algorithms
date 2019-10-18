add_executable(lab_02 main.cpp mamult.cpp matrix.cpp)

add_executable(test_02 test.cpp mamult.cpp matrix.cpp)
target_link_libraries(test_02 GTest::GTest GTest::Main)
add_test(NAME Lab02Tests COMMAND test_02)

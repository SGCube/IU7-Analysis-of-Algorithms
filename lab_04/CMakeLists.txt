add_executable(lab_04 main.cpp mamult.cpp matrix.cpp)

add_executable(test_04 test.cpp mamult.cpp matrix.cpp)
target_link_libraries(test_04 GTest::GTest GTest::Main)
add_test(NAME Lab04Tests COMMAND test_04)

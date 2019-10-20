add_executable(lab_03 main.cpp array.cpp)

add_executable(test_03 test.cpp array.cpp)
target_link_libraries(test_03 GTest::GTest GTest::Main)
add_test(NAME Lab03Tests COMMAND test_03)

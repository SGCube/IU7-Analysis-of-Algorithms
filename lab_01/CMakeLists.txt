add_executable(lab_01 main.cpp leven.cpp)

add_executable(test_01 test.cpp leven.cpp)
target_link_libraries(test_01 GTest::GTest GTest::Main)
add_test(NAME Lab01Tests COMMAND test_01)

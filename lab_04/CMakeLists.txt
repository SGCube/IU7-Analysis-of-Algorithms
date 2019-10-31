find_library(PTHREAD_LIBRARY pthread)

add_executable(lab_04 main.cpp mamult.cpp matrix.cpp)
target_link_libraries(lab_04 ${PTHREAD_LIBRARY})

add_executable(test_04 test.cpp mamult.cpp matrix.cpp)
target_link_libraries(test_04 GTest::GTest GTest::Main)
\target_link_libraries(test_04 ${PTHREAD_LIBRARY})
add_test(NAME Lab04Tests COMMAND test_04)

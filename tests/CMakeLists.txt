add_executable(my_tests test_example.cpp)
target_link_libraries(my_tests PRIVATE my_lib gtest gtest_main)
add_test(NAME MyTests COMMAND my_tests)

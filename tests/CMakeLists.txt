add_executable(tests
    test_example.cpp
    tree.cpp
)

target_link_libraries(tests
    PRIVATE
        gtest
        gtest_main
)

add_test(NAME all_tests COMMAND tests)

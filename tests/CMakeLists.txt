add_executable(tests
    test_monom.cpp
    test_polynom.cpp
)

target_link_libraries(tests
    PRIVATE
        monom
        polynom
        gtest
        gtest_main
)

add_test(NAME all_tests COMMAND tests)

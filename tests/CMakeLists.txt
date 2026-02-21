# 1. Создаем исполняемый файл из тех файлов, что реально есть в папке
add_executable(tests
    test_example.cpp
    test_itable.cpp
    test_unsortedtable.cpp
)

# 2. Подключаем библиотеки
target_link_libraries(tests
    PRIVATE
        gtest
        gtest_main
        # Если в других CMakeLists.txt ты создавал библиотеки (add_library), 
        # добавь их имена сюда, например:
        # libTvector 
        # libUnsortedTableOnVec
)

# 3. Подсказываем, где искать хедеры (на уровень выше, чтобы видеть libTvector и т.д.)
target_include_directories(tests PRIVATE ..)

# 4. Регистрация теста в системе
add_test(NAME all_tests COMMAND tests)
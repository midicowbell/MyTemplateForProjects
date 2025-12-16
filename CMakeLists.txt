# указываем последнюю доступную версию CMake
cmake_minimum_required(VERSION 3.14)

# стандарт языка
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# название проекта
project(MyProject)

# подключаем функции (если нужны)
include(cmake/functions.cmake)

# подключаем подкаталоги
add_subdirectory(lib)   # библиотека
add_subdirectory(src)   # основной исполняемый файл

# опция для тестов
option(BUILD_TESTS "Build unit tests?" ON)

if(BUILD_TESTS)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    add_subdirectory(third_party/gtest EXCLUDE_FROM_ALL)
    enable_testing()
    add_subdirectory(tests)
endif()

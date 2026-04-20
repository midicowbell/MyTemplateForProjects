cmake_minimum_required(VERSION 3.14)

project(MyProject)
include_directories(lib)
include_directories(libTree)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# подключаем функции (если нужны)
include(cmake/functions.cmake OPTIONAL)
include_directories(libTree)
include_directories(libBSTree)
include_directories(libAVLtree)
include_directories(libGraph)


# библиотеки
add_subdirectory(libTree)
add_subdirectory(libBSTree)
add_subdirectory(libAVLtree)
add_subdirectory(libGraph)


# основной исполняемый файл
add_subdirectory(src)

option(BUILD_TESTS "Build unit tests?" ON)

if(BUILD_TESTS)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    add_subdirectory(third_party/googletest EXCLUDE_FROM_ALL)

    enable_testing()
    add_subdirectory(tests)
endif()

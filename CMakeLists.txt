cmake_minimum_required(VERSION 3.14)
project(MyProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Папки для поиска хедеров во всем проекте
include_directories(lib)
include_directories(libTvector) # Исправил регистр v
include_directories(libUnsortedTableOnVec)

add_subdirectory(libAlgos)
add_subdirectory(lib_dsu)
add_subdirectory(src)

option(BUILD_TESTS "Build unit tests?" ON)

if(BUILD_TESTS)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    # Важно: путь должен совпадать с папкой на диске
    add_subdirectory(third_party/googletest EXCLUDE_FROM_ALL)

    enable_testing()
    add_subdirectory(tests) # Идет в папку tests и ищет там CMakeLists.txt
endif()
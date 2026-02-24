add_library(algos algos.cpp)
target_link_libraries(algos PUBLIC dsu)
target_include_directories(algos PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_library(libSortedTableOnRBTree tableRB.cpp)


target_link_libraries(libSortedTableOnRBTree PUBLIC itable)
target_include_directories(libSortedTableOnRBTree PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

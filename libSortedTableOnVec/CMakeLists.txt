add_library(SortedTable sortedTable.cpp)

# Polynom зависит от ITable
target_link_libraries(SortedTable PUBLIC itable)
target_link_libraries(SortedTable PUBLIC TVector)

target_include_directories(SortedTable PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

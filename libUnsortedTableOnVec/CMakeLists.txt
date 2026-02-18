add_library(UnsortedTable UnsortedTable.cpp)

# Polynom зависит от ITable
target_link_libraries(UnsortedTable PUBLIC itable)
target_link_libraries(UnsortedTable PUBLIC TVector)

target_include_directories(UnsortedTable PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

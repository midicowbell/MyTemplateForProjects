add_library(libHashTable hashTable.cpp)

# Polynom зависит от ITable
target_link_libraries(libHashTable PUBLIC itable)
target_link_libraries(libHashTable PUBLIC TVector)

target_include_directories(libHashTable PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

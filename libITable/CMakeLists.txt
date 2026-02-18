add_library(itable itable.cpp)
target_link_libraries(itable PUBLIC TVector)
target_include_directories(itable PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

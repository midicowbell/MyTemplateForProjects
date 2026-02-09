add_library(polynom Polynom.cpp)

# Polynom зависит от Monom
target_link_libraries(polynom PUBLIC monom)

target_include_directories(polynom PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

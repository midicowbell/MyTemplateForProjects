# functions.cmake
function(add_my_library target sources)
    add_library(${target} ${sources})
    target_include_directories(${target} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
endfunction()

function(add_my_executable target sources)
    add_executable(${target} ${sources})
    target_link_libraries(${target} PRIVATE my_lib)
endfunction()

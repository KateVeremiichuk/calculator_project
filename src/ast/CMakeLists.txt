set(CALC_AST ast)

add_library(${CALC_AST} INTERFACE)

target_include_directories(${CALC_AST}
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include
    )

if(CALC_BUILD_TESTS)
    add_subdirectory(test)
endif()

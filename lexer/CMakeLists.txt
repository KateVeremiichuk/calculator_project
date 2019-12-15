set(CALC_LEXER lexer)

add_library(${CALC_LEXER}
    src/Lexer.cpp
    )

target_include_directories(${CALC_LEXER}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
    )

if(CALC_BUILD_TESTS)
    add_subdirectory(test)
endif()

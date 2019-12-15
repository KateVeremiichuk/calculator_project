set(CALC_BINARY calc)

add_executable(${CALC_BINARY}
    src/main.cpp
    )

target_link_libraries(${CALC_BINARY}
    PRIVATE lexer
    PRIVATE parser
    )

set(CALC_LEXER_UNIT_TEST test_unit_lexer)

add_executable(${CALC_LEXER_UNIT_TEST}
    LexerUnitTest.cpp
    )

target_link_libraries(${CALC_LEXER_UNIT_TEST}
    PRIVATE GTest::GTest
    PRIVATE GTest::Main
    PRIVATE lexer
    )

add_test(${CALC_LEXER_UNIT_TEST} "" AUTO)

set(CALC_PARSER_UNIT_TEST test_unit_parser)

add_executable(${CALC_PARSER_UNIT_TEST}
    ParserUnitTest.cpp
    )

target_link_libraries(${CALC_PARSER_UNIT_TEST}
    PRIVATE GTest::GTest
    PRIVATE GTest::Main
    PRIVATE parser
    PRIVATE lexer
    )

add_test(${CALC_PARSER_UNIT_TEST} "" AUTO)

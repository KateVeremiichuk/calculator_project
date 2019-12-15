set(CALC_AST_UNIT_TEST test_unit_ast)

add_executable(${CALC_AST_UNIT_TEST}
    ASTUnitTest.cpp
    )

target_link_libraries(${CALC_AST_UNIT_TEST}
    PRIVATE GTest::GTest
    PRIVATE GTest::Main
    PRIVATE ast
    )

add_test(${CALC_AST_UNIT_TEST} "" AUTO)

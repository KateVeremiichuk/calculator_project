////////////////////////////////////////////////////////////////////////////////////////////////////
// @file ParserUnitTest.cpp
// @unit test:CParser
//

#include <stdexcept>

#include <gtest/gtest.h>

#include "lexer/Lexer.hpp"
#include "parser/Parser.hpp"

namespace {

void testExpr(const std::string &expr, double expected_value)
{
    Parser::CParser parser{std::make_unique<Lexer::CLexer>(expr)};

    auto node = parser.parse();
    ASSERT_NE(node, nullptr);

    EXPECT_DOUBLE_EQ(node->eval(), expected_value);
}

void testError(const std::string &expr)
{
    Parser::CParser parser{std::make_unique<Lexer::CLexer>(expr)};
    ASSERT_THROW(parser.parse(), std::runtime_error);
}

} // namespace

TEST(parser, numeric)
{
    testExpr("3.14", 3.14);
}

TEST(parser, simple)
{
    testExpr("2 + 2", 4);
}

TEST(parser, plus)
{
    testExpr("1 + 2 + 3", 6);
}

TEST(parser, minus)
{
    testExpr("1 - 1 - 1 - 1", -2);
}

TEST(parser, unary_plus)
{
    testExpr("+1", 1);
}

TEST(parser, minus_plus)
{
    testExpr("-1", -1);
}

TEST(parser, divide)
{
    testExpr("1 / 2", 0.5);
}

TEST(parser, precedence1)
{
    testExpr("1 + 3 * 2", 7);
}

TEST(parser, precedence2)
{
    testExpr("2 * 1 + 1", 3);
}

TEST(parser, power)
{
    testExpr("2 ^ 10", 1024);
}

TEST(parser, parentheses)
{
    testExpr("2 * (1 + 1)", 4);
}

TEST(parser, sin)
{
    testExpr("sin(pi / 2)", 1);
}

TEST(parser, cos)
{
    testExpr("cos(pi)", -1);
}

TEST(parser, tan)
{
    testExpr("tan(pi / 2) * cos(pi / 2)", 1);
}

TEST(parser, ctg)
{
    testExpr("ctg(pi) * sin(pi)", -1);
}

TEST(parser, sin2pluscos2)
{
    testExpr("sin(0.123456789) ^ 2 + cos(0.123456789) ^ 2", 1);
}

TEST(parser, log)
{
    testExpr("log(1024)/log(2)", 10);
}

TEST(parser, empty)
{
    testError("");
}

TEST(parser, excess)
{
    testError("2+2 2");
}

TEST(parser, unknown)
{
    testError("@");
}

TEST(parser, unexpected)
{
    testError("+");
}

TEST(parser, unexpected_end)
{
    testError("2+");
}

TEST(parser, paren_expected)
{
    testError("sin 2");
}

TEST(parser, unmatched_parentheses)
{
    testError("(2+2");
}

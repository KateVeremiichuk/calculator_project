////////////////////////////////////////////////////////////////////////////////////////////////////
// @file LexerUnitTest.cpp
// @unit test:CLexer
//

#include <utility>
#include <vector>

#include <gtest/gtest.h>

#include "lexer/Lexer.hpp"

namespace {

void testSequence(Lexer::CLexer &lexer, const std::vector<Lexer::Token> &tokens)
{
    for (const auto &expected_token : tokens)
    {
        Lexer::Token actual_token = lexer.nextToken();

        EXPECT_EQ(expected_token.id, actual_token.id);
        EXPECT_EQ(expected_token.text, actual_token.text);
    }
}

} // namespace

TEST(lexer, empty)
{
    const std::string expr{""};
    Lexer::CLexer lexer{expr};
    testSequence(
        lexer,
        {
            {Lexer::TokenId::End, ""},
        });
}

TEST(lexer, numeric)
{
    const std::string expr{"3.14"};
    Lexer::CLexer lexer{expr};
    testSequence(
        lexer,
        {
            {Lexer::TokenId::Numeric, "3.14"},
            {Lexer::TokenId::End, ""},
        });
}

TEST(lexer, unknown)
{
    const std::string expr{"@"};
    Lexer::CLexer lexer{expr};
    testSequence(
        lexer,
        {
            {Lexer::TokenId::Unknown, "@"},
            {Lexer::TokenId::End, ""},
        });
}

TEST(lexer, spaces)
{
    const std::string expr{"     "};
    Lexer::CLexer lexer{expr};
    testSequence(
        lexer,
        {
            {Lexer::TokenId::End, ""},
        });
}

TEST(lexer, more_unknown)
{
    const std::string expr{"!@#$"};
    Lexer::CLexer lexer{expr};
    testSequence(
        lexer,
        {
            {Lexer::TokenId::Unknown, "!"},
            {Lexer::TokenId::Unknown, "@"},
            {Lexer::TokenId::Unknown, "#"},
            {Lexer::TokenId::Unknown, "$"},
            {Lexer::TokenId::End, ""},
        });
}

TEST(lexer, identifier)
{
    const std::string expr{"test_identifier"};
    Lexer::CLexer lexer{expr};
    testSequence(
        lexer,
        {
            {Lexer::TokenId::Identifier, "test_identifier"},
            {Lexer::TokenId::End, ""},
        });
}

TEST(lexer, simple)
{
    const std::string expr{"2+2"};
    Lexer::CLexer lexer{expr};
    testSequence(
        lexer,
        {
            {Lexer::TokenId::Numeric, "2"},
            {Lexer::TokenId::Plus, "+"},
            {Lexer::TokenId::Numeric, "2"},
            {Lexer::TokenId::End, ""},
        });
}

TEST(lexer, complex)
{
    const std::string expr{"3.14 + (1 / 2.71) * (1 ^ 0) - 1"};
    Lexer::CLexer lexer{expr};
    testSequence(
        lexer,
        {
            {Lexer::TokenId::Numeric, "3.14"},
            {Lexer::TokenId::Plus, "+"},
            {Lexer::TokenId::LeftPar, "("},
            {Lexer::TokenId::Numeric, "1"},
            {Lexer::TokenId::Slash, "/"},
            {Lexer::TokenId::Numeric, "2.71"},
            {Lexer::TokenId::RightPar, ")"},
            {Lexer::TokenId::Asterisk, "*"},
            {Lexer::TokenId::LeftPar, "("},
            {Lexer::TokenId::Numeric, "1"},
            {Lexer::TokenId::Caret, "^"},
            {Lexer::TokenId::Numeric, "0"},
            {Lexer::TokenId::RightPar, ")"},
            {Lexer::TokenId::Minus, "-"},
            {Lexer::TokenId::Numeric, "1"},
            {Lexer::TokenId::End, ""},
        });
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// @file ASTUnitTest.cpp
// @unit test:TNode
//

#include <gtest/gtest.h>

#include "ast/TNode.hpp"

TEST(ast, constant)
{
    auto node = AST::makeNode([](const auto &) { return 42; });
    ASSERT_EQ(node->eval(), 42);
}

TEST(ast, unary)
{
    auto node = AST::makeNode(
        [](const auto &args) { return 2 * args[0]; },
        AST::makeNode([](const auto &) { return 15; }));
    ASSERT_EQ(node->eval(), 30);
}

TEST(ast, binary)
{
    auto node = AST::makeNode(
        [](const auto &args) { return args[0] + args[1]; },
        AST::makeNode([](const auto &) { return 2; }),
        AST::makeNode([](const auto &) { return 3; }));
    ASSERT_EQ(node->eval(), 5);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// @file Parser.cpp
// @unit CParser
//

#include "parser/Parser.hpp"

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>

#include "ast/TNode.hpp"

using namespace Lexer;

namespace Parser {

CParser::CParser(LexerPtr &&lexer)
    : m_lexer{std::move(lexer)}
{
}

AST::NodePtr CParser::parse()
{
    getToken();

    if (check(TokenId::End))
    {
        throw std::runtime_error{"empty expression"};
    }

    auto node = addSub();

    if (!check(TokenId::End))
    {
        throw std::runtime_error{"there's an excess part of expression"};
    }

    return node;
}

void CParser::getToken()
{
    m_token = m_lexer->nextToken();
}

bool CParser::check(TokenId id) const
{
    return m_token.id == id;
}

bool CParser::accept(TokenId id)
{
    if (check(id))
    {
        getToken();
        return true;
    }

    return false;
}

AST::NodePtr CParser::addSub()
{
    AST::NodePtr node = mulDiv();

    while (true)
    {
        if (accept(TokenId::Plus))
        {
            node = AST::makeNode(
                [](const auto &args) { return args[0] + args[1]; }, std::move(node), mulDiv());
        }
        else if (accept(TokenId::Minus))
        {
            node = AST::makeNode(
                [](const auto &args) { return args[0] - args[1]; }, std::move(node), mulDiv());
        }
        else
        {
            break;
        }
    }

    return node;
}

AST::NodePtr CParser::mulDiv()
{
    AST::NodePtr node = power();

    while (true)
    {
        if (accept(TokenId::Asterisk))
        {
            node = AST::makeNode(
                [](const auto &args) { return args[0] * args[1]; }, std::move(node), power());
        }
        else if (accept(TokenId::Slash))
        {
            node = AST::makeNode(
                [](const auto &args) { return args[0] / args[1]; }, std::move(node), power());
        }
        else
        {
            break;
        }
    }

    return node;
}

AST::NodePtr CParser::power()
{
    AST::NodePtr node = unary();

    while (true)
    {
        if (accept(TokenId::Caret))
        {
            node = AST::makeNode(
                [](const auto &args) { return std::pow(args[0], args[1]); },
                std::move(node),
                unary());
        }
        else
        {
            break;
        }
    }

    return node;
}

AST::NodePtr CParser::unary()
{
    AST::NodePtr node = nullptr;

    if (accept(TokenId::Minus))
    {
        node = AST::makeNode([](const auto &args) { return -args[0]; }, term());
    }
    else
    {
        accept(TokenId::Plus);
        node = term();
    }

    return node;
}

AST::NodePtr CParser::term()
{
    AST::NodePtr node = nullptr;

    if (check(TokenId::Numeric))
    {
        const double value = std::stod(m_token.text);
        node = AST::makeNode([=](const auto &) { return value; });
        getToken();
    }
    else if (check(TokenId::Identifier))
    {
        const std::string id = m_token.text;
        getToken();

        static const std::array<const char *, 7> c_ids{
            "pi", "e", "sin", "cos", "tan", "ctg", "log"};

        if (std::find(std::begin(c_ids), std::end(c_ids), id) == std::end(c_ids))
        {
            std::ostringstream ss;
            ss << "unknown identifier '" << id << "'";
            throw std::runtime_error{ss.str()};
        }

        if (id == "pi")
        {
            node = AST::makeNode([](const auto &) { return M_PI; });
        }
        else if (id == "e")
        {
            node = AST::makeNode([](const auto &) { return M_E; });
        }
        else
        {
            if (!accept(TokenId::LeftPar))
            {
                throw std::runtime_error{"open parenthesis expected"};
            }

            if (id == "sin")
            {
                node = AST::makeNode([](const auto &args) { return std::sin(args[0]); }, addSub());
            }
            else if (id == "cos")
            {
                node = AST::makeNode([](const auto &args) { return std::cos(args[0]); }, addSub());
            }
            else if (id == "tan")
            {
                node = AST::makeNode([](const auto &args) { return std::tan(args[0]); }, addSub());
            }
            else if (id == "ctg")
            {
                node = AST::makeNode(
                    [](const auto &args) { return 1.0 / std::tan(args[0]); }, addSub());
            }
            else if (id == "log")
            {
                node = AST::makeNode([](const auto &args) { return std::log(args[0]); }, addSub());
            }
            else
            {
                assert(false);
            }

            if (!accept(TokenId::RightPar))
            {
                throw std::runtime_error{"unmatched parentheses"};
            }
        }
    }
    else if (accept(TokenId::LeftPar))
    {
        node = addSub();

        if (!accept(TokenId::RightPar))
        {
            throw std::runtime_error{"unmatched parentheses"};
        }
    }
    else if (check(TokenId::Unknown))
    {
        std::ostringstream ss;
        ss << "unknown token '" << m_token.text << "'";
        throw std::runtime_error{ss.str()};
    }
    else if (check(TokenId::End))
    {
        throw std::runtime_error{"unexpected end of expression"};
    }
    else
    {
        std::ostringstream ss;
        ss << "unexpected token '" << m_token.text << "'";
        throw std::runtime_error{ss.str()};
    }

    return node;
}

} // namespace Parser

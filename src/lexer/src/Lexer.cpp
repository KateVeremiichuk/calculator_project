////////////////////////////////////////////////////////////////////////////////////////////////////
// @file Lexer.cpp
// @unit CLexer
//

#include "lexer/Lexer.hpp"

#include <cctype>
#include <unordered_map>

namespace Lexer {

namespace {

static const std::unordered_map<char, TokenId> s_token_id_map{
    {'+', TokenId::Plus},
    {'-', TokenId::Minus},
    {'*', TokenId::Asterisk},
    {'/', TokenId::Slash},
    {'^', TokenId::Caret},
    {'(', TokenId::LeftPar},
    {')', TokenId::RightPar},
};

} // namespace

CLexer::CLexer(const std::string &expr)
    : m_expr{expr}
    , m_pos{0}
{
}

Token CLexer::nextToken()
{
    Token token{TokenId::End, ""};

    while (m_pos < m_expr.size() && std::isspace(m_expr[m_pos]))
    {
        m_pos++;
    }

    if (m_pos == m_expr.size())
    {
    }
    else if (std::isdigit(m_expr[m_pos]))
    {
        token.id = TokenId::Numeric;

        while (std::isdigit(m_expr[m_pos]))
        {
            token.text += m_expr[m_pos++];
        }

        if (m_expr[m_pos] == '.')
        {
            do
            {
                token.text += m_expr[m_pos++];
            } while (std::isdigit(m_expr[m_pos]));
        }
    }
    else if (std::isalpha(m_expr[m_pos]) || m_expr[m_pos] == '_')
    {
        token.id = TokenId::Identifier;

        while (std::isalpha(m_expr[m_pos]) || m_expr[m_pos] == '_')
        {
            token.text += m_expr[m_pos++];
        }
    }
    else
    {
        const auto it = s_token_id_map.find(m_expr[m_pos]);
        token.id = it != s_token_id_map.end() ? it->second : TokenId::Unknown;

        token.text += m_expr[m_pos++];
    }

    return token;
}

} // namespace Lexer

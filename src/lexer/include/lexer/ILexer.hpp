////////////////////////////////////////////////////////////////////////////////////////////////////
// @file ILexer.hpp
// @unit ILexer
//

#pragma once

#include <memory>
#include <string>

namespace Lexer {

enum class TokenId
{
    Numeric,
    Plus,
    Minus,
    Asterisk,
    Slash,
    Caret,
    Identifier,
    LeftPar,
    RightPar,
    End,
    Unknown,
};

struct Token
{
    TokenId id;
    std::string text;
};

class ILexer
{
public: // methods
    virtual ~ILexer() = default;

    virtual Token nextToken() = 0;
};

using LexerPtr = std::unique_ptr<ILexer>;

} // namespace Lexer

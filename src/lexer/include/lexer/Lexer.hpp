////////////////////////////////////////////////////////////////////////////////////////////////////
// @file Lexer.hpp
// @unit CLexer
//

#pragma once

#include <cstddef>
#include <string>

#include "lexer/ILexer.hpp"

namespace Lexer {

class CLexer : public ILexer
{
public: // methods
    explicit CLexer(const std::string &expr);

    Token nextToken() override;

private: // fields
    const std::string &m_expr;
    size_t m_pos;
};

} // namespace Lexer

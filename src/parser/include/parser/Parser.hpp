////////////////////////////////////////////////////////////////////////////////////////////////////
// @file Parser.hpp
// @unit CParser
//

#pragma once

#include "ast/INode.hpp"
#include "lexer/ILexer.hpp"

namespace Parser {

class CParser
{
public: // methods
    explicit CParser(Lexer::LexerPtr &&lexer);

    AST::NodePtr parse();

private: // methods
    void getToken();

    bool check(Lexer::TokenId id) const;
    bool accept(Lexer::TokenId id);

    AST::NodePtr addSub();
    AST::NodePtr mulDiv();
    AST::NodePtr power();
    AST::NodePtr unary();
    AST::NodePtr term();

private: // fields
    Lexer::LexerPtr m_lexer;
    Lexer::Token m_token;
};

} // namespace Parser

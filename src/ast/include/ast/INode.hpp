////////////////////////////////////////////////////////////////////////////////////////////////////
// @file INode.hpp
// @unit INode
//

#pragma once

#include <memory>

namespace AST {

class INode
{
public: // methods
    virtual double eval() const = 0;

    virtual ~INode() = default;
};

using NodePtr = std::unique_ptr<INode>;

} // namespace AST

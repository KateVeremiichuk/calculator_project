////////////////////////////////////////////////////////////////////////////////////////////////////
// @file TNode.hpp
// @unit TNode
//

#pragma once

#include <array>
#include <cstddef>
#include <functional>
#include <utility>

#include "ast/INode.hpp"

namespace AST {

namespace detail {

template <size_t N>
using NodeFunc = std::function<double(const std::array<double, N> &)>;

template <size_t N>
using ChildNodes = std::array<NodePtr, N>;

} // namespace detail

template <size_t N>
class TNode : public INode
{
public: // methods
    explicit TNode(const detail::NodeFunc<N> &body, detail::ChildNodes<N> &&child_nodes)
        : m_body{body}
        , m_child_nodes{std::move(child_nodes)}
    {
    }

    double eval() const override
    {
        return evalImpl(std::make_index_sequence<N>{});
    }

private: // methods
    template <size_t... I>
    double evalImpl(std::index_sequence<I...>) const
    {
        return m_body({std::get<I>(m_child_nodes)->eval()...});
    }

private: // fields
    const detail::NodeFunc<N> m_body;
    const detail::ChildNodes<N> m_child_nodes;
};

template <class... TChildNodes>
NodePtr makeNode(
    const detail::NodeFunc<sizeof...(TChildNodes)> &body,
    TChildNodes &&... child_nodes)
{
    static constexpr size_t N = sizeof...(TChildNodes);
    return std::make_unique<TNode<N>>(
        body, detail::ChildNodes<N>{std::forward<TChildNodes>(child_nodes)...});
}

} // namespace AST

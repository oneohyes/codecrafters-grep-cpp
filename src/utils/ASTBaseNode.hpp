#pragma once
#include <cstddef>
#include <string_view>

namespace Utils {
template <typename R>
class Visitor;
// Abstract Syntax Tree Node
struct ASTNode {
    template<typename R>
    R accept(Visitor<R>& visitor) {
        return visitor.visit(*this);
    }
    virtual ~ASTNode() = default;
};

}

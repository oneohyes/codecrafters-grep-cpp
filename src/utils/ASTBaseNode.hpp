#pragma once
#include <cstddef>
#include <string_view>

namespace Utils {
template <typename R>
class Visitor;
// Abstract Syntax Tree Node
struct ASTNode {
    // enum class Type {
    //     Literal,
    //     Dot,
    //     Digit,
    //     Word,
    //     Whitespace,
    //     CharacterGroup,
    //     // NegativeCharacterGroup,
    //     StartAnchor,
    //     EndAnchor,
    //     Concat,
    //     Group,
    //     Alternation,
    //     Quantifier,
    //     Backreference
    // };
    // Type type{};
    template<typename R>
    R accept(Visitor<R>& visitor) {
        return visitor.visit(*this);
        
    };
    virtual void print() const = 0;
    virtual void print(int indent) const = 0;
    virtual bool match(std::string_view text, size_t& pos) const = 0;
    virtual ~ASTNode() = default;
};

}

#pragma once
#include <memory>
#include <string>
#include <vector>
#include <cctype>

#include "ASTBaseNode.hpp"

namespace Utils {

// LiteralNode represents a literal string
struct LiteralNode : ASTNode {
    char value;
    LiteralNode(char v) : value(v) { }
};

struct DotNode : ASTNode { 
};

struct DigitNode : ASTNode { 
};
// WordNode represents a word character
struct WordNode : ASTNode { 
};
// WhitespaceNode represents a whitespace character
struct WhitespaceNode : ASTNode { 
};
struct CharacterGroupNode : ASTNode {
    std::string chars;
    CharacterGroupNode(const std::string& c) : chars(c){ }
};
// NegativeCharacterGroupNode represents a negative character group
struct NegativeCharacterGroupNode : ASTNode {
    std::string chars;
    NegativeCharacterGroupNode(const std::string& c) : chars(c){ }
};

struct StartAnchorNode : ASTNode { 
};
// EndAnchorNode represents an end anchor
struct EndAnchorNode : ASTNode { 
};
// ConcatNode represents a concatenation
struct ConcatNode : ASTNode {
    std::vector<std::unique_ptr<ASTNode>> children;
    ConcatNode(std::vector<std::unique_ptr<ASTNode>> children) : children(std::move(children)) { }
};
// GroupNode represents a group (abc)
struct GroupNode : ASTNode {
    int id;
    std::unique_ptr<ASTNode> child;
    GroupNode(int id, std::unique_ptr<ASTNode> child) : id(id), child(std::move(child)) { }
};
// AlternationNode represents alternation (abc|def)
struct AlternationNode : ASTNode {
    std::vector<std::unique_ptr<ASTNode>> children;
};
// QuantifierNode represents a quantifier (abc{3,5})
struct QuantifierNode : ASTNode {
    std::pair<int, int> range;
    QuantifierNode(int l, int r) : range(l, r) { }
};
// BackreferenceNode represents a backreference (\1)
struct BackreferenceNode : ASTNode {
    int id;
    BackreferenceNode(int id) : id(id) { }
};

} // namespace Utils
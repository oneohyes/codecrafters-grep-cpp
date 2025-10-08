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
    // void accept(Visitor& visitor) override;
    // LiteralNode(char v) : value(v) { this->type = Type::Literal; }
    // void print(int indent) const override { std::cout << std::string(indent, ' ') << "Literal(" << value << ")"; }
    // bool match(std::string_view text, size_t& pos) const override {
    //     if (pos < text.size() && text[pos] == value) {
    //         pos++;
    //         return true;
    //     }
    //     return false;
    // }
};

struct DotNode : ASTNode { 
    // void accept(Visitor& visitor) override;
    // DotNode() { this->type = Type::Dot; }
    // void print(int indent) const override { std::cout << std::string(indent, ' ') << "Dot"; }
    // bool match(std::string_view text, size_t& pos) const override {
    //     if (pos < text.size()) {
    //         pos++;
    //         return true;
    //     }
    //     return false;
    // }
};

struct DigitNode : ASTNode { 
    // void accept(Visitor& visitor) override;
    // DigitNode() { this->type = Type::Digit; }
    // void print(int indent) const override { std::cout << std::string(indent, ' ') << "Digit"; }
    // bool match(std::string_view text, size_t& pos) const override {
    //     if (pos < text.size() && std::isdigit(text[pos])) {
    //         pos++;
    //         return true;
    //     }
    //     return false;
    // }
};
// WordNode represents a word character
struct WordNode : ASTNode { 
    // void accept(Visitor& visitor) override;
    // WordNode() { this->type = Type::Word; }
    // void print(int indent) const override { std::cout << std::string(indent, ' ') << "Word"; } 
    // bool match(std::string_view text, size_t& pos) const override {
    //     if (pos < text.size() && (std::isalnum(text[pos]) || text[pos] == '_')) {
    //         pos++;
    //         return true;
    //     }
    //     return false;
    // }
};
// WhitespaceNode represents a whitespace character
struct WhitespaceNode : ASTNode { 
    // void accept(Visitor& visitor) override;
    // WhitespaceNode() { this->type = Type::Whitespace; }
    // void print(int indent) const override { std::cout << std::string(indent, ' ') << "Whitespace"; } 
    // bool match(std::string_view text, size_t& pos) const override {
    //     if (pos < text.size() && std::isspace(text[pos])) {
    //         pos++;
    //         return true;
    //     }
    //     return false;
    // }
};
struct CharacterGroupNode : ASTNode {
    bool isNegative;
    std::string chars;
    CharacterGroupNode(bool isNegative, const std::string& c) : isNegative(isNegative), chars(c) { }
    // void accept(Visitor& visitor) override;
    // CharacterGroupNode(bool isNegative, const std::string& c) : isNegative(isNegative), chars(c) { this->type = Type::CharacterGroup; }
    // void print(int indent) const override { std::cout << std::string(indent, ' ') << "CharacterGroup(" << (isNegative ? "!" : "") << chars << ")"; }
    // bool match(std::string_view text, size_t& pos) const override {
    //     if (pos < text.size() && chars.find(text[pos]) != std::string::npos) {
    //         pos++;
    //         return isNegative ? false : true;
    //     }
    //     return isNegative ? true : false;
    // }
};
struct StartAnchorNode : ASTNode { 
    // void accept(Visitor& visitor) override;
    // StartAnchorNode() { this->type = Type::StartAnchor; } 
    // void print(int indent) const override { std::cout << std::string(indent, ' ') << "StartAnchor"; }
    // bool match(std::string_view text, size_t& pos) const override {
    //     return pos == 0;
    // }
};
// EndAnchorNode represents an end anchor
struct EndAnchorNode : ASTNode { 
    // void accept(Visitor& visitor) override;
    // EndAnchorNode() { this->type = Type::EndAnchor; } 
    // void print(int indent) const override { std::cout << std::string(indent, ' ') << "EndAnchor"; }
    // bool match(std::string_view text, size_t& pos) const override {
    //     return pos == text.size();
    // }
};
// ConcatNode represents a concatenation
struct ConcatNode : ASTNode {
    std::vector<std::unique_ptr<ASTNode>> children;
    ConcatNode(std::vector<std::unique_ptr<ASTNode>> children) : children(std::move(children)) { }
    // void accept(Visitor& visitor) override;
    // ConcatNode() { this->type = Type::Concat; }
    // void print(int indent) const override {
    //     std::cout << std::string(indent, ' ') << "Concat(";
    //     for (const auto& child : children) {
    //         child->print(indent + 2);
    //     }
    //     std::cout << ")";
    // }
    // bool match(std::string_view text, size_t& pos) const override {
    //     for (const auto& child : children) {
    //         if (!child->match(text, pos)) {
    //             return false;
    //         }
    //     }
    //     return true;
    // }
};
// GroupNode represents a group (abc)
struct GroupNode : ASTNode {
    int id;
    std::unique_ptr<ASTNode> child;
    GroupNode(int id, std::unique_ptr<ASTNode> child) : id(id), child(std::move(child)) { }
    // void accept(Visitor& visitor) override;
    // GroupNode(int id, std::unique_ptr<ASTNode> child) : id(id), child(std::move(child)) { this->type = Type::Group; }
    // void print(int indent) const override {
    //     std::cout << std::string(indent, ' ') << "Group(" << id << ")";
    //     child->print(indent + 2);
    // }
    // bool match(std::string_view text, size_t& pos) const override {
    //     return child->match(text, pos);
    // }
};
// AlternationNode represents alternation (abc|def)
struct AlternationNode : ASTNode {
    std::vector<std::unique_ptr<ASTNode>> children;
    // void accept(Visitor& visitor) override;
    // AlternationNode() { this->type = Type::Alternation; }
    // void print(int indent) const override {
    //     std::cout << std::string(indent, ' ') << "Alternation(";
    //     child->print(indent + 2);
    //     std::cout << ")";
    // }
};
// QuantifierNode represents a quantifier (abc{3,5})
struct QuantifierNode : ASTNode {
    std::pair<int, int> range;
    QuantifierNode(int l, int r) : range(l, r) { }
    // void accept(Visitor& visitor) override;
    // QuantifierNode(int l, int r) : range(l, r) { this->type = Type::Quantifier; }
    // void print(int indent) const override {
    //     std::cout << std::string(indent, ' ') << "Quantifier(" << range.first << "," << range.second << ")";
    // }
};
// BackreferenceNode represents a backreference (\1)
struct BackreferenceNode : ASTNode {
    int id;
    BackreferenceNode(int id) : id(id) { }
    // void accept(Visitor& visitor) override;
    // BackreferenceNode(int id) : id(id) { this->type = Type::Backreference; }
    // void print(int indent) const override {
    //     std::cout << std::string(indent, ' ') << "Backreference(" << id << ")";
    // }
};

} // namespace Utils
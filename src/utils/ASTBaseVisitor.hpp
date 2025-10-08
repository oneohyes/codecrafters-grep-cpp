#pragma once


namespace Utils {

// Forward declarations of AST node types
struct LiteralNode;
struct DotNode; 
struct DigitNode;
struct WordNode;
struct WhitespaceNode;
struct CharacterGroupNode;
// struct NegativeCharacterGroupNode;
struct StartAnchorNode;
struct EndAnchorNode;
struct ConcatNode;
struct GroupNode;
struct AlternationNode;
struct QuantifierNode;
struct BackreferenceNode;

template <typename R>
class Visitor {
public:
    virtual R visit(const LiteralNode& node) = 0;
    virtual R visit(const DotNode& node) = 0;
    virtual R visit(const DigitNode& node) = 0;
    virtual R visit(const WordNode& node) = 0;
    virtual R visit(const WhitespaceNode& node) = 0;
    virtual R visit(const CharacterGroupNode& node) = 0;
    // virtual R visit(const NegativeCharacterGroupNode& node) = 0;
    virtual R visit(const StartAnchorNode& node) = 0;
    virtual R visit(const EndAnchorNode& node) = 0;
    virtual R visit(const ConcatNode& node) = 0;
    virtual R visit(const GroupNode& node) = 0;
    virtual R visit(const AlternationNode& node) = 0;
    virtual R visit(const QuantifierNode& node) = 0;
    virtual R visit(const BackreferenceNode& node) = 0;
    ~Visitor() = default;
};

}
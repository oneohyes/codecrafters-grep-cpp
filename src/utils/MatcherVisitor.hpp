#pragma once
#include "ASTBaseVisitor.hpp"
#include "ASTNode.hpp"

namespace Utils {
    class MatcherVisitor : public Visitor<bool> {
    private:
        bool match(std::string_view text, const ASTNode* node);
    public:
        bool visit(const LiteralNode& node) override ;
        bool visit(const DotNode& node) override ;
        bool visit(const DigitNode& node) override ;
        bool visit(const WordNode& node) override ;
        bool visit(const WhitespaceNode& node) override ;
        bool visit(const CharacterGroupNode& node) override ;
        // bool visit(const NegativeCharacterGroupNode& node) override ;
        bool visit(const StartAnchorNode& node) override ;
        bool visit(const EndAnchorNode& node) override ;
        bool visit(const ConcatNode& node) override ;
        bool visit(const GroupNode& node) override ;
        bool visit(const AlternationNode& node) override ;
        bool visit(const QuantifierNode& node) override ;
        bool visit(const BackreferenceNode& node) override ;
    };
}

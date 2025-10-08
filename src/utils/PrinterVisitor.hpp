#pragma once
#include "ASTBaseVisitor.hpp"

namespace Utils {

    class PrinterVisitor : public Visitor<void> {
        int depth = 0;
        void indent();
    public:
        void visit(const LiteralNode& node) override ;
        void visit(const DotNode& node) override ;
        void visit(const DigitNode& node) override ;
        void visit(const WordNode& node) override ;
        void visit(const WhitespaceNode& node) override ;
        void visit(const CharacterGroupNode& node) override ;
        // void visit(const NegativeCharacterGroupNode& node) override ;
        void visit(const StartAnchorNode& node) override ;
        void visit(const EndAnchorNode& node) override ;
        void visit(const ConcatNode& node) override ;
        void visit(const GroupNode& node) override ;
        void visit(const AlternationNode& node) override ;
        void visit(const QuantifierNode& node) override ;
        void visit(const BackreferenceNode& node) override ;
    };

} // namespace Utils
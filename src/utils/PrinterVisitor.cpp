# include "PrinterVisitor.hpp"
# include "ASTNode.hpp"

#include <iostream>

namespace Utils {
    void PrinterVisitor::indent() {
        for (int i = 0; i < depth; i++) {
            std::cout << "    ";
        }
    }
    void PrinterVisitor::visit(const LiteralNode& node) {
        indent();
        std::cout << "Literal: " << node.value;
        std::cout << std::endl;
    }
    void PrinterVisitor::visit(const DotNode& ) {
        indent();
        std::cout << "Dot: .";
        std::cout << std::endl;
    }
    void PrinterVisitor::visit(const DigitNode& ) {
        indent();
        std::cout << "Digit: \\d";
        std::cout << std::endl;
    }
    void PrinterVisitor::visit(const WordNode& ) {
        indent();
        std::cout << "Word: \\w";
        std::cout << std::endl;
    }
    void PrinterVisitor::visit(const WhitespaceNode& ) {
        indent();
        std::cout << "Whitespace: \\s";
        std::cout << std::endl;
    }
    void PrinterVisitor::visit(const CharacterGroupNode& node) {
        indent();
        std::cout << "CharacterGroup: [";
        if (node.isNegative) {
            std::cout << "^";
        }
        std::cout << node.chars;
        std::cout << "]";
        std::cout << std::endl;
    }
    // void PrinterVisitor::visit(const NegativeCharacterGroupNode& node) {
    //     indent();
    //     std::cout << "NegativeCharacterGroup: [^";
    //     node.child->accept(*this);
    //     std::cout << "]";
    // }
    void PrinterVisitor::visit(const StartAnchorNode& ) {
        indent();
        std::cout << "StartAnchor: ^";
        std::cout << std::endl;
    }
    void PrinterVisitor::visit(const EndAnchorNode& ) {
        indent();
        std::cout << "EndAnchor: $";
        std::cout << std::endl;
    }
    void PrinterVisitor::visit(const ConcatNode& node) {
        indent();
        std::cout << "Concat: ";
        depth++;
        for (const auto& child : node.children) {
            child->accept(*this);
        }
        depth--;
        std::cout << std::endl;
    }
    void PrinterVisitor::visit(const GroupNode& node) {
        indent();
        std::cout << "Group: (" << node.id << " ";
        depth++;
        node.child->accept(*this);
        depth--;
        std::cout << ")";
        std::cout << std::endl;
    }
    void PrinterVisitor::visit(const AlternationNode& node) {
        indent();
        std::cout << "Alternation: ";
        depth++;
        for (const auto& child : node.children) {
            child->accept(*this);
            std::cout << " | ";
        }
        depth--;
        std::cout << std::endl;
    }
    void PrinterVisitor::visit(const QuantifierNode& node) {
        indent();
        std::cout << "Quantifier: ";
        std::cout << node.range.first;
        if (node.range.first != node.range.second) {
            std::cout << ", ";
            std::cout << node.range.second;
        }
        std::cout << std::endl;
    }
    void PrinterVisitor::visit(const BackreferenceNode& node) {
        indent();
        std::cout << "Backreference: \\";
        std::cout << node.id;
        std::cout << std::endl;
    }
}
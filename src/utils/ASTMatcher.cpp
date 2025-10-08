#include "ASTMatcher.hpp"
#include "ASTParser.hpp"
#include <algorithm>

namespace Utils {

bool ASTMatcher::match(std::string_view text, std::string_view pattern) {
    parse_regex(pattern);
    // return root_ -> match(text)
    return false;    
}

bool ASTMatcher::match_node(const ASTNode* node, std::string_view text, size_t& pos, GroupMap& group) {
    
    switch (node -> type) {
        case ASTNode::Type::Literal: {
            const auto* literalNode = static_cast<const LiteralNode*>(node);
            if (pos < text.size() && text[pos] == literalNode -> value) {
                pos++;
                return true;
            }
            return false;
        }
        case ASTNode::Type::Dot: {
            if (pos < text.size()) {
                pos++;
                return true;
            }
            return false;
        }
    }

    return false;
}

}
#include "ASTParser.hpp"
#include "ASTNode.hpp"
#include <memory>
#include <stdexcept>

namespace Utils {

std::unique_ptr<ASTNode> ASTParser::parse(const std::string& pattern) {
    size_t pos = 0;
    return parseNode(pattern, pos);
}

std::unique_ptr<ASTNode> ASTParser::parseNode(std::string_view pattern, size_t& pos) {
    if (pos >= pattern.size()) {
        return nullptr;
    }

    char ch = pattern[pos];

    // Handle anchors
    if (ch == '^') {
        pos++;
        return std::make_unique<StartAnchorNode>();
    }

    if (ch == '$') {
        pos++;
        return std::make_unique<EndAnchorNode>();
    }

    // Handle dot
    if (ch == '.') {
        pos++;
        return std::make_unique<DotNode>();
    }

    // Handle character groups
    if (ch == '[') {
        return parseCharacterGroup(pattern, pos);
    }

    // Handle groups
    if (ch == '(') {
        return parseGroup(pattern, pos);
    }

    // Handle quantifiers (but we need to handle the expression first)
    std::unique_ptr<ASTNode> node = parseSimpleNode(pattern, pos);

    // Check for quantifiers
    if (pos < pattern.size()) {
        char nextCh = pattern[pos];
        if (nextCh == '*' || nextCh == '+' || nextCh == '?' || nextCh == '{') {
            return parseQuantifier(pattern, pos, std::move(node));
        }
    }

    return node;
}

std::unique_ptr<ASTNode> ASTParser::parseSimpleNode(std::string_view pattern, size_t& pos) {
    if (pos >= pattern.size()) {
        return nullptr;
    }

    char ch = pattern[pos];

    // Handle escape sequences
    if (ch == '\\') {
        pos++;
        if (pos >= pattern.size()) {
            throw std::runtime_error("Invalid escape sequence at end of pattern");
        }
        char escaped = pattern[pos];
        pos++;

        switch (escaped) {
            case 'd':
                return std::make_unique<DigitNode>();
            case 'w':
                return std::make_unique<WordNode>();
            case 's':
                return std::make_unique<WhitespaceNode>();
            case '1': case '2': case '3': case '4': case '5':
            case '6': case '7': case '8': case '9':
                return std::make_unique<BackreferenceNode>(escaped - '0');
            default:
                // Treat as literal
                return std::make_unique<LiteralNode>(escaped);
        }
    }

    // Handle regular literals
    pos++;
    return std::make_unique<LiteralNode>(ch);
}

std::unique_ptr<ASTNode> ASTParser::parseCharacterGroup(std::string_view pattern, size_t& pos) {
    if (pos >= pattern.size() || pattern[pos] != '[') {
        throw std::runtime_error("Expected '[' for character group");
    }
    pos++;

    bool isNegative = false;
    if (pos < pattern.size() && pattern[pos] == '^') {
        isNegative = true;
        pos++;
    }

    std::string chars;
    while (pos < pattern.size() && pattern[pos] != ']') {
        char ch = pattern[pos];
        pos++;

        // Handle character ranges
        if (pos < pattern.size() && pattern[pos] == '-' && pos + 1 < pattern.size() && pattern[pos + 1] != ']') {
            char endChar = pattern[pos + 1];
            pos += 2; // Skip the '-' and the end char

            for (char c = ch; c <= endChar; c++) {
                chars += c;
            }
        } else {
            chars += ch;
        }
    }

    if (pos >= pattern.size()) {
        throw std::runtime_error("Unclosed character group");
    }
    pos++; // Skip the closing ']'

    return std::make_unique<CharacterGroupNode>(isNegative, chars);
}

std::unique_ptr<ASTNode> ASTParser::parseGroup(std::string_view pattern, size_t& pos) {
    if (pos >= pattern.size() || pattern[pos] != '(') {
        throw std::runtime_error("Expected '(' for group");
    }
    pos++;

    // For now, we'll implement simple groups without named groups
    std::unique_ptr<ASTNode> child = parseNode(pattern, pos);

    if (pos >= pattern.size() || pattern[pos] != ')') {
        throw std::runtime_error("Unclosed group");
    }
    pos++; // Skip the closing ')'

    static int groupId = 0;
    return std::make_unique<GroupNode>(groupId++, std::move(child));
}

std::unique_ptr<ASTNode> ASTParser::parseQuantifier(std::string_view pattern, size_t& pos, std::unique_ptr<ASTNode> child) {
    char quantifier = pattern[pos];
    pos++;

    switch (quantifier) {
        case '*':
            return std::make_unique<QuantifierNode>(std::move(child), 0, -1); // 0 or more
        case '+':
            return std::make_unique<QuantifierNode>(std::move(child), 1, -1); // 1 or more
        case '?':
            return std::make_unique<QuantifierNode>(std::move(child), 0, 1);  // 0 or 1
        case '{': {
            // Parse {min,max} format
            size_t startPos = pos;
            while (pos < pattern.size() && pattern[pos] != '}') {
                pos++;
            }

            if (pos >= pattern.size()) {
                throw std::runtime_error("Unclosed quantifier");
            }

            std::string rangeStr(pattern.substr(startPos, pos - startPos));
            pos++; // Skip the closing '}'

            // Parse min,max
            size_t commaPos = rangeStr.find(',');
            int min, max;

            if (commaPos == std::string::npos) {
                // Single number {n}
                min = max = std::stoi(rangeStr);
            } else {
                // {min,max}
                std::string minStr = rangeStr.substr(0, commaPos);
                std::string maxStr = rangeStr.substr(commaPos + 1);

                min = minStr.empty() ? 0 : std::stoi(minStr);
                max = maxStr.empty() ? -1 : std::stoi(maxStr);
            }

            return std::make_unique<QuantifierNode>(std::move(child), min, max);
        }
        default:
            throw std::runtime_error("Invalid quantifier");
    }
}

}
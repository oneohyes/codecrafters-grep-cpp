#include "Lexer.hpp"
#include <vector>
#include <cctype>
namespace Utils {
std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens(pattern.size());
    while (pos < pattern.size()) {
        char ch = pattern[pos];
        switch (ch) {
            case '(': tokens.push_back({Token::Type::LPAREN, ch}); break;
            case ')': tokens.push_back({Token::Type::RPAREN, ch}); break;
            case '[': tokens.push_back({Token::Type::LBRACKET, ch}); break;
            case ']': tokens.push_back({Token::Type::RBRACKET, ch}); break;
            case '|': tokens.push_back({Token::Type::ALTERNATION, ch}); break;
            case '*': tokens.push_back({Token::Type::STAR, ch}); break;
            case '+': tokens.push_back({Token::Type::PLUS, ch}); break;
            case '?': tokens.push_back({Token::Type::QUESTION, ch}); break;
            case '{': tokens.push_back({Token::Type::LBRACE, ch}); break;
            case '}': tokens.push_back({Token::Type::RBRACE, ch}); break;
            case ',': tokens.push_back({Token::Type::COMMA, ch}); break;
            case '^': tokens.push_back({Token::Type::CARET, ch}); break;
            case '$': tokens.push_back({Token::Type::DOLLAR, ch}); break;
            case '.': tokens.push_back({Token::Type::DOT, ch}); break;
            case '\\': 
                pos++;
                ch = pattern[pos];
                if (pos < pattern.size()) {
                    char next_ch = pattern[pos];
                    switch (ch) {
                        case 'd':
                            tokens.push_back({Token::Type::DIGIT, next_ch});
                            break;
                        case 'w':
                            tokens.push_back({Token::Type::WORD, next_ch});
                            break;
                        case 's':
                            tokens.push_back({Token::Type::WHITESPACE, next_ch});
                            break;
                        default:
                            tokens.push_back({Token::Type::LITERAL, next_ch});
                            break;
                    }
                } else {
                    // Handle error: dangling backslash
                }
                break;
            default:
                if (std::isdigit(ch)) {
                    tokens.push_back({Token::Type::NUMBER, ch});
                } else {
                    tokens.push_back({Token::Type::LITERAL, ch});
                }
                break;
        }
        pos++;
    }
    return tokens;
};
}
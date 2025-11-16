#pragma once
#include <string_view>
#include <vector>
namespace Utils {

class Token {
    public:
    enum class Type {
        LPAREN,     // e.g., '('
        RPAREN,     // e.g., ')'
        LBRACKET,   // e.g., '['
        RBRACKET,   // e.g., ']'
        ALTERNATION,// e.g., '|'
        STAR,       // e.g., '*', etc.
        PLUS,       // e.g., '+'
        QUESTION,   // e.g., '?'
        LBRACE,     // e.g., '{'
        RBRACE,     // e.g., '}'
        COMMA,      // e.g., ','
        CARET,      // e.g., '^'
        DOLLAR,     // e.g., '$'
        PIPE,       // e.g., '|'
        DOT,        // e.g., '.'
        NUMBER,     // e.g., '0'-'9'
        DIGIT,      // e.g., '\d' = [0-9]
        WORD,       // e.g., '\w' = [A-Za-z0-9_]
        WHITESPACE, // e.g., '\s' = [ \t\n\r\f\v]
        LITERAL     // e.g., any literal character
    };
    Type type{};
    char value{};
};


class Lexer {
public:
    explicit Lexer(std::string_view pattern) : pattern(pattern), pos(0) {}
    std::vector<Token> tokenize();
    private:
    std::string_view pattern;
    size_t pos;
};
}
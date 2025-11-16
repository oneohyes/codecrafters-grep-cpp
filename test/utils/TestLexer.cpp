#include <string>

#include "Lexer.hpp"
#include <gtest/gtest.h>

namespace {

class TestLexer : public ::testing::Test {
protected:
    Utils::Lexer lexer;    // The lexer object to be tested
    void SetUp() override {
        // This function runs before each test
    }
    void TearDown() override {
        // This function runs after each test
    }
};

TEST_F(TestLexer, TokenizeSimplePattern) {
    std::string pattern = "(a|b)*c+";
    lexer = Utils::Lexer(pattern);
    auto tokens = lexer.tokenize();
    std::vector<Utils::Token::Type> expectedTypes = {
        Utils::Token::Type::LPAREN,
        Utils::Token::Type::LITERAL,
        Utils::Token::Type::ALTERNATION,
        Utils::Token::Type::LITERAL,
        Utils::Token::Type::RPAREN,
        Utils::Token::Type::STAR,
        Utils::Token::Type::LITERAL,
        Utils::Token::Type::PLUS
    };
    std::string expectedValues = pattern;
    ASSERT_EQ(tokens.size(), expectedTypes.size());
    for (size_t i = 0; i < tokens.size(); ++i) {
        EXPECT_EQ(tokens[i].type, expectedTypes[i]);
        EXPECT_EQ(tokens[i].value, expectedValues[i]);
    }
}
}
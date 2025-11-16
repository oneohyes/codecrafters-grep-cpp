#pragma once
#include "ASTNode.hpp"
#include <memory>
#include <string>
#include <string_view>


// imput: ""
namespace Utils {
class ASTParser {
public:
    std::unique_ptr<ASTNode> parse(const std::string& pattern);
private:

    std::unique_ptr<ASTNode> parseNode(std::string_view pattern, size_t& pos);
    std::unique_ptr<ASTNode> parseSimpleNode(std::string_view pattern, size_t& pos);
    std::unique_ptr<ASTNode> parseCharacterGroup(std::string_view pattern, size_t& pos);
    std::unique_ptr<ASTNode> parseGroup(std::string_view pattern, size_t& pos);
    std::unique_ptr<ASTNode> parseQuantifier(std::string_view pattern, size_t& pos, std::unique_ptr<ASTNode> child);
};
}



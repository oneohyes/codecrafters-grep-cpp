#pragma once

#include "ASTParser.hpp"
#include <string>
#include <string_view>
#include <unordered_map>

namespace Utils {

class ASTMatcher {
    struct GroupCapture {
        size_t start;
        size_t end;
    };
    using GroupMap = std::unordered_map<int, GroupCapture>;
public: 
    void parse_regex(std::string_view pattern);
    bool match(std::string_view text, std::string_view pattern);
private:
    bool match_node(const ASTNode* node, std::string_view text, size_t& pos, GroupMap& group);
};

} // namespace Utils

#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>

bool match_digit(const std::string &input) {
    return std::any_of(
        input.begin(),
        input.end(),
        [](char c){return std::isdigit(c);}
    );
}

bool match_alpha(const std::string &input) {
    return std::any_of(
        input.begin(),
        input.end(),
        [](char c){return std::isalpha(c);}
    );
}

bool match_alphanumeric (const std::string &input) {
    return std::any_of(
        input.begin(),
        input.end(),
        [](char c){return std::isalnum(c) || c == '_';}
    );
}

// match positive character group
bool match_positive_group (const std::string &input, const std::string &pattern) {
    return input.find_first_of(pattern) != std::string::npos;
}
// match negative character group
bool match_negative_group (const std::string &input, const std::string &pattern) {
    return input.find_first_not_of(pattern) != std::string::npos;
}

bool match_pattern(const std::string& input_line, const std::string& pattern) {
    if (pattern.length() == 1) {
        return input_line.find(pattern) != std::string::npos;
    }
    if (pattern.size() > 2 && pattern[0] == '[' && pattern[pattern.size()-1] == ']') {
        if(pattern[1] == '^') {
            return match_negative_group(input_line, pattern.substr(2, pattern.size()-3));
        } else {
            return  match_positive_group(input_line, pattern.substr(1, pattern.size()-2));
        }
    }
    if (pattern.compare("\\d") == 0) {
        return match_digit(input_line);
    } else if (pattern.compare("\\w") == 0) {
        return match_alphanumeric(input_line) ;
    } 
    else {
        throw std::runtime_error("Unhandled pattern " + pattern);
    }
}

int main(int argc, char* argv[]) {
    // Flush after every std::cout / std::cerr
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    // You can use print statements as follows for debugging, they'll be visible when running tests.
    // std::cerr << "Logs from your program will appear here" << std::endl;

    if (argc != 3) {
        std::cerr << "Expected two arguments" << std::endl;
        return 1;
    }

    std::string flag = argv[1];
    std::string pattern = argv[2];

    if (flag != "-E") {
        std::cerr << "Expected first argument to be '-E'" << std::endl;
        return 1;
    }

    // Uncomment this block to pass the first stage
    //
    std::string input_line;
    std::getline(std::cin, input_line);
    
    try {
        if (match_pattern(input_line, pattern)) {
            std::cout << 0 << std::endl;
            return 0;
        } else {
            std::cout << 0 << std::endl;
            return 1;
        }
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}

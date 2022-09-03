#pragma once

#include <string>
#include <vector>

namespace Just {
struct ParseString {
    template<typename T>
    static T ToNumeric(const std::string& str);

    static std::vector<std::string> GetSubStringsByDelimiter(const std::string& str, const std::string& delimiter);
};

template<typename T>
T ParseString::ToNumeric(const std::string& str) {
    char* end = nullptr;
    T result = static_cast<T>(strtoul(str.c_str(), &end, 10));
    assert(*end == '\0');
    return result;
}

std::vector<std::string> ParseString::GetSubStringsByDelimiter(const std::string& str, const std::string& delimiter) {
    std::string::size_type currPos = 0;
    std::string::size_type nextPos = str.find(delimiter, currPos);
    std::vector<std::string> tokens;
    while (currPos != std::string::npos) {
        if (nextPos != currPos) {
            tokens.push_back(str.substr(currPos, nextPos));
        }
        currPos = nextPos;
        if (currPos != std::string::npos) {
            currPos++;
            nextPos = str.find_first_of(delimiter, currPos);
        }
    }
    return tokens;
}

}
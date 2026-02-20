//
// Created by masti on 2/20/2026.
//

#include "Utilities.h"
#include <regex>
#include <stdexcept>

namespace seneca {

    char Utilities::m_delimiter = ',';

    std::string Utilities::trim(const std::string &str) {

        const std::regex pattern(R"(^\s+|\s+$)");
        return std::regex_replace(str, pattern, std::string());
    }
    void Utilities::setFieldWidth(const size_t newWidth) {

        m_widthField = newWidth;
    }
    size_t Utilities::getFieldWidth() const {

        return m_widthField;
    }
    std::string Utilities::extractToken(const std::string &str, size_t &next_pos, bool &more) {

        if (next_pos >= str.length()) {
            more = false;
            return "";
        }
        if (str[next_pos] == m_delimiter) {
            more = false;
            throw std::invalid_argument("Extra token");
        }
        const size_t end_pos = str.find(m_delimiter, next_pos);
        std::string token;
        if (end_pos != std::string::npos) {
            token = str.substr(next_pos, end_pos - next_pos);
            next_pos = end_pos + 1;
            more = true;
        }
        else {
            token = str.substr(next_pos);
            next_pos = str.length();
            more = false;
        }
        token = trim(token);
        if (token.empty()) throw std::invalid_argument("Empty token");
        if (token.length() > m_widthField) m_widthField = token.length();
        return token;
    }
    void Utilities::setDelimiter(char newDelimiter) {

        m_delimiter = newDelimiter;
    }
    char Utilities::getDelimiter() {

        return m_delimiter;
    }
}

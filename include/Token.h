#pragma once

#include <string>

class Token {
public:
    const int m_Type;
    const std::string m_Text;

    const int m_StartIndex;
    const int m_Line;

    Token(int type, const std::string &text, int line, int startIndex);
    ~Token();
};

std::ostream& operator<<(std::ostream &strm, const Token &tok);

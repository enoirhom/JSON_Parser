#pragma once

#include <string>

class Token {
public:
    const int m_Type;
    const std::string m_Text;

    Token(int type, const std::string &text);
    ~Token();
};

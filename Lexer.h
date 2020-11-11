#pragma once

#include "Token.h"

class Lexer {
public:
    static const int EOF_TYPE = 0, LCURL = 1, RCURL = 2, LBRACK = 3, RBRACK = 4,
        COLON = 5, COMMA = 6, STRING = 7, NUMBER = 8;

    Lexer(std::string &input);
    ~Lexer();
    Token nextToken();

private:
    char m_CurrentChar;
    int m_Index;
    std::string m_Input;

    void consume();

    void WS();
    Token STRINGF();
    Token NUMBERF();
};

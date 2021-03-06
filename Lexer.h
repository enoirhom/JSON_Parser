#pragma once

#include <fstream>
#include "Token.h"

class Lexer {
public:
    static const int EOF_TYPE = 1, LCURL = 2, RCURL = 3, LBRACK = 4, RBRACK = 5,
        COLON = 6, COMMA = 7, STRING = 8, NUMBER = 9;
    static std::string TOKEN_NAMES[];

    Lexer(const std::string &input);
    ~Lexer();
    Token* nextToken();

private:
    char m_CurrentChar;
    int m_Index;
    std::ifstream m_Input;

    void consume();
    void consume(std::string &buff);

    void WS();
    Token* STRINGF();
    Token* NUMBERF();
    void INTEGERF(std::string &buff);
    void FRACTIONF(std::string &buff);
    void EXPONENTF(std::string &buff);
    void DIGITS(std::string &buff);

    void printState();
    bool isWS();
};

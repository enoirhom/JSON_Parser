#pragma once

#include <istream>
#include "Token.hpp"

class Lexer {
public:
    static const int EOF_TYPE = 1, LCURL = 2, RCURL = 3, LBRACK = 4, RBRACK = 5,
        COLON = 6, COMMA = 7, TRUE = 8, FALSE = 9, NULL_LIT = 10, STRING = 11,
        NUMBER = 12;
    static std::string TOKEN_NAMES[];

    Lexer(std::istream* stream);
    ~Lexer();
    Token* nextToken();

private:
    std::istream* m_Input;
    int m_Line;
    int m_IndexInLine;

    char m_CurrentChar;
    char m_LookaheadChar;

    void consume();
    void consume(std::string &buff);

    void WS();
    Token* STRINGF();
    Token* NUMBERF();
    void INTEGERF(std::string &buff);
    void FRACTIONF(std::string &buff);
    void EXPONENTF(std::string &buff);
    void DIGITS(std::string &buff);

    void getNextChar();
    bool isWS();
};

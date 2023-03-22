#pragma once

#include "Lexer.hpp"
#include "Token.hpp"

class Parser {
public:
    Parser(Lexer &lexer);
    ~Parser();
    void json();
    void obj();
    void pair();
    void arr();
    void value();

private:
    Lexer &m_Input;
    Token *m_Lookahead;

    void match(int type);
    void consume();

    bool lookForValue();
};

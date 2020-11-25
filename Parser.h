#pragma once

#include "Lexer.h"
#include "Token.h"

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

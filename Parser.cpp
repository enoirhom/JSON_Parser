#include "Parser.h"

Parser::Parser(Lexer &lexer) : m_Input(lexer), m_Lookahead(nullptr) {
    consume();
}

Parser::~Parser() {
    if (m_Lookahead != nullptr) {
        delete m_Lookahead;
    }
}

void Parser::json() {
    value();
}

void Parser::obj() {
    match(Lexer::LCURL);
    if (m_Lookahead->m_Type == Lexer::STRING) {
        pair();
        while (m_Lookahead->m_Type == Lexer::COMMA) {
            match(Lexer::COMMA);
            pair();
        }
    }
    match(Lexer::RCURL);
}

void Parser::pair() {
    match(Lexer::STRING);
    match(Lexer::COLON);
    value();
}

void Parser::arr() {
    match(Lexer::LBRACK);
    if (lookForValue()) {
        value();
        while (m_Lookahead->m_Type == Lexer::COMMA) {
            match(Lexer::COMMA);
            value();
        }
    }
    match(Lexer::RBRACK);
}

void Parser::value() {
    if (m_Lookahead->m_Type == Lexer::STRING) {
        match(Lexer::STRING);
    } else if (m_Lookahead->m_Type == Lexer::NUMBER) {
        match(Lexer::NUMBER);
    } else if (m_Lookahead->m_Type == Lexer::LCURL) {
        obj();
    } else if (m_Lookahead->m_Type == Lexer::LBRACK) {
        arr();
    } else {
        throw "error Parser::value()";
    }
}

void Parser::match(int type) {
    if (m_Lookahead->m_Type == type) {
        consume();
    } else {
        throw "error Parser::match()";
    }
}

void Parser::consume() {
    if (m_Lookahead != nullptr) {
        delete m_Lookahead;
    }
    m_Lookahead = m_Input.nextToken();
}

bool Parser::lookForValue() {
    return m_Lookahead->m_Type == Lexer::STRING ||
            m_Lookahead->m_Type == Lexer::NUMBER ||
            m_Lookahead->m_Type == Lexer::LCURL ||
            m_Lookahead->m_Type == Lexer::LBRACK;
}

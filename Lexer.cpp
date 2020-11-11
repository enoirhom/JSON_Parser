#include <iostream>
#include <cctype>
#include "Lexer.h"

Lexer::Lexer(std::string &input) : m_Input(input) {
    m_Index = 0;
    m_CurrentChar = m_Input[m_Index];
    std::cout << "Create Lexer" << std::endl;
}

Lexer::~Lexer() {
    std::cout << "Delete Lexer" << std::endl;
}

Token Lexer::nextToken() {
    while (m_CurrentChar != '\0') {
        if (m_CurrentChar == ' ' || m_CurrentChar == '\t' ||
                m_CurrentChar == '\n' || m_CurrentChar == '\r') {
            WS();
        }
        switch (m_CurrentChar) {
        case '{':
            consume();
            return Token(LCURL, "{");
        case '}':
            consume();
            return Token(RCURL, "}");
        case '[':
            consume();
            return Token(LBRACK, "[");
        case ']':
            consume();
            return Token(RBRACK, "]");
        case ':':
            consume();
            return Token(COLON, ":");
        case ',':
            consume();
            return Token(COMMA, ",");
        default:
            if (m_CurrentChar == '"') {
                return STRINGF();
            } else if (m_CurrentChar == '+' || m_CurrentChar == '-' ||
                    isdigit(m_CurrentChar)) {
                return NUMBERF();
            } else {
                throw "Token Lexer::nextToken()";
            }
        }
    }
    return Token(EOF_TYPE, "<EOF>");
}

void Lexer::consume() {
    m_Index++;
    m_CurrentChar = m_Input[m_Index];
}

void Lexer::WS() {
    while (m_CurrentChar == ' ' || m_CurrentChar == '\t' ||
            m_CurrentChar == '\n' || m_CurrentChar == '\r') {
        consume();
    }
}

Token Lexer::STRINGF() {
    std::string buff;
    do {
        buff += m_CurrentChar;
        consume();
    } while(m_CurrentChar != '"');

    return Token(STRING, buff);
}

Token Lexer::NUMBERF() {
    std::string buff;
    do {
        buff += m_CurrentChar;
        consume();
    } while(isdigit(m_CurrentChar));

    return Token(NUMBER, buff);
}

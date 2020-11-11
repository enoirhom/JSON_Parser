#include <iostream>
#include <cctype>
#include "Lexer.h"

Lexer::Lexer(const std::string &input) : m_Input(input) {
    m_Index = 0;
    m_CurrentChar = m_Input[m_Index];
    std::cout << "Create Lexer" << std::endl;
}

Lexer::~Lexer() {
    std::cout << "Delete Lexer" << std::endl;
}

Token* Lexer::nextToken() {
    while (m_CurrentChar != '\0') {
        if (m_CurrentChar == ' ' || m_CurrentChar == '\t' ||
                m_CurrentChar == '\n' || m_CurrentChar == '\r') {
            WS();
        }
        switch (m_CurrentChar) {
        case '{':
            consume();
            return new Token(LCURL, "{");
        case '}':
            consume();
            return new Token(RCURL, "}");
        case '[':
            consume();
            return new Token(LBRACK, "[");
        case ']':
            consume();
            return new Token(RBRACK, "]");
        case ':':
            consume();
            return new Token(COLON, ":");
        case ',':
            consume();
            return new Token(COMMA, ",");
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
    return new Token(EOF_TYPE, "<EOF>");
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

Token* Lexer::STRINGF() {
    std::string buff;
    do {
        buff += m_CurrentChar;
        consume();
    } while(m_CurrentChar != '"');
    consume();

    return new Token(STRING, buff);
}

Token* Lexer::NUMBERF() {
    std::string buff;
    do {
        buff += m_CurrentChar;
        consume();
    } while(isdigit(m_CurrentChar));

    return new Token(NUMBER, buff);
}

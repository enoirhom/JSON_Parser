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
            continue;
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
            } else if (m_CurrentChar == '-' || isdigit(m_CurrentChar)) {
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

void Lexer::consume(std::string &buff) {
    buff += m_CurrentChar;
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
        consume(buff);
    } while(m_CurrentChar == '_' || isalpha(m_CurrentChar));

    if (m_CurrentChar == '"') {
        consume(buff);
    } else {
        throw "invalid char in string";
    }

    return new Token(STRING, buff);
}

Token* Lexer::NUMBERF() {
    std::string buff;

    INTEGERF(buff);
    FRACTIONF(buff);
    EXPONENTF(buff);

    if (m_CurrentChar != ' ' && m_CurrentChar != '\t' &&
            m_CurrentChar != '\n' && m_CurrentChar != '\r' && m_CurrentChar != 0) {
        throw "invalid char, expecting white space or end of string char";
    }

    return new Token(NUMBER, buff);
}

void Lexer::INTEGERF(std::string &buff) {
    if (m_CurrentChar == '-') {
        consume(buff);
    }

    if (m_CurrentChar == '0') {
        consume(buff);
    } else if (isdigit(m_CurrentChar)) {
        do {
            consume(buff);
        } while(isdigit(m_CurrentChar));
    } else {
        throw "invalid char, expecting digit";
    }
}

void Lexer::FRACTIONF(std::string &buff) {
    if (m_CurrentChar == '.') {
        consume(buff);

        DIGITS(buff);
    }
}

void Lexer::EXPONENTF(std::string &buff) {
    if (m_CurrentChar == 'e' || m_CurrentChar == 'E') {
        consume(buff);

        if (m_CurrentChar != '+' && m_CurrentChar != '-') {
            throw "invalid char, expecting + or -";
        }
        consume(buff);

        DIGITS(buff);
    }

}

void Lexer::DIGITS(std::string &buff) {
    if (!isdigit(m_CurrentChar)) {
        throw "invalid char, expecting digit";
    }

    while (isdigit(m_CurrentChar)) {
        consume(buff);
    }
}

#include <iostream>
#include <cctype>
#include "Lexer.h"

Lexer::Lexer(const std::string &input) : m_Input(std::ifstream(input)) {
    m_Index = 0;
    consume();
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
                printState();
                throw "Token Lexer::nextToken()";
            }
        }
    }
    return new Token(EOF_TYPE, "<EOF>");
}

void Lexer::consume() {
    m_Index++;
    if (!(m_Input >> m_CurrentChar)) {
        m_CurrentChar = '\0';
    }
}

void Lexer::consume(std::string &buff) {
    buff += m_CurrentChar;
    consume();
}

void Lexer::WS() {
    while (m_CurrentChar == ' ' || m_CurrentChar == '\t' ||
            m_CurrentChar == '\n' || m_CurrentChar == '\r') {
        consume();
    }
}

Token* Lexer::STRINGF() {
    std::string buff;

    consume();

    while (m_CurrentChar != '"' && m_CurrentChar != '\0') {
        if (m_CurrentChar == '\\') {
            consume(buff);
            if (!(m_CurrentChar == '"' || m_CurrentChar == '\\' || m_CurrentChar == '/' ||
                    m_CurrentChar == 'b' || m_CurrentChar == 'f' ||
                    m_CurrentChar == 'n' || m_CurrentChar == 'r' ||
                    m_CurrentChar == 't')) {
                printState();
                throw "invalid escape char";
            }
        }
        consume(buff);
    }

    if (m_CurrentChar == '"') {
        consume();
    } else {
        printState();
        throw "reaching end of file before end of string";
    }

    return new Token(STRING, buff);
}

Token* Lexer::NUMBERF() {
    std::string buff;

    INTEGERF(buff);
    FRACTIONF(buff);
    EXPONENTF(buff);

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
        printState();
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
            printState();
            throw "invalid char, expecting + or -";
        }
        consume(buff);

        DIGITS(buff);
    }

}

void Lexer::DIGITS(std::string &buff) {
    if (!isdigit(m_CurrentChar)) {
        printState();
        throw "invalid char, expecting digit";
    }

    while (isdigit(m_CurrentChar)) {
        consume(buff);
    }
}

void Lexer::printState() {
    std::cout << "m_CurrentChar: '" << m_CurrentChar << "' m_Index: " << m_Index << std::endl;
}

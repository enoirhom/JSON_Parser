#include <cctype>
#include <iostream>
#include "Lexer.h"

std::string Lexer::TOKEN_NAMES[] = {"n/a", "<EOF>", "LCURL", "RCURL", "LBRACK", "RBRACK", "COLON", "COMMA", "STRING", "NUMBER"};

Lexer::Lexer(std::istream* stream) : m_Input(stream), m_Line(1), m_IndexInLine(0) {
    m_Input->unsetf(std::ios_base::skipws);
    getNextChar();
}

Lexer::~Lexer() { }

Token* Lexer::nextToken() {
    consume();
    WS();

    switch (m_CurrentChar) {
    case '\0':
        return new Token(EOF_TYPE, "<EOF>", m_Line, m_IndexInLine);
    case '{':
        return new Token(LCURL, "{", m_Line, m_IndexInLine);
    case '}':
        return new Token(RCURL, "}", m_Line, m_IndexInLine);
    case '[':
        return new Token(LBRACK, "[", m_Line, m_IndexInLine);
    case ']':
        return new Token(RBRACK, "]", m_Line, m_IndexInLine);
    case ':':
        return new Token(COLON, ":", m_Line, m_IndexInLine);
    case ',':
        return new Token(COMMA, ",", m_Line, m_IndexInLine);
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

void Lexer::consume() {
    m_IndexInLine += 1;
    m_CurrentChar = m_LookaheadChar;

    getNextChar();

    if (m_CurrentChar == '\n') {
        m_Line += 1;
        m_IndexInLine = 0;
    }
}

void Lexer::consume(std::string &buff) {
    buff += m_CurrentChar;
    consume();
}

void Lexer::WS() {
    while (isWS()) {
        consume();
    }
}

Token* Lexer::STRINGF() {
    std::string buff;

    consume();

    int start = m_IndexInLine;

    while (m_CurrentChar != '"' && m_CurrentChar != '\0') {
        if (m_CurrentChar == '\\') {
            consume(buff);
            if (!(m_CurrentChar == '"' || m_CurrentChar == '\\' ||
                    m_CurrentChar == '/' || m_CurrentChar == 'b' ||
                    m_CurrentChar == 'f' || m_CurrentChar == 'n' ||
                    m_CurrentChar == 'r' || m_CurrentChar == 't')) {
                throw "invalid escape char";
            }
        }
        consume(buff);
    }

    if (m_CurrentChar != '"') {
        throw "reaching end of file before end of string";
    }

    return new Token(STRING, buff, m_Line, start);
}

Token* Lexer::NUMBERF() {
    std::string buff;

    int start = m_IndexInLine;

    INTEGERF(buff);
    FRACTIONF(buff);
    EXPONENTF(buff);

    return new Token(NUMBER, buff, m_Line, start);
}

void Lexer::INTEGERF(std::string &buff) {
    if (m_CurrentChar == '-') {
        consume(buff);
    }

    if (m_CurrentChar == '0') {
        consume(buff);
    } else if (isdigit(m_CurrentChar)) {
        while (isdigit(m_LookaheadChar)) {
            consume(buff);
        }
        buff += m_CurrentChar;
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

void Lexer::getNextChar() {
    if (!((*m_Input) >> m_LookaheadChar)) {
        m_CurrentChar = '\0';
    }
}

bool Lexer::isWS() {
    return m_CurrentChar == ' ' || m_CurrentChar == '\t' ||
            m_CurrentChar == '\n' || m_CurrentChar == '\r';
}

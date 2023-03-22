#include <cctype>
#include <iostream>
#include "../include/Lexer.hpp"

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
            if (m_CurrentChar == 't') {
                TRUEF();
                return new Token(TRUE, "true", m_Line, m_IndexInLine);
            } else if (m_CurrentChar == 'f') {
                FALSEF();
                return new Token(FALSE, "false", m_Line, m_IndexInLine);
            } else if (m_CurrentChar == 'n') {
                NULLF();
                return new Token(NULL_TYPE, "null", m_Line, m_IndexInLine);
            } else {
                throw "Token Lexer::nextToken()";
            }
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
            // TODO: add unicode codepoint (i.e.: \u000A)
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
        buff += m_CurrentChar;
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
    consume();
    if (m_CurrentChar == '.') {
        consume(buff);

        DIGITS(buff);
    }
}

void Lexer::EXPONENTF(std::string &buff) {
    if (m_CurrentChar == 'e' || m_CurrentChar == 'E') {
        consume(buff);

        if (m_CurrentChar == '+' || m_CurrentChar == '-') {
            consume(buff);
        }

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

void Lexer::TRUEF() {
    match('t');
    match('r');
    match('u');

    if (m_CurrentChar != 'e') {
        // do something!
    }
}

void Lexer::FALSEF() {
    match('f');
    match('a');
    match('l');
    match('s');

    if (m_CurrentChar != 'e') {
        // do something!
    }
}

void Lexer::NULLF() {
    match('n');
    match('u');
    match('l');

    if (m_CurrentChar != 'l') {
        // do something!
    }
}

void Lexer::getNextChar() {
    if (!((*m_Input) >> m_LookaheadChar)) {
        m_LookaheadChar = '\0';
    }
}

void Lexer::match(char c) {
    if (m_CurrentChar == c) {
        consume();
    } else {
        std::string message = "invalid char, expecting ";
        message += c;
        throw message;
    }
}

bool Lexer::isWS() {
    return m_CurrentChar == ' ' || m_CurrentChar == '\t' ||
            m_CurrentChar == '\n' || m_CurrentChar == '\r';
}

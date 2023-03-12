#include <iostream>
#include "Token.h"
#include "Lexer.h"

std::ostream& operator<<(std::ostream &strm, const Token &tok) {
    return strm << "Token(" << Lexer::TOKEN_NAMES[tok.m_Type] << " at " << tok.m_Line << ":" << tok.m_StartIndex << ", " << tok.m_Text << ")";
}

Token::Token(int type, const std::string &text, int line, int startIndex) : m_Type(type), m_Text(text), m_StartIndex(startIndex), m_Line(line) { }

Token::~Token() { }

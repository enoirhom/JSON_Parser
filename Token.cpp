#include <iostream>
#include "Token.h"
#include "Log.h"
#include "Lexer.h"

std::ostream& operator<<(std::ostream &strm, const Token &tok) {
    return strm << "Token(" << Lexer::TOKEN_NAMES[tok.m_Type] << ", " << tok.m_Text << ")";
}

Token::Token(int type, const std::string &text) : m_Type(type), m_Text(text) {
    l.printOLC("Create Token");
}

Token::~Token() {
    l.printOLC("Delete Token");
}

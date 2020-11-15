#include <iostream>
#include "Token.h"

std::ostream& operator<<(std::ostream &strm, const Token &tok) {
    return strm << "Token(" << tok.m_Type << ", " << tok.m_Text << ")";
}

Token::Token(int type, const std::string &text) : m_Type(type), m_Text(text) {
    std::cout << "Create Token" << std::endl;
}

Token::~Token() {
    std::cout << "Delete Token" << std::endl;
}

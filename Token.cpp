#include <iostream>
#include "Token.h"

Token::Token(int type, const std::string &text) : m_Type(type), m_Text(text) {
    std::cout << "Create Token" << std::endl;
}

Token::~Token() {
    std::cout << "Delete Token" << std::endl;
}

#include <iostream>
#include "Token.h"
#include "Lexer.h"


int main(int argc, const char *argv[]) {

    if (argc == 2) {
        std::cout << argv[1] << std::endl;
        Lexer lexer(argv[1]);
        Token *tok = lexer.nextToken();
        while (tok->m_Type != Lexer::EOF_TYPE) {
            std::cout << "Type: " << tok->m_Type << ", " << tok->m_Text << std::endl;
            delete tok;
            tok = lexer.nextToken();
        }
    }

    return 0;
}

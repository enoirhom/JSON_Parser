#include <iostream>
#include "Token.h"
#include "Lexer.h"


int main(int argc, const char *argv[]) {

    if (argc == 2) {
        try {
            std::cout << argv[1] << std::endl;
            Lexer lexer(argv[1]);
            Token *tok = lexer.nextToken();
            while (tok->m_Type != Lexer::EOF_TYPE) {
                std::cout << "Type: " << *tok << std::endl;
                delete tok;
                tok = lexer.nextToken();
            }
        } catch(char const *e) {
            std::cout << e << std::endl;
        }
    }

    return 0;
}

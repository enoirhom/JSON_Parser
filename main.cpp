#include <iostream>
#include "Token.h"
#include "Lexer.h"
#include "Parser.h"

int main(int argc, const char *argv[]) {

    if (argc == 2) {
        try {
            Lexer lexer(argv[1]);
            Parser parser(lexer);
            parser.json();
        } catch(char const *e) {
            std::cout << e << std::endl;
        }
    }

    return 0;
}

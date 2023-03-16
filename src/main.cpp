#include <iostream>
#include <fstream>
#include "Token.h"
#include "Lexer.h"
#include "Parser.h"

int main(int argc, const char *argv[]) {

    if (argc == 2) {
        try {
            std::ifstream stream(argv[1]);
            Lexer lexer(&stream);
            Parser parser(lexer);
            parser.json();
        } catch(char const *e) {
            std::cout << e << std::endl;
        }
    }

    return 0;
}

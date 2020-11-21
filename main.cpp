#include "Token.h"
#include "Lexer.h"
#include "Log.h"

Log l;

int main(int argc, const char *argv[]) {
    l.setMode(Log::TOK);
    l.setMode(Log::ERR);
    l.setMode(Log::MESS);

    if (argc == 2) {
        try {
            l.printMess(argv[1]);
            Lexer lexer(argv[1]);
            Token *tok = nullptr;
            while (tok == nullptr || tok->m_Type != Lexer::EOF_TYPE) {
                tok = lexer.nextToken();
                l.printTok(*tok);
                delete tok;
            }
        } catch(char const *e) {
            l.printErr(e);
        }
    }

    return 0;
}

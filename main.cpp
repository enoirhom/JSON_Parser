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
            Token *tok = lexer.nextToken();
            while (tok->m_Type != Lexer::EOF_TYPE) {
                l.printTok(*tok);
                delete tok;
                tok = lexer.nextToken();
            }
        } catch(char const *e) {
            l.printErr(e);
        }
    }

    return 0;
}

#pragma once

#include <string>
#include "Token.h"

class Log {
public:
    enum Mode : unsigned char {OLC = 1, ERR = 2, TOK = 4, MESS = 8};

    Log();

    void setMode(Mode m);
    void unsetMode(Mode m);

    void printOLC(const std::string &message) const;
    void printErr(const std::string &message) const;
    void printTok(const Token &tok) const;
    void printMess(const std::string &message) const;

private:
    unsigned char m_Mode;

    const std::string red = "\033[0;31m";
    const std::string green = "\033[1;32m";
    const std::string yellow = "\033[1;33m";
    const std::string cyan = "\033[0;36m";
    const std::string magenta = "\033[0;35m";
    const std::string reset = "\033[0m";
};

extern Log l;

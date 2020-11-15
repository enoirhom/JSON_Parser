#include <iostream>
#include "Log.h"

Log::Log() : m_Mode(0) {

}

void Log::setMode(Mode m) {
    m_Mode |= m;
}

void Log::unsetMode(Mode m) {
    m_Mode &= (~m);
}

void Log::printOLC(const std::string &message) const {
    if (m_Mode & OLC) {
        std::cout << yellow << "[OLC]: " << reset << message << std::endl;
    }
}

void Log::printErr(const std::string &message) const {
    if (m_Mode & ERR) {
        std::cout << red << "[ERROR]: " << reset << message << std::endl;
    }
}

void Log::printTok(const Token &tok) const {
    if (m_Mode & TOK) {
        std::cout << green << "[TOKEN]: " << reset << tok << std::endl;
    }
}

void Log::printMess(const std::string &message) const {
    if (m_Mode & MESS) {
        std::cout << "[MESSAGE]: " << message << std::endl;
    }
}

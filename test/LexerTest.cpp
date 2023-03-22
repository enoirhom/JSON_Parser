#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "../include/Lexer.hpp"

void test(const std::string& input, int expectedType, const std::string& expectedText) {
    std::istringstream stream(input);
    Lexer lexer(&stream);

    Token* token = lexer.nextToken();

    EXPECT_EQ(expectedType, token->m_Type);
    EXPECT_EQ(expectedText, token->m_Text);

    delete token;
    token = lexer.nextToken();

    EXPECT_EQ(1, token->m_Type);
    delete token;
}

void test(const std::string& input, int expectedType) {
    test(input, expectedType, input);
}

TEST(LexerTest, Numbers) {
    std::string inputs[] = {"0", "0.0", "0.1", "0.09", "10", "10.10", "10.01", "1e19", "1e+19",
        "1e-19", "1E19", "1E+19", "1E-19", "1.23e3", "1.23e+3", "1.23e-3"};

    for (std::string input : inputs) {
        test(input, Lexer::NUMBER);
    }
}

TEST(LexerTest, NegativeNumbers) {
    std::string inputs[] = {"-0", "-0.0", "-0.1", "-0.09", "-10", "-10.10", "-10.01", "-1e19",
        "-1e+19", "-1e-19", "-1E19", "-1E+19", "-1E-19", "-1.23e3", "-1.23e+3",
        "-1.23e-3"};

    for (std::string input : inputs) {
        test(input, Lexer::NUMBER);
    }
}

TEST(LexerTest, String) {
    std::string inputs[] = {"test", "abcdefg", "hijklmn", "opqrst", "uvwxyz",
        "\\\"", "\\\\", "\\/", "\\b", "\\f", "\\n", "\\r", "\\t"};

    for (std::string input : inputs) {
        test("\"" + input + "\"", Lexer::STRING, input);
    }
}

TEST(LexerTest, JSONMarkers) {
    test("{", Lexer::LCURL);
    test("}", Lexer::RCURL);
    test("[", Lexer::LBRACK);
    test("]", Lexer::RBRACK);
    test(":", Lexer::COLON);
    test(",", Lexer::COMMA);
}

TEST(LexerTest, JSONLiterals) {
    test("true", Lexer::TRUE);
    test("false", Lexer::FALSE);
    test("null", Lexer::NULL_TYPE);
}
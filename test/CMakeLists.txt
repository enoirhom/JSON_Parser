cmake_minimum_required(VERSION 3.19.1)

set(This JsonParserTests)

set(Sources
    LexerTest.cpp
)

add_executable(${This} ${Sources})
target_link_libraries(${This} PUBLIC
    gtest_main
    json_parser
)

add_test(
    NAME ${This}
    COMMAND ${This}
)
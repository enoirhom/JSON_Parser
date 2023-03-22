cmake_minimum_required(VERSION 3.19.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

project(json_parser)

enable_testing()

add_subdirectory(googletest)

set(Headers
    include/Lexer.hpp
    include/Parser.hpp
    include/Token.hpp
)

set(Sources
    src/Lexer.cpp
    src/Parser.cpp
    src/Token.cpp
)

add_library(${PROJECT_NAME} STATIC ${Sources} ${Headers})

add_subdirectory(test)

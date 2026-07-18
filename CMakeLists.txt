cmake_minimum_required(VERSION 4.1)
project(Lexa_programming_language)

set(CMAKE_CXX_STANDARD 20)

add_executable(Lexa_programming_language main.cpp
        token.h
        lexer.h
        Lexer.cpp
        ast.h
        parser.h
        parser.cpp
        evaluator.h
        evaluator.cpp
        symboltable.h
        symboltable.cpp)

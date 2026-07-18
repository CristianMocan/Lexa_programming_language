#pragma once
#include <string>
using namespace std;
enum token_type {
    IDENTIFIER,
    NUMBER,
    ASSIGN,
    DIFERIT,
    EGAL_EGAL,
    PLUS,
    PLUS_ASSIGN,
    PLUS_PLUS,
    MINUS_ASSIGN,
    MINUS,
    MINUS_MINUS,
    MULTIPLY,
    DIVIDE,
    MOD,
    MAI_MARE,
    MAI_MARE_EGAL,
    MAI_MIC,
    MAI_MIC_EGAL,
    PRINT,
    IF,
    ELSE,
    WHILE,
    FOR,
    SEMICOLON,
    LEFT_BRACKET,
    RIGHT_BRACKET,
    LEFT_AC,
    RIGHT_AC,
    END_TOKEN
};

struct Token {
    token_type type;
    string value;
};
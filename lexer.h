#pragma once
#include <string>
#include <vector>
#include "token.h"

using namespace std;

class Lexer {
private:
    string text;
    int pos;
public:
    Lexer(const string &input);
    vector<Token> tokensize();
};
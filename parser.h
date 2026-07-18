#pragma once
#include <vector>
#include "token.h"
#include "ast.h"

using namespace std;

class Parser {
private:
    vector<Token> tokens;
    int pos;
    Token currentToken();
    ASTNode *parseExpression();
    ASTNode *parseTerm();
    ASTNode *parseFactor();
    ASTNode *parseAssignment();
    ASTNode *parseComparasion();
    ASTNode *parseIf();
    ASTNode *parsePrint();
    ASTNode *parseWhile();
    ASTNode *parseFor();
    ASTNode *parseBlock();
public:
    Parser(const vector<Token> &inputTokens);
    ASTNode *parse();
};
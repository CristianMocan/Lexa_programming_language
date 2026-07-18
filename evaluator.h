#pragma once
#include "ast.h"
#include "symboltable.h"

class Evaluator {
private:
    SymbolTable table;
public:
    int evaluate(ASTNode *node);
};
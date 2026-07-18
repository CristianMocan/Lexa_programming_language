#include "symboltable.h"

using namespace std;

void SymbolTable::setVariable(const string &name, int value) {
    variables[name] = value;
}

int SymbolTable::getVariable(const string &name) {
    return variables[name];
}
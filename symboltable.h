#pragma once
#include <string>
#include <unordered_map>
using namespace std;


class SymbolTable {
private:
    unordered_map<string, int> variables;
public:
    void setVariable(const string &name, int value);
    int getVariable(const string &name);
};
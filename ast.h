#pragma once
#include <string>
#include <vector>
using namespace std;

struct ASTNode {
    string value;
    ASTNode *left;
    ASTNode *right;
    ASTNode *extra;
    ASTNode *ex;
    vector<ASTNode*> children;

    ASTNode(const string &val) {
        value = val;
        left = nullptr;
        right = nullptr;
        extra = nullptr;
        ex = nullptr;
    }
};
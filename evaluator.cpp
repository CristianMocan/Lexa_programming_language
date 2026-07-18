#include "evaluator.h"
#include <string>
#include <iostream>
using namespace std;

int Evaluator::evaluate(ASTNode *node) {
    if (node->value == "block") {
        for (ASTNode *child : node->children) {
            evaluate(child);
        }
        return 0;
    }
    if (node->left == nullptr && node->right == nullptr) {
        if (isdigit(node->value[0])){
            return stoi(node->value);
        }
        return table.getVariable(node->value);
    }
    if (node->value == "*") {
        return evaluate(node->left) * evaluate(node->right);
    }
    if (node->value == "/") {
        int right = evaluate(node->right);
        if (right == 0) {
            cout<<"Error: Division by zero!"<<endl;
            return 0;
        }
        return evaluate(node->left) / right;
    }
    if (node->value == "%") {
        return evaluate(node->left) % evaluate(node->right);
    }
    if (node->value == "+") {
        return evaluate(node->left) + evaluate(node->right);
    }
    if (node->value == "-") {
        return evaluate(node->left) - evaluate(node->right);
    }
    if (node->value == "==") {
        return evaluate(node->left) == evaluate(node->right);
    }
    if (node->value == "!=") {
        return evaluate(node->left) != evaluate(node->right);
    }
    if (node->value == "<=") {
        return evaluate(node->left) <= evaluate(node->right);
    }
    if (node->value == ">=") {
        return evaluate(node->left) >= evaluate(node->right);
    }
    if (node->value == ">") {
        return evaluate(node->left) > evaluate(node->right);
    }
    if (node->value == "<") {
        return evaluate(node->left) < evaluate(node->right);
    }
    if (node->value == "plx") {
        int value = evaluate(node->left);
        cout<<value<<endl;
        return value;
    }
    if (node->value == "if") {
        if (evaluate(node->left)) {
            return evaluate(node->right);
        }
        if (node->extra!=nullptr) {
            return evaluate(node->extra);
        }
    }
    if (node->value == "while") {
        while (evaluate(node->left)) {
            evaluate(node->right);
        }
        return 0;
    }
    if (node->value == "for") {
        evaluate(node->left);
        while (evaluate(node->right)) {
            evaluate(node->ex);
            evaluate(node->extra);
        }
        return 0;
    }
    if (node->value == "=") {
        int value = evaluate(node->right);
        table.setVariable(
            node->left->value,
            value
            );
        return value;
    }
    return 0;
}
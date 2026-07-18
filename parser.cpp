#include "parser.h"
#include <iostream>
using namespace std;

Parser::Parser(const vector<Token> &inputTokens) {
    tokens = inputTokens;
    pos = 0;
}

Token Parser::currentToken() {
    return tokens[pos];
}

ASTNode *Parser::parse() {
    return parseFor();
}

ASTNode *Parser::parseFactor() {
    if (currentToken().type == LEFT_BRACKET) {
        pos++;
        ASTNode *node = parseExpression();
        if (currentToken().type == RIGHT_BRACKET) {
            pos++;
        }
        return node;
    }
    Token token = currentToken();
    pos++;
    return new ASTNode(token.value);
}

ASTNode *Parser::parsePrint() {
    if (currentToken().type == PRINT) {
        pos++;
        if (currentToken().type == LEFT_BRACKET) {
            pos++;
        }
        ASTNode *expr = parseComparasion();
        if (currentToken().type == RIGHT_BRACKET) {
            pos++;
        }
        ASTNode *node = new ASTNode("plx");
        node->left = expr;
        node->right = nullptr;
        return node;
    }
    return parseAssignment();
}

ASTNode *Parser::parseWhile() {
    if (currentToken().type == WHILE) {
        pos++;
        if (currentToken().type == LEFT_BRACKET) {
            pos++;
        }
        ASTNode *conditie = parseComparasion();
        if (currentToken().type == RIGHT_BRACKET) {
            pos++;
        }
        if (currentToken().type == LEFT_AC) {
            pos++;
        }
        ASTNode *block_node = parseBlock();
        ASTNode *node = new ASTNode("while");
        node->left = conditie;
        node->right = block_node;
        return node;
    }
    return parseIf();
}

ASTNode *Parser::parseFor() {
    if (currentToken().type == FOR) {
        pos++;
        if (currentToken().type == LEFT_BRACKET)
            pos++;
        ASTNode *expr = parseAssignment();
        if(currentToken().type == SEMICOLON)
            pos++;
        ASTNode *conditie = parseComparasion();
        if(currentToken().type == SEMICOLON)
            pos++;
        ASTNode *operatie = parseAssignment();
        if (currentToken().type == RIGHT_BRACKET)
            pos++;
        if (currentToken().type == LEFT_AC)
            pos++;
        ASTNode *block_node = parseBlock();
        ASTNode *node = new ASTNode("for");
        node->left = expr;
        node->right = conditie;
        node->extra = operatie;
        node->ex = block_node;
        return node;
    }
    return parseWhile();
}

ASTNode *Parser::parseBlock() {
    ASTNode *block = new ASTNode("block");
    while (currentToken().type != RIGHT_AC) {
        block->children.push_back(parseFor());
    }
    pos++;
    return block;
}


ASTNode *Parser::parseIf() {
    if (currentToken().type == IF) {
        pos++;
        if (currentToken().type == LEFT_BRACKET) {
            pos++;
        }
        ASTNode *condition = parseComparasion();
        if (currentToken().type == RIGHT_BRACKET) {
            pos++;
        }
        if (currentToken().type == LEFT_AC) {
            pos++;
        }
        ASTNode *block = parseBlock();
        ASTNode *else_node = nullptr;
        if (currentToken().type == ELSE) {
            pos++;
            else_node = parseIf();
        }
        ASTNode *ifnode = new ASTNode("if");
        ifnode->left = condition;
        ifnode->right = block;
        ifnode->extra = else_node;
        return ifnode;
    }
    return parsePrint();
}

ASTNode *Parser::parseTerm() {
    ASTNode *node = parseFactor();
    while (currentToken().type == MULTIPLY || currentToken().type == DIVIDE || currentToken().type == MOD) {
        Token op = currentToken();
        pos++;
        ASTNode *right = parseFactor();
        ASTNode *newNode = new ASTNode(op.value);
        newNode->left = node;
        newNode->right = right;
        node = newNode;
    }
    return node;
}

ASTNode *Parser::parseAssignment() {
    if (pos + 1 < tokens.size() && currentToken().type == IDENTIFIER && tokens[pos+1].type == PLUS_ASSIGN) {
        Token ident = currentToken();
        pos+=2; //ca sa sara peste '=' de aia e pos++ de 2 ori
        ASTNode *value = parseExpression();
        ASTNode *plusNode = new ASTNode("+");
        plusNode->left = new ASTNode(ident.value);
        plusNode->right = value;

        ASTNode *assignNode = new ASTNode("=");
        assignNode->left = new ASTNode(ident.value);
        assignNode->right = plusNode;

        return assignNode;
    }
    if (pos + 1 < tokens.size() && currentToken().type == IDENTIFIER && tokens[pos+1].type == PLUS_PLUS) {
        Token ident = currentToken();
        pos+=2;
        ASTNode *plus_plusNode = new ASTNode("+");
        plus_plusNode->left = new ASTNode(ident.value);
        plus_plusNode->right = new ASTNode("1");

        ASTNode *plus_plusNode2 = new ASTNode("=");
        plus_plusNode2->left = new ASTNode(ident.value);
        plus_plusNode2->right = plus_plusNode;
        return plus_plusNode2;
    }
    if (pos + 1 < tokens.size() && currentToken().type == IDENTIFIER && tokens[pos+1].type == MINUS_MINUS) {
        Token ident = currentToken();
        pos+=2;
        ASTNode *minus_Node = new ASTNode("-");
        minus_Node->left = new ASTNode(ident.value);
        minus_Node->right = new ASTNode("1");

        ASTNode *assignNode = new ASTNode("=");
        assignNode->left = new ASTNode(ident.value);
        assignNode->right = minus_Node;
        return assignNode;
    }
    if (pos + 1 < tokens.size() && currentToken().type == IDENTIFIER && tokens[pos+1].type == ASSIGN) {
        Token ident = currentToken();
        pos+=2; //ca sa sara peste '=' de aia e pos++ de 2 ori
        ASTNode *value = parseExpression();
        ASTNode *assignNode = new ASTNode("=");
        assignNode->left = new ASTNode(ident.value);
        assignNode->right = value;

        return assignNode;
    }
    if (pos + 1 < tokens.size() && currentToken().type == IDENTIFIER && tokens[pos+1].type == MINUS_ASSIGN) {
        Token ident = currentToken();
        pos+=2; //ca sa sara peste '=' de aia e pos++ de 2 ori
        ASTNode *value = parseExpression();
        ASTNode *minusNode = new ASTNode("-");
        minusNode->left = new ASTNode(ident.value);
        minusNode->right = value;
        ASTNode *assignNode = new ASTNode("=");
        assignNode->left = new ASTNode(ident.value);
        assignNode->right = minusNode;

        return assignNode;
    }
    return parseComparasion();
}

ASTNode *Parser::parseComparasion() {
    ASTNode *node = parseExpression();
    while (currentToken().type == MAI_MARE || currentToken().type == MAI_MIC || currentToken().type == EGAL_EGAL
        || currentToken().type == MAI_MARE_EGAL || currentToken().type == MAI_MIC_EGAL || currentToken().type == DIFERIT) {
        Token op = currentToken();
        pos++;
        ASTNode *right = parseExpression();
        ASTNode *newNode = new ASTNode(op.value);
        newNode->left = node;
        newNode->right = right;
        node = newNode;
    }
    return node;
}

ASTNode *Parser::parseExpression() {
    ASTNode *node = parseTerm();
    while (currentToken().type == PLUS || currentToken().type == MINUS) {
        Token op = currentToken();
        pos++;
        ASTNode *right = parseTerm();
        ASTNode *newNode = new ASTNode(op.value);
        newNode->left = node;
        newNode->right = right;
        node = newNode;
    }
    return node;
}

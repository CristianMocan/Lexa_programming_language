#include <cctype>
#include "lexer.h"

using namespace std;

Lexer::Lexer(const string &input) {
    text = input;
    pos = 0;
}

vector<Token> Lexer::tokensize() {
    vector<Token> tokens;
    while (pos < text.length()) {
        char current = text[pos];
        if (isspace(current)) {
            pos++;
            continue;
        }
        if (isalpha(current)) {
            string identifier;
            while (pos < text.length() && isalnum(text[pos])) {
                identifier += text[pos];
                pos++;
            }
            if (identifier == "plx") {
                tokens.push_back({PRINT, identifier});
            }
            else if (identifier == "if") {
                tokens.push_back({IF, identifier});
            }
            else if (identifier == "else") {
                tokens.push_back({ELSE, identifier});
            }
            else if (identifier == "while") {
                tokens.push_back({WHILE, identifier});
            }
            else if (identifier == "for") {
                tokens.push_back({FOR, identifier});
            }
            else {
                tokens.push_back({IDENTIFIER, identifier});
            }
            continue;
        }
        if (current == '+' && text[pos+1] == '+' && pos+1 < text.length()) {
            string plus_plus = "++";
            tokens.push_back({PLUS_PLUS, plus_plus});
            pos+=2;
            continue;
        }
        if (current == ';') {
            string semicolon = ";";
            tokens.push_back({SEMICOLON, semicolon});
            pos++;
            continue;
        }
        if (current == '=' && text[pos+1] == '=' && pos+1 < text.length()) {
            string egal_egal = "==";
            tokens.push_back({EGAL_EGAL, egal_egal});
            pos+=2;
            continue;
        }
        if (current == '>' && text[pos+1] == '=' && pos+1 < text.length()) {
            string mai_mare_egal = ">=";
            tokens.push_back({MAI_MARE_EGAL, mai_mare_egal});
            pos+=2;
            continue;
        }
        if (current == '<' && text[pos+1] == '=' && pos+1 < text.length()) {
            string mai_mic_egal = "<=";
            tokens.push_back({MAI_MIC_EGAL, mai_mic_egal});
            pos+=2;
            continue;
        }
        if (current == '-' && text[pos+1] == '-' && pos+1 < text.length()) {
            string minus_minus = "--";
            tokens.push_back({MINUS_MINUS, minus_minus});
            pos+=2;
            continue;
        }
        if (current == '!' && text[pos+1] == '=' && pos+1 < text.length()) {
            string diferit = "!=";
            tokens.push_back({DIFERIT, diferit});
            pos+=2;
            continue;
        }
        if (current == '>') {
            string mai_mare = ">";
            tokens.push_back({MAI_MARE,mai_mare});
            pos++;
            continue;
        }
        if (current == '<') {
            string mai_mic = "<";
            tokens.push_back({MAI_MIC,mai_mic});
            pos++;
            continue;
        }
        if (current == '+' && text[pos+1] == '=' && pos+1 < text.length()) {
            string plus_assign = "+=";
            tokens.push_back({PLUS_ASSIGN, plus_assign});
            pos+=2;
            continue;
        }
        if (current == '-' && text[pos+1] == '=' && pos+1 < text.length()) {
            string minus_assign = "-=";
            tokens.push_back({MINUS_ASSIGN, minus_assign});
            pos+=2;
            continue;
        }
        if (isdigit(current)) {
            string number;
            while (pos < text.length() && isdigit(text[pos])) {
                number += text[pos];
                pos++;
            }
            tokens.push_back({NUMBER, number});
            continue;
        }
        switch (current) {
            case '(':
                tokens.push_back({LEFT_BRACKET, "("});
                break;
            case '{':
                tokens.push_back({LEFT_AC, "{"});
                break;
            case ')':
                tokens.push_back({RIGHT_BRACKET, ")"});
                break;
            case '}':
                tokens.push_back({RIGHT_AC, "}"});
                break;
            case '=':
                tokens.push_back({ASSIGN, "="});
                break;
            case '+':
                tokens.push_back({PLUS, "+"});
                break;
            case '-':
                tokens.push_back({MINUS, "-"});
                break;
            case '%':
                tokens.push_back({MOD, "%"});
                break;
            case '*':
                tokens.push_back({MULTIPLY, "*"});
                break;
            case '/':
                tokens.push_back({DIVIDE, "/"});
                break;
        }
        pos++;
    }
    tokens.push_back({END_TOKEN, ""});
    return tokens;
}
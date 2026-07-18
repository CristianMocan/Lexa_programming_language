#include <iostream>
#include <string>
#include "lexer.h"
#include "parser.h"
#include "evaluator.h"
using namespace std;

// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
int main() {
    Evaluator evaluator;

    while (true) {
        string code;
        string line;
        int acolade = 0;

        do {
            if (code.empty())
                cout << "lexa>> ";
            else
                cout << "...> ";

            getline(cin, line);

            if (line == "exit")
                return 0;

            code += line + "\n";

            for (char c : line) {
                if (c == '{')
                    acolade++;
                else if (c == '}')
                    acolade--;
            }

        } while (acolade > 0);

        if (code.empty())
            continue;

        Lexer lexer(code);
        vector<Token> tokens = lexer.tokensize();

        Parser parser(tokens);
        ASTNode *root = parser.parse();

        evaluator.evaluate(root);
    }

    return 0;
}
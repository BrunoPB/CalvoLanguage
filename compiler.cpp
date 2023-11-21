#include <iostream>
#include <vector>

#include "ir/ir.h"
#include "lexer/lexer.h"
#include "parser/parser.h"
#include "shared/allincludes.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        error("COMPILER", "No file to compile.");
    }

    // Lexer
    string fileName = argv[1];
    vector<token> tokens;
    tokens = getTokens(fileName);

    // Parser
    lr0_automaton automaton = getAutomaton();
    parsing_table parsingTable = getParsingTable(automaton);
    shared_ptr<S> AST = getAST(parsingTable, tokens);

    // IR Generation
    compileToIR(move(AST));

    // Save module
    string outputFileName = "calvo.ll";
    if (argc == 3) {
        outputFileName = argv[2];
    }
    saveModuleToFile(outputFileName);

    return 0;
}
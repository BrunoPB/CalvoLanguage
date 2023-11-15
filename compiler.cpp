#include <iostream>
#include <vector>

#include "lexer/lexer.h"
#include "parser/parser.h"
#include "shared/allincludes.h"
#include "shared/namespaces.h"

int main(int argc, char *argv[]) {
    // try {
    string fileName = argv[1];
    vector<token> tokens;
    tokens = getTokens(fileName);
    lr0_automaton automaton = getAutomaton();
    parsing_table parsingTable = getParsingTable(automaton);
    shared_ptr<S> AST = getAST(parsingTable, tokens);
    parser_rule test = AST->code->decl->getParserRule();
    cout << get<0>(test) << " -> ";
    for (auto p : get<1>(test)) {
        cout << p << " ";
    }
    cout << endl;
    // } catch (string error) {
    //     cout << "ERROR: " << error << endl;
    // }
    return 0;
}
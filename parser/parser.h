#ifndef PARSER_H
#define PARSER_H
#include <iostream>
#include <memory>
#include <set>
#include <vector>

#include "../shared/allincludes.h"
#include "../shared/namespaces.h"
#include "parser-classes.h"

shared_ptr<S> getAST(parsing_table, vector<token>);

void generateASTFromRule(ParserClasses*, stack<token>*, int);

parsing_table getParsingTable(lr0_automaton);

lr0_automaton getAutomaton();

set<parser_rule> getNonTerminalRules(int);

aut_state closure(item initialItem, set<int> = {});

aut_state goTo(aut_state, int);

bool doesAutomatonHasState(lr0_automaton, aut_state);

bool areStatesEqual(aut_state, aut_state);

bool areItemsEqual(item, item);

int getRuleNumber(parser_rule);

parser_rule getRuleFromNumber(int);

set<int> FOLLOW(int, set<int> = {});

set<int> FIRST(vector<int>);

bool hasLambdaProduction(int);

int stateIndexInAutomaton(lr0_automaton, aut_state);

#include "parser.cpp"

#endif
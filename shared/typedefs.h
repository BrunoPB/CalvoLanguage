#ifndef TYPEDEFS_H
#define TYPEDEFS_H
#include <iostream>
#include <map>
#include <set>
#include <tuple>
#include <vector>

#include "namespaces.h"

typedef tuple<string, int> lexer_rule;
typedef tuple<int, string> token;
typedef tuple<int, vector<int>> parser_rule;
typedef tuple<parser_rule, int> item;
typedef set<item> aut_state;
typedef vector<aut_state> lr0_automaton;
typedef map<tuple<int, int>, tuple<char, int>> parsing_table;

#endif
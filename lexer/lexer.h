#ifndef LEXER_H
#define LEXER_H
#include <iostream>
#include <regex>
#include <vector>

#include "./../shared/allincludes.h"

/*
 * Get the tokens from a file
 * @returns vector<string> List of tokens
 */
vector<token> getTokens(string);

vector<token> tokenize(string, vector<lexer_rule>);

bool isEmptySpace(char);

bool matchAnyRule(string, vector<lexer_rule>);

int matchToken(string, vector<lexer_rule>);

#include "lexer.cpp"

#endif
#ifndef READER_H
#define READER_H
#include <iostream>
#include <vector>
#include <tuple>

#include "./../shared/allincludes.h"

using namespace std;

vector<string> readFile(string);

vector<lexer_rule> getLexerConfig();

string treatLine(string);

int getTokenEnum(string);

#include "reader.cpp"

#endif
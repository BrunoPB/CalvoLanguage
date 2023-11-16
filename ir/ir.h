#ifndef IR_H
#define IR_H

#include "../parser/parser-classes.h"
#include "../shared/allincludes.h"

void compileToIR(shared_ptr<S>);

void setupPrintfFunction();

Function* declareMainFunction();

void setEntryBlock(Function*);

void endMain();

void saveModuleToFile(const string&);

#include "ir.cpp"

#endif
#ifndef ENV_H
#define ENV_H

#include <iostream>
#include <map>

#include "../shared/allincludes.h"

typedef map<string, Value*> symbol_table;

class Environment : public enable_shared_from_this<Environment> {
   private:
    symbol_table record;
    shared_ptr<Environment> parent;

    shared_ptr<Environment> resolve(const string&);

   public:
    Environment(symbol_table _record, shared_ptr<Environment> _parent) : record(_record), parent(_parent) {}

    Value* define(const string& name, Value* value);

    Value* lookup(const string&);

    shared_ptr<Environment> generateChild();

    shared_ptr<Environment> getParent();
};

#include "env.cpp"

#endif
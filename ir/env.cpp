#include "env.h"

shared_ptr<Environment> Environment::resolve(const string& name) {
    if (record.count(name) != 0) {
        return shared_from_this();
    }

    if (parent == nullptr) {
        return nullptr;
    }

    return parent->resolve(name);
}

Value* Environment::define(const string& name, Value* value) {
    record[name] = value;
    return value;
}

Value* Environment::lookup(const string& name) {
    shared_ptr<Environment> env = resolve(name);

    if (env == nullptr) {
        return nullptr;
    }

    return env->record[name];
}

shared_ptr<Environment> Environment::generateChild() {
    return make_shared<Environment>(Environment({}, shared_from_this()));
}

shared_ptr<Environment> Environment::getParent() {
    return parent;
}
#ifndef PARSERCLASSES_H
#define PARSERCLASSES_H
#include <iostream>
#include <memory>
#include <stack>

#include "../shared/allincludes.h"

class ParserRule {
   public:
    virtual parser_rule getParserRule() { return parser_rule(); };
    virtual Value *codegen() { return nullptr; }
};

class Code;
class Declaration;
class Atrib;
class Expression;
class Operation;
class Bool;
class BoolOp;
class Cond;
class Else;
class Rep;
class Call;
class Param;

class S : public ParserRule {
   public:
    shared_ptr<Code> code;

    S() {}
    S(shared_ptr<Code> code) : code(move(code)) {}

    parser_rule getParserRule() override;
    Value *codegen() override;
};

class Code : public ParserRule {
   public:
    shared_ptr<Declaration> decl;
    shared_ptr<Atrib> atrib;
    shared_ptr<Code> code;
    shared_ptr<Call> call;
    shared_ptr<Rep> rep;
    shared_ptr<Cond> cond;
    parser_rule getParserRule() { return parser_rule(); };
    virtual Value *codegen() { return nullptr; };
};

class LambdaCode : public Code {
   public:
    LambdaCode() {}
    parser_rule getParserRule() override;
};

class DecCode : public Code {
   public:
    DecCode() {}
    DecCode(shared_ptr<Declaration> _decl,
            shared_ptr<Code> _code) {
        decl = move(_decl);
        code = move(_code);
    }

    parser_rule getParserRule() override;
    // Value *codegen() override;
};

class AtribCode : public Code {
   public:
    AtribCode() {}
    AtribCode(shared_ptr<Atrib> _atrib,
              shared_ptr<Code> _code) {
        atrib = move(_atrib);
        code = move(_code);
    }

    parser_rule getParserRule() override;
    // Value *codegen() override;
};

class CondCode : public Code {
   public:
    CondCode() {}
    CondCode(shared_ptr<Cond> _cond,
             shared_ptr<Code> _code) {
        cond = move(_cond);
        code = move(_code);
    }

    parser_rule getParserRule() override;
    // Value *codegen() override;
};

class RepCode : public Code {
   public:
    RepCode() {}
    RepCode(shared_ptr<Rep> _rep,
            shared_ptr<Code> _code) {
        rep = move(_rep);
        code = move(_code);
    }

    parser_rule getParserRule() override;
    // Value *codegen() override;
};

class CallCode : public Code {
   public:
    CallCode() {}
    CallCode(shared_ptr<Call> _call,
             shared_ptr<Code> _code) {
        call = move(_call);
        code = move(_code);
    }

    parser_rule getParserRule() override;
    Value *codegen() override;
};

class Declaration : public ParserRule {
   public:
    shared_ptr<Atrib> atrib;

    Declaration() {}
    Declaration(shared_ptr<Atrib> atrib) : atrib(move(atrib)) {}

    parser_rule getParserRule() override;
    // Value *codegen() override;
};

class Atrib : public ParserRule {
   public:
    string id;
    shared_ptr<Expression> expr;

    Atrib() {}
    Atrib(string id, shared_ptr<Expression> expr) : id(id), expr(move(expr)) {}

    parser_rule getParserRule() override;
    // Value *codegen() override;
};

class Expression : public ParserRule {
   public:
    int number;
    shared_ptr<Operation> op;
    string id;
    shared_ptr<Expression> expr;
    parser_rule getParserRule() { return parser_rule(); };
    virtual Value *codegen() { return nullptr; };
};

class NumberExpression : public Expression {
   public:
    NumberExpression() {}
    NumberExpression(int _number, shared_ptr<Operation> _op) {
        number = _number;
        op = move(_op);
    }

    parser_rule getParserRule() override;
    Value *codegen() override;
};

class IdExpression : public Expression {
   public:
    IdExpression() {}
    IdExpression(string _id, shared_ptr<Operation> _op) {
        id = _id;
        op = move(_op);
    }

    parser_rule getParserRule() override;
    // Value *codegen() override;
};

class ParenExpression : public Expression {
   public:
    ParenExpression() {}
    ParenExpression(shared_ptr<Expression> _expr) {
        expr = move(_expr);
    }

    parser_rule getParserRule() override;
    // Value *codegen() override;
};

class Operation : public ParserRule {
   public:
    string op;
    shared_ptr<Expression> expr;
    parser_rule getParserRule() { return parser_rule(); };
    Value *codegen() { return nullptr; };
};

class OpOperation : public Operation {
   public:
    OpOperation() {}
    OpOperation(string _op, shared_ptr<Expression> _expr) {
        op = move(_op);
        expr = move(_expr);
    }

    parser_rule getParserRule() override;
    // Value *codegen() override;
};

class LambdaOperation : public Operation {
   public:
    LambdaOperation() {}
    parser_rule getParserRule() override;
};

class Bool : public ParserRule {
   public:
    shared_ptr<Expression> expr1;
    string compare;
    shared_ptr<Expression> expr2;
    shared_ptr<BoolOp> boolop;

    Bool() {}
    Bool(shared_ptr<Expression> expr1,
         string compare,
         shared_ptr<Expression> expr2,
         shared_ptr<BoolOp> boolop) : expr1(move(expr1)), compare(compare), expr2(move(expr2)), boolop(move(boolop)) {}

    parser_rule getParserRule() override;
    // Value *codegen() override;
};

class BoolOp : public ParserRule {
   public:
    string boolean;
    shared_ptr<Bool> boolptr;
    parser_rule getParserRule() { return parser_rule(); };
    // Value *codegen() override;
};

class BoBoolOp : public BoolOp {
   public:
    BoBoolOp() {}
    BoBoolOp(string _boolean, shared_ptr<Bool> _boolptr) {
        boolean = _boolean;
        boolptr = move(_boolptr);
    }

    parser_rule getParserRule() override;
    // Value *codegen() override;
};

class LambdaBoolOp : public BoolOp {
   public:
    LambdaBoolOp() {}
    parser_rule getParserRule() override;
    // Value *codegen() override;
};

class Cond : public ParserRule {
   public:
    shared_ptr<Bool> boolptr;
    shared_ptr<Code> code;
    shared_ptr<Else> elseptr;

    Cond() {}
    Cond(shared_ptr<Bool> boolptr,
         shared_ptr<Code> code,
         shared_ptr<Else> elseptr) : boolptr(move(boolptr)), code(move(code)), elseptr(move(elseptr)) {}

    parser_rule getParserRule() override;
    // Value *codegen() override;
};

class Else : public ParserRule {
   public:
    shared_ptr<Code> code;
    parser_rule getParserRule() { return parser_rule(); };
    // Value *codegen() override;
};

class ElElse : public Else {
   public:
    ElElse() {}
    ElElse(shared_ptr<Code> _code) {
        code = move(_code);
    }

    parser_rule getParserRule() override;
    // Value *codegen() override;
};

class LambdaElse : public Else {
   public:
    LambdaElse() {}
    parser_rule getParserRule() override;
    // Value *codegen() override;
};

class Rep : public ParserRule {
   public:
    shared_ptr<Bool> boolptr;
    shared_ptr<Code> code;

    Rep() {}
    Rep(shared_ptr<Bool> boolptr,
        shared_ptr<Code> code) : boolptr(move(boolptr)), code(move(code)) {}

    parser_rule getParserRule() override;
    // Value *codegen() override;
};

class Call : public ParserRule {
   public:
    string id;
    shared_ptr<Param> param;

    Call() {}
    Call(string id, shared_ptr<Param> param) : id(id), param(move(param)) {}

    parser_rule getParserRule() override;
    Value *codegen() override;
};

class Param : public ParserRule {
   public:
    shared_ptr<Expression> expr;
    parser_rule getParserRule() { return parser_rule(); };
    Value *codegen() { return nullptr; };
};

class ExprParam : public Param {
   public:
    ExprParam() {}
    ExprParam(shared_ptr<Expression> _expr) {
        expr = move(_expr);
    }

    parser_rule getParserRule() override;
    Value *codegen() override;
};

class LambdaParam : public Param {
   public:
    LambdaParam() {}
    parser_rule getParserRule() override;
};

class ParserClasses {
   public:
    stack<shared_ptr<ParserRule>> pr;
    stack<shared_ptr<S>> s;
    stack<shared_ptr<Code>> c;
    stack<shared_ptr<Declaration>> d;
    stack<shared_ptr<Atrib>> a;
    stack<shared_ptr<Expression>> expr;
    stack<shared_ptr<ParenExpression>> pe;
    stack<shared_ptr<Operation>> o;
    stack<shared_ptr<Bool>> b;
    stack<shared_ptr<BoolOp>> bo;
    stack<shared_ptr<Cond>> cn;
    stack<shared_ptr<Else>> e;
    stack<shared_ptr<Rep>> r;
    stack<shared_ptr<Call>> cl;
    stack<shared_ptr<Param>> p;

    ParserClasses() {
        pr = {};
        c = {};
        s = {};
        d = {};
        a = {};
        expr = {};
        pe = {};
        o = {};
        b = {};
        bo = {};
        cn = {};
        e = {};
        r = {};
        cl = {};
        p = {};
    };
};

Value *LogErrorV(const char *);

int getRuleNumber(parser_rule);

parser_rule getRuleFromNumber(int);

#include "../ir/codegen.cpp"
#include "parser-classes.cpp"
#include "parser-rules.cpp"

#endif
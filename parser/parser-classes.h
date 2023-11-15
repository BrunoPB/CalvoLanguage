#ifndef PARSERCLASSES_H
#define PARSERCLASSES_H
#include <iostream>
#include <memory>
#include <stack>

#include "../shared/allincludes.h"
#include "../shared/namespaces.h"
// #include "llvm/IR/IRBuilder.h"
// #include "llvm/IR/LLVMContext.h"
// #include "llvm/IR/Module.h"
// #include "llvm/IR/Value.h"

// using namespace llvm;

// static std::unique_ptr<LLVMContext> TheContext; // LLVM global context, where the IR will be stored
// static std::unique_ptr<IRBuilder<>> Builder; // Builder used to build the LLVM context
// static std::unique_ptr<Module> TheModule; // Type of object that can be built into the LLVM context
// static std::map<std::string, Value *> NamedValues;

class ParserRule {
   public:
    virtual parser_rule getParserRule() { return parser_rule(); };
    // virtual Value *codegen() = 0;
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
    // Value *codegen() override;
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
    // Value *codegen() override;
};

class LambdaCode : public Code {
   public:
    LambdaCode() {}
    parser_rule getParserRule() override;
    // Value *codegen() override;
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
    // Value *codegen() override;
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
    // Value *codegen() override;
};

class NumberExpression : public Expression {
   public:
    NumberExpression() {}
    NumberExpression(int _number, shared_ptr<Operation> _op) {
        number = _number;
        op = move(_op);
    }

    parser_rule getParserRule() override;
    // Value *codegen() override;
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
    // Value *codegen() override;
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
    // Value *codegen() override;
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
    // Value *codegen() override;
};

class Param : public ParserRule {
   public:
    shared_ptr<Expression> expr;
    parser_rule getParserRule() { return parser_rule(); };
    // Value *codegen() override;
};

class ExprParam : public Param {
   public:
    ExprParam() {}
    ExprParam(shared_ptr<Expression> _expr) {
        expr = move(_expr);
    }

    parser_rule getParserRule() override;
    // Value *codegen() override;
};

class LambdaParam : public Param {
   public:
    LambdaParam() {}
    parser_rule getParserRule() override;
    // Value *codegen() override;
};

shared_ptr<S> parseStart(shared_ptr<Code>);
shared_ptr<DecCode> parseDeclarationCode(shared_ptr<Declaration>, shared_ptr<Code>);
shared_ptr<AtribCode> parseAtribuitionCode(shared_ptr<Atrib>, shared_ptr<Code>);
shared_ptr<CondCode> parseConditionalCode(shared_ptr<Cond>, shared_ptr<Code>);
shared_ptr<RepCode> parseRepetitionCode(shared_ptr<Rep>, shared_ptr<Code>);
shared_ptr<CallCode> parseCallCode(shared_ptr<Call>, shared_ptr<Code>);
shared_ptr<Declaration> parseDeclaration(shared_ptr<Atrib>);
shared_ptr<Atrib> parseAtribuition(string, shared_ptr<Expression>);
shared_ptr<NumberExpression> parseNumberExpression(int, shared_ptr<Operation>);
shared_ptr<IdExpression> parseIdExpression(string, shared_ptr<Operation>);
shared_ptr<ParenExpression> parseParenExpression(shared_ptr<Expression>);
shared_ptr<OpOperation> parseOpOperation(string, shared_ptr<Expression>);
shared_ptr<Bool> parseBool(shared_ptr<Expression>, string, shared_ptr<Expression>, shared_ptr<BoolOp>);
shared_ptr<BoBoolOp> parseBoBoolOperation(string, shared_ptr<Bool>);
shared_ptr<Cond> parseConditional(shared_ptr<Bool>, shared_ptr<Code>, shared_ptr<Else>);
shared_ptr<ElElse> parseElElse(shared_ptr<Code>);
shared_ptr<Rep> parseRepetition(shared_ptr<Bool>, shared_ptr<Code>);
shared_ptr<Call> parseCall(string, shared_ptr<Param>);
shared_ptr<ExprParam> parseExpressionParameter(shared_ptr<Expression>);

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

#include "parser-classes.cpp"

#endif
#ifndef PARSERCLASSES_H
#define PARSERCLASSES_H
#include <iostream>
#include <memory>
#include <stack>

#include "../shared/allincludes.h"
#include "../shared/namespaces.h"

class ParserRule {
   public:
    virtual parser_rule getParserRule() { return parser_rule(); };
};

class Code : public ParserRule {
   public:
    parser_rule getParserRule() { return parser_rule(); };
};

class Expression : public ParserRule {
   public:
    parser_rule getParserRule() { return parser_rule(); };
};

class Operation : public ParserRule {
   public:
    parser_rule getParserRule() { return parser_rule(); };
};

class BoolOp : public ParserRule {
   public:
    parser_rule getParserRule() { return parser_rule(); };
};

class Else : public ParserRule {
   public:
    parser_rule getParserRule() { return parser_rule(); };
};

class Param : public ParserRule {
   public:
    parser_rule getParserRule() { return parser_rule(); };
};

class S : public ParserRule {
   public:
    shared_ptr<Code> code;

    S() {}
    S(shared_ptr<Code> code) : code(move(code)) {}

    parser_rule getParserRule() override;
};

class LambdaCode : public Code {
   public:
    LambdaCode() {}
    parser_rule getParserRule() override;
};

class Atrib : public ParserRule {
   public:
    string id;
    shared_ptr<Expression> expr;

    Atrib() {}
    Atrib(string id, shared_ptr<Expression> expr) : id(id), expr(move(expr)) {}

    parser_rule getParserRule() override;
};

class Declaration : public ParserRule {
   public:
    shared_ptr<Atrib> atrib;

    Declaration() {}
    Declaration(shared_ptr<Atrib> atrib) : atrib(move(atrib)) {}

    parser_rule getParserRule() override;
};

class NumberExpression : public Expression {
   public:
    int number;
    shared_ptr<Operation> op;

    NumberExpression() {}
    NumberExpression(int number, shared_ptr<Operation> op) : number(number), op(move(op)) {}

    parser_rule getParserRule() override;
};

class IdExpression : public Expression {
   public:
    string id;
    shared_ptr<Operation> op;

    IdExpression() {}
    IdExpression(string id, shared_ptr<Operation> op) : id(id), op(move(op)) {}

    parser_rule getParserRule() override;
};

class ParenExpression : public Expression {
   public:
    shared_ptr<Expression> expr;

    ParenExpression() {}
    ParenExpression(shared_ptr<Expression> expr) : expr(move(expr)) {}

    parser_rule getParserRule() override;
};

class OpOperation : public Operation {
   public:
    string op;
    shared_ptr<Expression> expr;

    OpOperation() {}
    OpOperation(string op, shared_ptr<Expression> expr) : op(op), expr(move(expr)) {}

    parser_rule getParserRule() override;
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
};

class BoBoolOp : public BoolOp {
   public:
    string boolean;
    shared_ptr<Bool> boolptr;

    BoBoolOp() {}
    BoBoolOp(string boolean, shared_ptr<Bool> boolptr) : boolean(boolean), boolptr(move(boolptr)) {}

    parser_rule getParserRule() override;
};

class LambdaBoolOp : public BoolOp {
   public:
    LambdaBoolOp() {}
    parser_rule getParserRule() override;
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
};

class ElElse : public Else {
   public:
    shared_ptr<Code> code;

    ElElse() {}
    ElElse(shared_ptr<Code> code) : code(move(code)) {}

    parser_rule getParserRule() override;
};

class LambdaElse : public Else {
   public:
    LambdaElse() {}
    parser_rule getParserRule() override;
};

class Rep : public ParserRule {
   public:
    shared_ptr<Bool> boolptr;
    shared_ptr<Code> code;

    Rep() {}
    Rep(shared_ptr<Bool> boolptr,
        shared_ptr<Code> code) : boolptr(move(boolptr)), code(move(code)) {}

    parser_rule getParserRule() override;
};

class Call : public ParserRule {
   public:
    string id;
    shared_ptr<Param> param;

    Call() {}
    Call(string id, shared_ptr<Param> param) : id(id), param(move(param)) {}

    parser_rule getParserRule() override;
};

class ExprParam : public Param {
   public:
    shared_ptr<Expression> expr;

    ExprParam() {}
    ExprParam(shared_ptr<Expression> expr) : expr(move(expr)) {}

    parser_rule getParserRule() override;
};

class LambdaParam : public Param {
   public:
    LambdaParam() {}
    parser_rule getParserRule() override;
};

class DecCode : public Code {
   public:
    shared_ptr<Declaration> decl;
    shared_ptr<Code> code;

    DecCode() {}
    DecCode(shared_ptr<Declaration> decl,
            shared_ptr<Code> code) : decl(move(decl)), code(move(code)) {}

    parser_rule getParserRule() override;
};

class AtribCode : public Code {
   public:
    shared_ptr<Atrib> atrib;
    shared_ptr<Code> code;

    AtribCode() {}
    AtribCode(shared_ptr<Atrib> atrib,
              shared_ptr<Code> code) : atrib(move(atrib)), code(move(code)) {}

    parser_rule getParserRule() override;
};

class CondCode : public Code {
   public:
    shared_ptr<Cond> cond;
    shared_ptr<Code> code;

    CondCode() {}
    CondCode(shared_ptr<Cond> cond,
             shared_ptr<Code> code) : cond(move(cond)), code(move(code)) {}

    parser_rule getParserRule() override;
};

class RepCode : public Code {
   public:
    shared_ptr<Rep> rep;
    shared_ptr<Code> code;

    RepCode() {}
    RepCode(shared_ptr<Rep> rep,
            shared_ptr<Code> code) : rep(move(rep)), code(move(code)) {}

    parser_rule getParserRule() override;
};

class CallCode : public Code {
   public:
    shared_ptr<Call> call;
    shared_ptr<Code> code;

    CallCode() {}
    CallCode(shared_ptr<Call> call,
             shared_ptr<Code> code) : call(move(call)), code(move(code)) {}

    parser_rule getParserRule() override;
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
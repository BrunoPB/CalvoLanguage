#ifndef PARSER_H
#define PARSER_H
#include <iostream>
#include <memory>
#include <vector>

using std::string, std::unique_ptr, std::move, std::vector;

class S {
    unique_ptr<Code> code;

   public:
    S(unique_ptr<Code> code) : code(move(code)) {}
};

class Code {
};

class LambdaCode : public Code {
};

class DecCode : public Code {
    unique_ptr<Declaration> decl;
    unique_ptr<Code> code;

   public:
    DecCode(unique_ptr<Declaration> decl,
            unique_ptr<Code> code) : decl(move(decl)), code(move(code)) {}
};

class AtribCode : public Code {
    unique_ptr<Atrib> atrib;
    unique_ptr<Code> code;

   public:
    AtribCode(unique_ptr<Atrib> atrib,
              unique_ptr<Code> code) : atrib(move(atrib)), code(move(code)) {}
};

class CondCode : public Code {
    unique_ptr<Cond> cond;
    unique_ptr<Code> code;

   public:
    CondCode(unique_ptr<Cond> cond,
             unique_ptr<Code> code) : cond(move(cond)), code(move(code)) {}
};

class RepCode : public Code {
    unique_ptr<Rep> rep;
    unique_ptr<Code> code;

   public:
    RepCode(unique_ptr<Rep> rep,
            unique_ptr<Code> code) : rep(move(rep)), code(move(code)) {}
};

class CallCode : public Code {
    unique_ptr<Call> call;
    unique_ptr<Code> code;

   public:
    CallCode(unique_ptr<Call> call,
             unique_ptr<Code> code) : call(move(call)), code(move(code)) {}
};

class Declaration {
    unique_ptr<Atrib> atrib;

   public:
    Declaration(unique_ptr<Atrib> atrib) : atrib(move(atrib)) {}
};

class Atrib {
    string id;
    unique_ptr<Expression> expr;

   public:
    Atrib(string id, unique_ptr<Expression> expr) : id(id), expr(move(expr)) {}
};

class Expression {
};

class NumberExpression : public Expression {
    int number;
    unique_ptr<Operation> op;

   public:
    NumberExpression(int number, unique_ptr<Operation> op) : number(number), op(move(op)) {}
};

class IdExpression : public Expression {
    string id;
    unique_ptr<Operation> op;

   public:
    IdExpression(string id, unique_ptr<Operation> op) : id(id), op(move(op)) {}
};

class ParenExpression : public Expression {
    unique_ptr<Expression> expr;

   public:
    ParenExpression(unique_ptr<Expression> expr) : expr(move(expr)) {}
};

class Operation {
};

class OpOperation : public Operation {
    string op;
    unique_ptr<Expression> expr;

   public:
    OpOperation(string op, unique_ptr<Expression> expr) : op(op), expr(move(expr)) {}
};

class LambdaOperation : public Operation {
};

class Bool {
    unique_ptr<Expression> expr1;
    string compare;
    unique_ptr<Expression> expr2;
    unique_ptr<BoolOp> boolop;

   public:
    Bool(unique_ptr<Expression> expr1,
         string compare,
         unique_ptr<Expression> expr2,
         unique_ptr<BoolOp> boolop) : expr1(move(expr1)), compare(compare), expr2(move(expr2)), boolop(move(boolop)) {}
};

class BoolOp {
};

class BoBoolOp : BoolOp {
    string boolean;
    unique_ptr<Bool> boolptr;

   public:
    BoBoolOp(string boolean, unique_ptr<Bool> boolptr) : boolean(boolean), boolptr(move(boolptr)) {}
};

class LambdaBoolOp : BoolOp {
};

class Cond {
    unique_ptr<Bool> boolptr;
    unique_ptr<Code> code;
    unique_ptr<Else> elseptr;

   public:
    Cond(unique_ptr<Bool> boolptr,
         unique_ptr<Code> code,
         unique_ptr<Else> elseptr) : boolptr(move(boolptr)), code(move(code)), elseptr(move(elseptr)) {}
};

class Else {
};

class ElElse : Else {
    unique_ptr<Code> code;

   public:
    ElElse(unique_ptr<Code> code) : code(move(code)) {}
};

class LambdaElse : Else {
};

class Rep {
    unique_ptr<Bool> boolptr;
    unique_ptr<Code> code;

   public:
    Rep(unique_ptr<Bool> boolptr,
        unique_ptr<Code> code) : boolptr(move(boolptr)), code(move(code)) {}
};

class Call {
    unique_ptr<Param> param;

   public:
    Call(unique_ptr<Param> param) : param(move(param)) {}
};

class Param {
};

class ExprParam : public Param {
    unique_ptr<Expression> expr;

   public:
    ExprParam(unique_ptr<Expression> expr) : expr(move(expr)) {}
};

class LambdaParam : public Param {
};

unique_ptr<S> parseS(unique_ptr<Code>);
unique_ptr<DecCode> parseDeclarationCode(unique_ptr<Declaration>,unique_ptr<Code>);
unique_ptr<AtribCode> parseAtribuitionCode(unique_ptr<Atrib>,unique_ptr<Code>);
unique_ptr<CondCode> parseConditionalCode(unique_ptr<Cond>,unique_ptr<Code>);
unique_ptr<RepCode> parseRepetitionCode(unique_ptr<Rep>,unique_ptr<Code>);
unique_ptr<CallCode> parseCallCode(unique_ptr<Call>,unique_ptr<Code>);
unique_ptr<Declaration> parseDeclaration(unique_ptr<Atrib>);
unique_ptr<Atrib> parseAtribuition(string,unique_ptr<Expression>);
unique_ptr<NumberExpression> parseNumberExpression(int,unique_ptr<Operation>);
unique_ptr<IdExpression> parseIdExpression(string,unique_ptr<Operation>);
unique_ptr<ParenExpression> parseParenExpression(unique_ptr<Expression>);
unique_ptr<OpOperation> parseOpOperation(string,unique_ptr<Expression>);
unique_ptr<Bool> parseBool(unique_ptr<Expression>,string,unique_ptr<Expression>,unique_ptr<BoolOp>);
unique_ptr<BoBoolOp> parseBoBoolOperation(string,unique_ptr<Bool>);
unique_ptr<Cond> parseConditional(unique_ptr<Bool>,unique_ptr<Code>,unique_ptr<Else>);
unique_ptr<Else> parseElse(unique_ptr<Code>);
unique_ptr<Rep> parseRepetition(unique_ptr<Bool>,unique_ptr<Code>);
unique_ptr<Call> parseCall(string,unique_ptr<Param>);
unique_ptr<ExprParam> parseExpressionParameter(unique_ptr<Expression>);

// TODO: Does the Kaleidoscope language have if-else or do-while statements?

#include "parser.cpp"

#endif
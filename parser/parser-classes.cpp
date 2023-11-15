#include "parser-classes.h"

#include <iostream>
#include <memory>

shared_ptr<S> parseStart(shared_ptr<Code> code) {
    S s = S(move(code));
    shared_ptr<S> result = make_shared<S>(move(s));
    return result;
}

shared_ptr<DecCode> parseDeclarationCode(shared_ptr<Declaration> decl, shared_ptr<Code> code) {
    DecCode dc = DecCode(move(decl), move(code));
    shared_ptr<DecCode> result = make_shared<DecCode>(move(dc));
    return result;
}

shared_ptr<AtribCode> parseAtribuitionCode(shared_ptr<Atrib> atrib, shared_ptr<Code> code) {
    AtribCode ac = AtribCode(move(atrib), move(code));
    shared_ptr<AtribCode> result = make_shared<AtribCode>(move(ac));
    return result;
}

shared_ptr<CondCode> parseConditionalCode(shared_ptr<Cond> cond, shared_ptr<Code> code) {
    CondCode cc = CondCode(move(cond), move(code));
    shared_ptr<CondCode> result = make_shared<CondCode>(move(cc));
    return result;
}

shared_ptr<RepCode> parseRepetitionCode(shared_ptr<Rep> rep, shared_ptr<Code> code) {
    RepCode rc = RepCode(move(rep), move(code));
    shared_ptr<RepCode> result = make_shared<RepCode>(move(rc));
    return result;
}

shared_ptr<CallCode> parseCallCode(shared_ptr<Call> call, shared_ptr<Code> code) {
    CallCode clc = CallCode(move(call), move(code));
    shared_ptr<CallCode> result = make_shared<CallCode>(move(clc));
    return result;
}

shared_ptr<Declaration> parseDeclaration(shared_ptr<Atrib> atrib) {
    Declaration d = Declaration(move(atrib));
    shared_ptr<Declaration> result = make_shared<Declaration>(move(d));
    return result;
}

shared_ptr<Atrib> parseAtribuition(string id, shared_ptr<Expression> expr) {
    Atrib a = Atrib(move(id), move(expr));
    shared_ptr<Atrib> result = make_shared<Atrib>(move(a));
    return result;
}

shared_ptr<NumberExpression> parseNumberExpression(int number, shared_ptr<Operation> op) {
    NumberExpression ne = NumberExpression(number, move(op));
    shared_ptr<NumberExpression> result = make_shared<NumberExpression>(move(ne));
    return result;
}

shared_ptr<IdExpression> parseIdExpression(string id, shared_ptr<Operation> op) {
    IdExpression ie = IdExpression(id, move(op));
    shared_ptr<IdExpression> result = make_shared<IdExpression>(move(ie));
    return result;
}

shared_ptr<ParenExpression> parseParenExpression(shared_ptr<Expression> expr) {
    ParenExpression pe = ParenExpression(move(expr));
    shared_ptr<ParenExpression> result = make_shared<ParenExpression>(move(expr));
    return result;
}

shared_ptr<OpOperation> parseOpOperation(string op, shared_ptr<Expression> expr) {
    OpOperation oo = OpOperation(op, move(expr));
    shared_ptr<OpOperation> result = make_shared<OpOperation>(move(oo));
    return result;
}

shared_ptr<Bool> parseBool(shared_ptr<Expression> expr1, string compare, shared_ptr<Expression> expr2, shared_ptr<BoolOp> boolop) {
    Bool b = Bool(move(expr1), compare, move(expr2), move(boolop));
    shared_ptr<Bool> result = make_shared<Bool>(move(b));
    return result;
}

shared_ptr<BoBoolOp> parseBoBoolOperation(string boolop, shared_ptr<Bool> boolptr) {
    BoBoolOp bbo = BoBoolOp(boolop, move(boolptr));
    shared_ptr<BoBoolOp> result = make_shared<BoBoolOp>(move(bbo));
    return result;
}

shared_ptr<Cond> parseConditional(shared_ptr<Bool> boolptr, shared_ptr<Code> code, shared_ptr<Else> elseptr) {
    Cond c = Cond(move(boolptr), move(code), move(elseptr));
    shared_ptr<Cond> result = make_shared<Cond>(move(c));
    return result;
}

shared_ptr<ElElse> parseElElse(shared_ptr<Code> code) {
    ElElse ee = ElElse(move(code));
    shared_ptr<ElElse> result = make_shared<ElElse>(move(ee));
    return result;
}

shared_ptr<Rep> parseRepetition(shared_ptr<Bool> boolptr, shared_ptr<Code> code) {
    Rep r = Rep(move(boolptr), move(code));
    shared_ptr<Rep> result = make_shared<Rep>(move(r));
    return result;
}

shared_ptr<Call> parseCall(string id, shared_ptr<Param> param) {
    Call cll = Call(id, move(param));
    shared_ptr<Call> result = make_shared<Call>(move(cll));
    return result;
}

shared_ptr<ExprParam> parseExpressionParameter(shared_ptr<Expression> expr) {
    ExprParam ep = ExprParam(move(expr));
    shared_ptr<ExprParam> result = make_shared<ExprParam>(move(ep));
    return result;
}

parser_rule S::getParserRule() {
    int left = nt_S;
    vector<int> right = {nt_CODE};
    return make_tuple(left, right);
}

parser_rule LambdaCode::getParserRule() {
    int left = nt_CODE;
    vector<int> right = {};
    return make_tuple(left, right);
}

parser_rule DecCode::getParserRule() {
    int left = nt_CODE;
    vector<int> right = {nt_DECLARATION, nt_CODE};
    return make_tuple(left, right);
}

parser_rule AtribCode::getParserRule() {
    int left = nt_CODE;
    vector<int> right = {nt_ATRIB, nt_CODE};
    return make_tuple(left, right);
}

parser_rule CondCode::getParserRule() {
    int left = nt_CODE;
    vector<int> right = {nt_COND, nt_CODE};
    return make_tuple(left, right);
}

parser_rule RepCode::getParserRule() {
    int left = nt_CODE;
    vector<int> right = {nt_REP, nt_CODE};
    return make_tuple(left, right);
}

parser_rule CallCode::getParserRule() {
    int left = nt_CODE;
    vector<int> right = {nt_CALL, nt_CODE};
    return make_tuple(left, right);
}

parser_rule Declaration::getParserRule() {
    int left = nt_DECLARATION;
    vector<int> right = {tok_var, nt_ATRIB};
    return make_tuple(left, right);
}

parser_rule Atrib::getParserRule() {
    int left = nt_ATRIB;
    vector<int> right = {tok_id, tok_equal, nt_EXPRESSION, tok_semicolon};
    return make_tuple(left, right);
}

parser_rule NumberExpression::getParserRule() {
    int left = nt_EXPRESSION;
    vector<int> right = {tok_number, nt_OPERATION};
    return make_tuple(left, right);
}

parser_rule IdExpression::getParserRule() {
    int left = nt_EXPRESSION;
    vector<int> right = {tok_id, nt_OPERATION};
    return make_tuple(left, right);
}

parser_rule ParenExpression::getParserRule() {
    int left = nt_EXPRESSION;
    vector<int> right = {tok_paren_o, nt_EXPRESSION, tok_paren_c};
    return make_tuple(left, right);
}

parser_rule OpOperation::getParserRule() {
    int left = nt_OPERATION;
    vector<int> right = {tok_operator, nt_EXPRESSION};
    return make_tuple(left, right);
}

parser_rule LambdaOperation::getParserRule() {
    int left = nt_OPERATION;
    vector<int> right = {};
    return make_tuple(left, right);
}

parser_rule Bool::getParserRule() {
    int left = nt_BOOL;
    vector<int> right = {nt_EXPRESSION, tok_compare, nt_EXPRESSION, nt_BOOLOP};
    return make_tuple(left, right);
}

parser_rule BoBoolOp::getParserRule() {
    int left = nt_BOOLOP;
    vector<int> right = {tok_boolean, nt_BOOL};
    return make_tuple(left, right);
}

parser_rule LambdaBoolOp::getParserRule() {
    int left = nt_BOOLOP;
    vector<int> right = {};
    return make_tuple(left, right);
}

parser_rule Cond::getParserRule() {
    int left = nt_COND;
    vector<int> right = {tok_if, tok_paren_o, nt_BOOL, tok_paren_c, tok_bracket_o, nt_CODE, tok_bracket_c, nt_ELSE};
    return make_tuple(left, right);
}

parser_rule ElElse::getParserRule() {
    int left = nt_ELSE;
    vector<int> right = {tok_else, tok_bracket_o, nt_CODE, tok_bracket_c};
    return make_tuple(left, right);
}

parser_rule LambdaElse::getParserRule() {
    int left = nt_ELSE;
    vector<int> right = {};
    return make_tuple(left, right);
}

parser_rule Rep::getParserRule() {
    int left = nt_REP;
    vector<int> right = {tok_while, tok_paren_o, nt_BOOL, tok_paren_c, tok_bracket_o, nt_CODE, tok_bracket_c};
    return make_tuple(left, right);
}

parser_rule Call::getParserRule() {
    int left = nt_CALL;
    vector<int> right = {tok_id, tok_paren_o, nt_PARAM, tok_paren_c, tok_semicolon};
    return make_tuple(left, right);
}

parser_rule ExprParam::getParserRule() {
    int left = nt_PARAM;
    vector<int> right = {nt_EXPRESSION};
    return make_tuple(left, right);
}

parser_rule LambdaParam::getParserRule() {
    int left = nt_PARAM;
    vector<int> right = {};
    return make_tuple(left, right);
}

// Value* S::codegen() {

// }
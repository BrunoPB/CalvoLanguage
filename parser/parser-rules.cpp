#include "parser-classes.h"

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
    vector<int> right = {tok_paren_o, nt_EXPRESSION, tok_paren_c, nt_OPERATION};
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
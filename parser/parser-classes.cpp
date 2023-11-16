#include "parser-classes.h"

#include <iostream>
#include <memory>

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

Value* LogErrorV(const char* Str) {
    cerr << *Str << endl;
    return nullptr;
}

int getRuleNumber(parser_rule rule) {
    S s = S();
    if (rule == s.getParserRule()) {
        return 0;
    }
    LambdaCode lc = LambdaCode();
    if (rule == lc.getParserRule()) {
        return 1;
    }
    DecCode dc = DecCode();
    if (rule == dc.getParserRule()) {
        return 2;
    }
    AtribCode ac = AtribCode();
    if (rule == ac.getParserRule()) {
        return 3;
    }
    CondCode cc = CondCode();
    if (rule == cc.getParserRule()) {
        return 4;
    }
    RepCode rc = RepCode();
    if (rule == rc.getParserRule()) {
        return 5;
    }
    CallCode clc = CallCode();
    if (rule == clc.getParserRule()) {
        return 6;
    }
    Declaration d = Declaration();
    if (rule == d.getParserRule()) {
        return 7;
    }
    Atrib a = Atrib();
    if (rule == a.getParserRule()) {
        return 8;
    }
    NumberExpression ne = NumberExpression();
    if (rule == ne.getParserRule()) {
        return 9;
    }
    IdExpression ie = IdExpression();
    if (rule == ie.getParserRule()) {
        return 10;
    }
    ParenExpression pe = ParenExpression();
    if (rule == pe.getParserRule()) {
        return 11;
    }
    OpOperation oo = OpOperation();
    if (rule == oo.getParserRule()) {
        return 12;
    }
    LambdaOperation lo = LambdaOperation();
    if (rule == lo.getParserRule()) {
        return 13;
    }
    Bool b = Bool();
    if (rule == b.getParserRule()) {
        return 14;
    }
    BoBoolOp bbo = BoBoolOp();
    if (rule == bbo.getParserRule()) {
        return 15;
    }
    LambdaBoolOp lbo = LambdaBoolOp();
    if (rule == lbo.getParserRule()) {
        return 16;
    }
    Cond c = Cond();
    if (rule == c.getParserRule()) {
        return 17;
    }
    ElElse ee = ElElse();
    if (rule == ee.getParserRule()) {
        return 18;
    }
    LambdaElse le = LambdaElse();
    if (rule == le.getParserRule()) {
        return 19;
    }
    Rep r = Rep();
    if (rule == r.getParserRule()) {
        return 20;
    }
    Call cl = Call();
    if (rule == cl.getParserRule()) {
        return 21;
    }
    ExprParam ep = ExprParam();
    if (rule == ep.getParserRule()) {
        return 22;
    }
    LambdaParam lp = LambdaParam();
    if (rule == lp.getParserRule()) {
        return 23;
    }
    return -1;
}

parser_rule getRuleFromNumber(int number) {
    switch (number) {
        case 0: {
            S s = S();
            return s.getParserRule();
        }
        case 1: {
            LambdaCode lc = LambdaCode();
            return lc.getParserRule();
        }
        case 2: {
            DecCode dc = DecCode();
            return dc.getParserRule();
        }
        case 3: {
            AtribCode ac = AtribCode();
            return ac.getParserRule();
        }
        case 4: {
            CondCode cc = CondCode();
            return cc.getParserRule();
        }
        case 5: {
            RepCode rc = RepCode();
            return rc.getParserRule();
        }
        case 6: {
            CallCode clc = CallCode();
            return clc.getParserRule();
        }
        case 7: {
            Declaration d = Declaration();
            return d.getParserRule();
        }
        case 8: {
            Atrib a = Atrib();
            return a.getParserRule();
        }
        case 9: {
            NumberExpression ne = NumberExpression();
            return ne.getParserRule();
        }
        case 10: {
            IdExpression ie = IdExpression();
            return ie.getParserRule();
        }
        case 11: {
            ParenExpression pe = ParenExpression();
            return pe.getParserRule();
        }
        case 12: {
            OpOperation oo = OpOperation();
            return oo.getParserRule();
        }
        case 13: {
            LambdaOperation lo = LambdaOperation();
            return lo.getParserRule();
        }
        case 14: {
            Bool b = Bool();
            return b.getParserRule();
        }
        case 15: {
            BoBoolOp bbo = BoBoolOp();
            return bbo.getParserRule();
        }
        case 16: {
            LambdaBoolOp lbo = LambdaBoolOp();
            return lbo.getParserRule();
        }
        case 17: {
            Cond c = Cond();
            return c.getParserRule();
        }
        case 18: {
            ElElse ee = ElElse();
            return ee.getParserRule();
        }
        case 19: {
            LambdaElse le = LambdaElse();
            return le.getParserRule();
        }
        case 20: {
            Rep r = Rep();
            return r.getParserRule();
        }
        case 21: {
            Call cll = Call();
            return cll.getParserRule();
        }
        case 22: {
            ExprParam ep = ExprParam();
            return ep.getParserRule();
        }
        case 23: {
            LambdaParam lp = LambdaParam();
            return lp.getParserRule();
        }
    }
    return make_tuple(0, vector<int>());
}

Value* S::codegen() {
    return code->codegen();
}

Value* CallCode::codegen() {
    Value* callRet = call->codegen();
    Value* codeRet = code->codegen();
    return nullptr;
}

Value* Call::codegen() {
    FunctionCallee fnCall;
    Value* arg = param->codegen();
    if (id == "show") {
        static Value* pdStr;
        if (pdStr == nullptr) {
            pdStr = Builder->CreateGlobalStringPtr("%d\n");
        }
        fnCall = TheModule->getFunction("printf");
        ArrayRef<Value*> args = {pdStr, move(arg)};
        return Builder->CreateCall(fnCall, args);
    } else {
        cout << "SHIT! THE FUNCTION CALL IS WRONG!\n";
    }
    return Builder->CreateCall(fnCall, arg);
}

Value* ExprParam::codegen() {
    return expr->codegen();
}

Value* NumberExpression::codegen() {
    Value* cOp = op->codegen();
    ConstantInt* cNumber = Builder->getInt32(number);
    return cNumber;
}

// Value* Atrib::codegen() {
//     NamedValues[id] = expr->codegen();
// }

// Value* LambdaOperation::codegen() {
//     return nullptr;
// }
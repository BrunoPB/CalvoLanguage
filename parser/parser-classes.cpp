#include "parser-classes.h"

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
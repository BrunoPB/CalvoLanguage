#include "parser-classes.h"

int getRuleNumber(parser_rule rule) {
    S s = S();
    if (rule == s.getParserRule()) {
        return 0;
    }
    LambdaCode lc = LambdaCode();
    if (rule == lc.getParserRule()) {
        return 1;
    }
    AtribCode ac = AtribCode();
    if (rule == ac.getParserRule()) {
        return 2;
    }
    CondCode cc = CondCode();
    if (rule == cc.getParserRule()) {
        return 3;
    }
    RepCode rc = RepCode();
    if (rule == rc.getParserRule()) {
        return 4;
    }
    CallCode clc = CallCode();
    if (rule == clc.getParserRule()) {
        return 5;
    }
    Atrib a = Atrib();
    if (rule == a.getParserRule()) {
        return 6;
    }
    NumberExpression ne = NumberExpression();
    if (rule == ne.getParserRule()) {
        return 7;
    }
    IdExpression ie = IdExpression();
    if (rule == ie.getParserRule()) {
        return 8;
    }
    ParenExpression pe = ParenExpression();
    if (rule == pe.getParserRule()) {
        return 9;
    }
    OpOperation oo = OpOperation();
    if (rule == oo.getParserRule()) {
        return 10;
    }
    LambdaOperation lo = LambdaOperation();
    if (rule == lo.getParserRule()) {
        return 11;
    }
    Bool b = Bool();
    if (rule == b.getParserRule()) {
        return 12;
    }
    BoBoolOp bbo = BoBoolOp();
    if (rule == bbo.getParserRule()) {
        return 13;
    }
    LambdaBoolOp lbo = LambdaBoolOp();
    if (rule == lbo.getParserRule()) {
        return 14;
    }
    Cond c = Cond();
    if (rule == c.getParserRule()) {
        return 15;
    }
    ElElse ee = ElElse();
    if (rule == ee.getParserRule()) {
        return 16;
    }
    LambdaElse le = LambdaElse();
    if (rule == le.getParserRule()) {
        return 17;
    }
    Rep r = Rep();
    if (rule == r.getParserRule()) {
        return 18;
    }
    Call cl = Call();
    if (rule == cl.getParserRule()) {
        return 19;
    }
    ExprParam ep = ExprParam();
    if (rule == ep.getParserRule()) {
        return 20;
    }
    LambdaParam lp = LambdaParam();
    if (rule == lp.getParserRule()) {
        return 21;
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
            AtribCode ac = AtribCode();
            return ac.getParserRule();
        }
        case 3: {
            CondCode cc = CondCode();
            return cc.getParserRule();
        }
        case 4: {
            RepCode rc = RepCode();
            return rc.getParserRule();
        }
        case 5: {
            CallCode clc = CallCode();
            return clc.getParserRule();
        }
        case 6: {
            Atrib a = Atrib();
            return a.getParserRule();
        }
        case 7: {
            NumberExpression ne = NumberExpression();
            return ne.getParserRule();
        }
        case 8: {
            IdExpression ie = IdExpression();
            return ie.getParserRule();
        }
        case 9: {
            ParenExpression pe = ParenExpression();
            return pe.getParserRule();
        }
        case 10: {
            OpOperation oo = OpOperation();
            return oo.getParserRule();
        }
        case 11: {
            LambdaOperation lo = LambdaOperation();
            return lo.getParserRule();
        }
        case 12: {
            Bool b = Bool();
            return b.getParserRule();
        }
        case 13: {
            BoBoolOp bbo = BoBoolOp();
            return bbo.getParserRule();
        }
        case 14: {
            LambdaBoolOp lbo = LambdaBoolOp();
            return lbo.getParserRule();
        }
        case 15: {
            Cond c = Cond();
            return c.getParserRule();
        }
        case 16: {
            ElElse ee = ElElse();
            return ee.getParserRule();
        }
        case 17: {
            LambdaElse le = LambdaElse();
            return le.getParserRule();
        }
        case 18: {
            Rep r = Rep();
            return r.getParserRule();
        }
        case 19: {
            Call cll = Call();
            return cll.getParserRule();
        }
        case 20: {
            ExprParam ep = ExprParam();
            return ep.getParserRule();
        }
        case 21: {
            LambdaParam lp = LambdaParam();
            return lp.getParserRule();
        }
    }
    return make_tuple(0, vector<int>());
}
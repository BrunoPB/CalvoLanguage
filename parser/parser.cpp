#include "parser.h"

shared_ptr<S> getAST(parsing_table parsingTable, vector<token> tokens) {
    ParserClasses ASTStack = ParserClasses();
    stack<token> tokenStack = {};
    stack<int> stack = {};
    stack.push(0);
    vector<token> input = move(tokens);
    input.push_back(make_tuple(tok_id - 1, "$"));
    tokenStack.push(make_tuple(tok_id - 1, "$"));
    bool doneParsing = false;
    while (!doneParsing) {
        tuple<int, int> key = make_tuple(get<0>(input[0]), stack.top());
        if (parsingTable.count(key) < 1) {
            string errorMsg = "Syntax error in " + get<1>(input[0]);
            error("PARSER", errorMsg);
        }
        switch (get<0>(parsingTable[key])) {
            case 'a': {
                generateASTFromRule(&ASTStack, &tokenStack, 0);
                doneParsing = true;
                break;
            }
            case 's': {
                tokenStack.push(input[0]);
                input = vector<token>(input.begin() + 1, input.end());
                int stateNumber = get<1>(parsingTable[key]);
                stack.push(stateNumber);
                break;
            }
            case 'r': {
                int ruleNumber = get<1>(parsingTable[key]);
                parser_rule rule = getRuleFromNumber(ruleNumber);

                generateASTFromRule(&ASTStack, &tokenStack, ruleNumber);

                int productionSize = get<1>(rule).size();
                for (int i = 0; i < productionSize; i++) {
                    stack.pop();
                }
                key = make_tuple(get<0>(rule), stack.top());
                int stateNumber = get<1>(parsingTable[key]);
                stack.push(stateNumber);
                break;
            }
            default:
                error("PARSER", "Unhandled");
                break;
        }
    }
    return move(ASTStack.s.top());
}

void generateASTFromRule(ParserClasses* ASTStack, stack<token>* tokenStack, int ruleNumber) {
    switch (ruleNumber) {
        case 0: {
            shared_ptr<Code> c = shared_ptr<Code>{ASTStack->c.top()};
            ASTStack->c.pop();
            S s = S(move(c));
            ASTStack->s.push(move(make_shared<S>(s)));
            break;
        }
        case 1: {
            LambdaCode lc = LambdaCode();
            ASTStack->c.push(move(make_shared<LambdaCode>(lc)));
            break;
        }
        case 2: {
            shared_ptr<Code> c = shared_ptr<Code>{ASTStack->c.top()};
            ASTStack->c.pop();
            shared_ptr<Atrib> a = shared_ptr<Atrib>{ASTStack->a.top()};
            ASTStack->a.pop();
            AtribCode ac = AtribCode(move(a), move(c));
            ASTStack->c.push(move(make_shared<AtribCode>(ac)));
            break;
        }
        case 3: {
            shared_ptr<Code> c = shared_ptr<Code>{ASTStack->c.top()};
            ASTStack->c.pop();
            shared_ptr<Cond> cn = shared_ptr<Cond>{ASTStack->cn.top()};
            ASTStack->cn.pop();
            CondCode cc = CondCode(move(cn), move(c));
            ASTStack->c.push(move(make_shared<CondCode>(cc)));
            break;
        }
        case 4: {
            shared_ptr<Code> c = shared_ptr<Code>{ASTStack->c.top()};
            ASTStack->c.pop();
            shared_ptr<Rep> r = shared_ptr<Rep>{ASTStack->r.top()};
            ASTStack->r.pop();
            RepCode rc = RepCode(move(r), move(c));
            ASTStack->c.push(move(make_shared<RepCode>(rc)));
            break;
        }
        case 5: {
            shared_ptr<Code> c = shared_ptr<Code>{ASTStack->c.top()};
            ASTStack->c.pop();
            shared_ptr<Call> cl = shared_ptr<Call>{ASTStack->cl.top()};
            ASTStack->cl.pop();
            CallCode clc = CallCode(move(cl), move(c));
            ASTStack->c.push(move(make_shared<CallCode>(clc)));
            break;
        }
        case 6: {
            shared_ptr<Expression> expr = shared_ptr<Expression>{ASTStack->expr.top()};
            ASTStack->expr.pop();
            tokenStack->pop();  // Removed ";" terminal
            tokenStack->pop();  // Removed "=" terminal
            string id = get<1>(tokenStack->top());
            tokenStack->pop();  // Removed id terminal
            Atrib a = Atrib(id, move(expr));
            ASTStack->a.push(move(make_shared<Atrib>(a)));
            break;
        }
        case 7: {
            shared_ptr<Operation> o = shared_ptr<Operation>{ASTStack->o.top()};
            ASTStack->o.pop();
            int number = stoi(get<1>(tokenStack->top()));
            tokenStack->pop();  // Removed number terminal
            NumberExpression ne = NumberExpression(number, move(o));
            ASTStack->expr.push(move(make_shared<NumberExpression>(ne)));
            break;
        }
        case 8: {
            shared_ptr<Operation> op = shared_ptr<Operation>{ASTStack->o.top()};
            ASTStack->o.pop();
            string id = get<1>(tokenStack->top());
            tokenStack->pop();  // Removed id terminal
            IdExpression ie = IdExpression(id, move(op));
            ASTStack->expr.push(move(make_shared<IdExpression>(ie)));
            break;
        }
        case 9: {
            shared_ptr<Operation> op = shared_ptr<Operation>{ASTStack->o.top()};
            ASTStack->o.pop();
            shared_ptr<Expression> expr = shared_ptr<Expression>{ASTStack->expr.top()};
            ASTStack->expr.pop();
            tokenStack->pop();  // Removed ")" terminal
            tokenStack->pop();  // Removed "(" terminal
            ParenExpression pe = ParenExpression(move(expr), move(op));
            ASTStack->expr.push(move(make_shared<ParenExpression>(pe)));
            break;
        }
        case 10: {
            shared_ptr<Expression> expr = shared_ptr<Expression>{ASTStack->expr.top()};
            ASTStack->expr.pop();
            string op = get<1>(tokenStack->top());
            tokenStack->pop();  // Removed operator terminal
            OpOperation oo = OpOperation(op, move(expr));
            ASTStack->o.push(move(make_shared<OpOperation>(oo)));
            break;
        }
        case 11: {
            LambdaOperation lo = LambdaOperation();
            ASTStack->o.push(move(make_shared<LambdaOperation>(lo)));
            break;
        }
        case 12: {
            shared_ptr<BoolOp> boolop = shared_ptr<BoolOp>{ASTStack->bo.top()};
            ASTStack->bo.pop();
            shared_ptr<Expression> expr2 = shared_ptr<Expression>{ASTStack->expr.top()};
            ASTStack->expr.pop();
            string compare = get<1>(tokenStack->top());
            tokenStack->pop();  // Removed compare terminal
            shared_ptr<Expression> expr1 = shared_ptr<Expression>{ASTStack->expr.top()};
            ASTStack->expr.pop();
            Bool b = Bool(move(expr1), compare, move(expr2), move(boolop));
            ASTStack->b.push(move(make_shared<Bool>(b)));
            break;
        }
        case 13: {
            shared_ptr<Bool> boolptr = shared_ptr<Bool>{ASTStack->b.top()};
            ASTStack->b.pop();
            string boolean = get<1>(tokenStack->top());
            tokenStack->pop();  // Removed boolean terminal
            BoBoolOp bbo = BoBoolOp(boolean, move(boolptr));
            ASTStack->bo.push(move(make_shared<BoBoolOp>(bbo)));
            break;
        }
        case 14: {
            LambdaBoolOp lbo = LambdaBoolOp();
            ASTStack->bo.push(move(make_shared<LambdaBoolOp>(lbo)));
            break;
        }
        case 15: {
            shared_ptr<Else> elseptr = shared_ptr<Else>{ASTStack->e.top()};
            ASTStack->e.pop();
            shared_ptr<Code> c = shared_ptr<Code>{ASTStack->c.top()};
            ASTStack->c.pop();
            shared_ptr<Bool> boolptr = shared_ptr<Bool>{ASTStack->b.top()};
            ASTStack->b.pop();
            tokenStack->pop();  // Removed "}" terminal
            tokenStack->pop();  // Removed "{" terminal
            tokenStack->pop();  // Removed ")" terminal
            tokenStack->pop();  // Removed "(" terminal
            tokenStack->pop();  // Removed "if" terminal
            Cond cn = Cond(move(boolptr), move(c), move(elseptr));
            ASTStack->cn.push(move(make_shared<Cond>(cn)));
            break;
        }
        case 16: {
            shared_ptr<Code> c = shared_ptr<Code>{ASTStack->c.top()};
            ASTStack->c.pop();
            tokenStack->pop();  // Removed "}" terminal
            tokenStack->pop();  // Removed "{" terminal
            tokenStack->pop();  // Removed "else" terminal
            ElElse ee = ElElse(move(c));
            ASTStack->e.push(move(make_shared<ElElse>(ee)));
            break;
        }
        case 17: {
            LambdaElse le = LambdaElse();
            ASTStack->e.push(move(make_shared<LambdaElse>(le)));
            break;
        }
        case 18: {
            shared_ptr<Code> c = shared_ptr<Code>{ASTStack->c.top()};
            ASTStack->c.pop();
            shared_ptr<Bool> boolptr = shared_ptr<Bool>{ASTStack->b.top()};
            ASTStack->b.pop();
            tokenStack->pop();  // Removed "}" terminal
            tokenStack->pop();  // Removed "{" terminal
            tokenStack->pop();  // Removed ")" terminal
            tokenStack->pop();  // Removed "(" terminal
            tokenStack->pop();  // Removed "while" terminal
            Rep r = Rep(move(boolptr), move(c));
            ASTStack->r.push(move(make_shared<Rep>(r)));
            break;
        }
        case 19: {
            shared_ptr<Param> p = shared_ptr<Param>{ASTStack->p.top()};
            ASTStack->p.pop();
            tokenStack->pop();  // Removed ";" terminal
            tokenStack->pop();  // Removed ")" terminal
            tokenStack->pop();  // Removed "(" terminal
            string id = get<1>(tokenStack->top());
            tokenStack->pop();  // Removed id terminal
            Call cl = Call(id, move(p));
            ASTStack->cl.push(move(make_shared<Call>(cl)));
            break;
        }
        case 20: {
            shared_ptr<Expression> expr = shared_ptr<Expression>{ASTStack->expr.top()};
            ASTStack->expr.pop();
            ExprParam ep = ExprParam(move(expr));
            ASTStack->p.push(move(make_shared<ExprParam>(ep)));
            break;
        }
        case 21: {
            LambdaParam lp = LambdaParam();
            ASTStack->p.push(move(make_shared<LambdaParam>(lp)));
            break;
        }
        default:
            break;
    }
}

parsing_table getParsingTable(lr0_automaton automaton) {
    parsing_table parsingTable = {};
    for (int i = 0; i < automaton.size(); i++) {
        // Stacking
        for (int symbol = nt_PARAM; symbol >= tok_id; symbol--) {
            aut_state goToState = goTo(automaton[i], symbol);
            if (goToState.size() > 0) {
                tuple<int, int> key = make_tuple(symbol, i);
                int dest = stateIndexInAutomaton(automaton, goToState);
                parsingTable.insert(make_pair(key, make_tuple((symbol < 0 ? 's' : 'g'), dest)));
            }
        }
        // Reducing
        for (item itm : automaton[i]) {
            if (get<1>(itm) == get<1>(get<0>(itm)).size() || get<1>(get<0>(itm)).size() < 1) {  // The dot is in the end of the production or is a lambda production
                // Accepting
                if (get<0>(get<0>(itm)) == nt_S) {
                    tuple<int, int> key = make_tuple(tok_id - 1, i);
                    parsingTable.insert(make_pair(key, make_tuple('a', 0)));
                    continue;
                }
                set<int> follow = FOLLOW(get<0>(get<0>(itm)));
                for (int terminal : follow) {
                    tuple<int, int> key = make_tuple(terminal, i);
                    parsingTable.insert(make_pair(key, make_tuple('r', getRuleNumber(get<0>(itm)))));
                }
            }
        }
    }
    return parsingTable;
}

lr0_automaton getAutomaton() {
    lr0_automaton aut = {};
    S s = S();
    parser_rule startingRule = s.getParserRule();
    item startingItem = make_tuple(startingRule, 0);
    aut_state state0 = closure(startingItem);
    aut.push_back(state0);
    for (int i = 0; i < aut.size(); i++) {
        for (int sym = nt_PARAM; sym >= tok_id; sym--) {
            aut_state newState = goTo(aut[i], sym);
            if (newState.size() > 0 && !doesAutomatonHasState(aut, newState)) {
                aut.push_back(newState);
            }
        }
    }
    return aut;
}

set<parser_rule> getNonTerminalRules(int nonTerminal) {
    switch (nonTerminal) {
        case nt_S: {
            S s = S();
            return {s.getParserRule()};
        }
        case nt_CODE: {
            LambdaCode lc = LambdaCode();
            AtribCode ac = AtribCode();
            CondCode cc = CondCode();
            RepCode rc = RepCode();
            CallCode clc = CallCode();
            return {lc.getParserRule(), ac.getParserRule(), cc.getParserRule(), rc.getParserRule(), clc.getParserRule()};
        }
        case nt_ATRIB: {
            Atrib a = Atrib();
            return {a.getParserRule()};
        }
        case nt_EXPRESSION: {
            NumberExpression ne = NumberExpression();
            IdExpression ie = IdExpression();
            ParenExpression pe = ParenExpression();
            return {ne.getParserRule(), ie.getParserRule(), pe.getParserRule()};
        }
        case nt_OPERATION: {
            OpOperation oo = OpOperation();
            LambdaOperation lo = LambdaOperation();
            return {oo.getParserRule(), lo.getParserRule()};
        }
        case nt_BOOL: {
            Bool b = Bool();
            return {b.getParserRule()};
        }
        case nt_BOOLOP: {
            BoBoolOp bbo = BoBoolOp();
            LambdaBoolOp lbo = LambdaBoolOp();
            return {bbo.getParserRule(), lbo.getParserRule()};
        }
        case nt_COND: {
            Cond c = Cond();
            return {c.getParserRule()};
        }
        case nt_ELSE: {
            ElElse ee = ElElse();
            LambdaElse le = LambdaElse();
            return {ee.getParserRule(), le.getParserRule()};
        }
        case nt_REP: {
            Rep r = Rep();
            return {r.getParserRule()};
        }
        case nt_CALL: {
            Call cl = Call();
            return {cl.getParserRule()};
        }
        case nt_PARAM: {
            ExprParam ep = ExprParam();
            LambdaParam lp = LambdaParam();
            return {ep.getParserRule(), lp.getParserRule()};
        }
    }
    return {};
}

aut_state closure(item initialItem, set<int> analyzedNonTerminals) {
    aut_state closureStates = {};
    closureStates.insert(initialItem);
    vector<int> production = get<1>(get<0>(initialItem));
    if (production.size() > get<1>(initialItem)) {  // Not lambda
        int symbolAfterDot = production[get<1>(initialItem)];
        if (symbolAfterDot >= 0 && analyzedNonTerminals.count(symbolAfterDot) < 1) {  // Is a non-terminal and has not been analyzed
            analyzedNonTerminals.insert(symbolAfterDot);
            set<parser_rule> parserRules = getNonTerminalRules(symbolAfterDot);
            for (parser_rule rule : parserRules) {
                item newItem = make_tuple(rule, 0);
                aut_state itemClosure = closure(newItem, analyzedNonTerminals);
                closureStates.insert(itemClosure.begin(), itemClosure.end());
            }
        }
    }
    return closureStates;
}

aut_state goTo(aut_state startState, int symbol) {
    aut_state endState = {};
    for (item itm : startState) {
        if (get<1>(get<0>(itm)).size() > get<1>(itm) && get<1>(get<0>(itm))[get<1>(itm)] == symbol) {  // If the symbol is after the dot in this item
            item nextItem = make_tuple(get<0>(itm), get<1>(itm) + 1);
            aut_state itemClosure = closure(nextItem);
            endState.insert(itemClosure.begin(), itemClosure.end());
        }
    }
    return endState;
}

bool doesAutomatonHasState(lr0_automaton automaton, aut_state stt) {
    for (aut_state s : automaton) {
        if (areStatesEqual(stt, s)) {
            return true;
        }
    }
    return false;
}

bool areStatesEqual(aut_state stt1, aut_state stt2) {
    if (stt1.size() != stt2.size()) {
        return false;
    }
    aut_state stateChecker = {};
    for (item i1 : stt1) {
        bool found = false;
        for (item i2 : stt2) {
            if (areItemsEqual(i1, i2)) {
                stateChecker.insert(i1);
                found = true;
                break;
            }
        }
        if (found) {
            found = false;
        } else {
            return false;
        }
    }
    return true;
}

bool areItemsEqual(item i1, item i2) {
    if (get<0>(get<0>(i1)) != get<0>(get<0>(i2))) {  // Comparing left side
        return false;
    }

    if (get<1>(i1) != get<1>(i2)) {  // Comparing dot position
        return false;
    }

    if (get<1>(get<0>(i1)).size() != get<1>(get<0>(i2)).size()) {  // Comparing right side size
        return false;
    }

    for (int i = 0; i < get<1>(get<0>(i1)).size(); i++) {  // Comparing right side symbols
        if (get<1>(get<0>(i1))[i] != get<1>(get<0>(i2))[i]) {
            return false;
        }
    }

    return true;
}

set<int> FOLLOW(int prod, set<int> analyzedSymbols) {
    set<int> follows = {};
    analyzedSymbols.insert(prod);
    if (prod == nt_S) {
        follows.insert(tok_id - 1);
    }
    for (int r = 0; r < 24; r++) {
        parser_rule rule = getRuleFromNumber(r);
        for (int i = 0; i < get<1>(rule).size(); i++) {
            if (get<1>(rule)[i] == prod) {
                if (i == get<1>(rule).size() - 1 || get<1>(rule).size() < 1) {  // Last symbol in production or λ
                    if (analyzedSymbols.count(get<0>(rule)) < 1) {
                        set<int> newFollow = FOLLOW(get<0>(rule), analyzedSymbols);
                        follows.insert(newFollow.begin(), newFollow.end());
                    }
                } else {
                    vector<int> nextSym = {};
                    nextSym.push_back(get<1>(rule)[i + 1]);
                    set<int> first = FIRST(nextSym);
                    follows.insert(first.begin(), first.end());
                    // If the production can produce λ, get it's follow as well
                    bool needFollow = true;
                    for (int s : nextSym) {
                        if (!hasLambdaProduction(s)) {
                            needFollow = false;
                            break;
                        }
                    }
                    if (needFollow) {
                        set<int> newFollow = FOLLOW(nextSym[nextSym.size() - 1], analyzedSymbols);
                        follows.insert(newFollow.begin(), newFollow.end());
                    }
                }
            }
        }
    }
    return follows;
}

set<int> FIRST(vector<int> prod) {
    set<int> firsts = {};
    if (prod.size() == 0) {
        return firsts;
    }
    if (prod[0] < 0) {
        firsts.insert(prod[0]);
    } else {
        for (int r = 0; r < 24; r++) {
            parser_rule rule = getRuleFromNumber(r);
            if (get<0>(rule) == prod[0]) {
                vector<int> productions = get<1>(rule);
                set<int> newFirsts = FIRST(productions);
                firsts.insert(newFirsts.begin(), newFirsts.end());
            }
        }
        if (hasLambdaProduction(prod[0])) {
            if (prod.size() > 1) {
                vector<int> nextSym(prod.begin() + 1, prod.end());
                set<int> newFirsts = FIRST(nextSym);
                firsts.insert(newFirsts.begin(), newFirsts.end());
            }
        }
    }
    return firsts;
}

bool hasLambdaProduction(int symbol) {
    if (symbol < 0) {
        return false;
    }

    for (int r = 0; r < 24; r++) {
        parser_rule rule = getRuleFromNumber(r);
        if (get<0>(rule) == symbol) {
            if (get<1>(rule).size() < 1) {
                return true;
            }
        }
    }
    return false;
}

int stateIndexInAutomaton(lr0_automaton automaton, aut_state stt) {
    for (int i = 0; i < automaton.size(); i++) {
        if (areStatesEqual(stt, automaton[i])) {
            return i;
        }
    }
    return -1;
}
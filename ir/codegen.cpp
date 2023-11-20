#include "../parser/parser-classes.h"
#include "env.h"

Value* S::codegen() {
    return code->codegen();
}

Value* AtribCode::codegen() {
    Value* atribGen = atrib->codegen();
    Value* codeGen = code->codegen();
    return atribGen;
}

Value* CondCode::codegen() {
    Value* condGen = cond->codegen();
    Value* codeGen = code->codegen();
    return condGen;
}

Value* RepCode::codegen() {
    Value* repGen = rep->codegen();
    Value* codeGen = code->codegen();
    return repGen;
}

Value* CallCode::codegen() {
    Value* callGen = call->codegen();
    Value* codeGen = code->codegen();
    return callGen;
}

Value* Atrib::codegen() {
    Value* varValue = expr->codegen();
    Type* varType = varValue->getType();

    AllocaInst* varAlloc;
    Value* lookup = CurrentEnv->lookup(id);
    bool varExists = (lookup != nullptr);

    if (varExists) {
        varAlloc = dyn_cast<AllocaInst>(lookup);
    } else {
        varAlloc = Builder->CreateAlloca(varType, varValue, id);
        CurrentEnv->define(id, varAlloc);
    }

    Builder->CreateStore(varValue, varAlloc);

    return varValue;
}

Value* NumberExpression::codegen() {
    ConstantInt* lhs = Builder->getInt32(number);

    Value* rhs = op->codegen();
    if (rhs == nullptr) {
        return lhs;
    }

    string operatorStr = op->op;
    if (operatorStr == "+") {
        return Builder->CreateAdd(lhs, rhs);
    } else if (operatorStr == "-") {
        return Builder->CreateSub(lhs, rhs);
    } else if (operatorStr == "*") {
        return Builder->CreateMul(lhs, rhs);
    } else if (operatorStr == "/") {
        return Builder->CreateSDiv(lhs, rhs);
    } else if (operatorStr == "%") {
        return Builder->CreateSRem(lhs, rhs);
    } else {
        cerr << "Unknown operator " << operatorStr << "\n";
        return nullptr;
    }
}

Value* IdExpression::codegen() {
    Value* lookup = CurrentEnv->lookup(id);
    bool varExists = (lookup != nullptr);
    if (!varExists) {
        cerr << "Variable " << id << " not found in current scope!\n";
        return nullptr;
    }
    AllocaInst* varAlloc = dyn_cast<AllocaInst>(lookup);
    Value* lhs = Builder->CreateLoad(varAlloc->getAllocatedType(), varAlloc, id);

    Value* rhs = op->codegen();
    if (rhs == nullptr) {
        return lhs;
    }

    string operatorStr = op->op;
    if (operatorStr == "+") {
        return Builder->CreateAdd(lhs, rhs);
    } else if (operatorStr == "-") {
        return Builder->CreateSub(lhs, rhs);
    } else if (operatorStr == "*") {
        return Builder->CreateMul(lhs, rhs);
    } else if (operatorStr == "/") {
        return Builder->CreateSDiv(lhs, rhs);
    } else if (operatorStr == "%") {
        return Builder->CreateSRem(lhs, rhs);
    } else {
        cerr << "Unknown operator " << operatorStr << "\n";
        return nullptr;
    }
}

Value* ParenExpression::codegen() {
    Value* lhs = expr->codegen();

    Value* rhs = op->codegen();
    if (rhs == nullptr) {
        return lhs;
    }

    string operatorStr = op->op;
    if (operatorStr == "+") {
        return Builder->CreateAdd(lhs, rhs);
    } else if (operatorStr == "-") {
        return Builder->CreateSub(lhs, rhs);
    } else if (operatorStr == "*") {
        return Builder->CreateMul(lhs, rhs);
    } else if (operatorStr == "/") {
        return Builder->CreateSDiv(lhs, rhs);
    } else if (operatorStr == "%") {
        return Builder->CreateSRem(lhs, rhs);
    } else {
        cerr << "Unknown operator " << operatorStr << "\n";
        return nullptr;
    }
}

Value* OpOperation::codegen() {
    return expr->codegen();
}

Value* Bool::codegen() {
    Value* lhs = expr1->codegen();
    Value* rhs = expr2->codegen();

    Value* boolValue;

    string compareStr = compare;
    if (compareStr == "<") {
        boolValue = Builder->CreateICmpSLT(lhs, rhs);
    } else if (compareStr == "<=") {
        boolValue = Builder->CreateICmpSLE(lhs, rhs);
    } else if (compareStr == "==") {
        boolValue = Builder->CreateICmpEQ(lhs, rhs);
    } else if (compareStr == "=!") {
        boolValue = Builder->CreateICmpNE(lhs, rhs);
    } else if (compareStr == ">=") {
        boolValue = Builder->CreateICmpSGE(lhs, rhs);
    } else if (compareStr == ">") {
        boolValue = Builder->CreateICmpSGT(lhs, rhs);
    } else {
        cerr << "Unknown comparison operator " << compareStr << "\n";
        return nullptr;
    }

    Value* oBool = boolop->codegen();
    if (oBool == nullptr) {
        return boolValue;
    }

    string boolOp = boolop->boolean;
    if (boolOp == "&") {
        return Builder->CreateAnd(boolValue, oBool);
    } else if (boolOp == "|") {
        return Builder->CreateOr(boolValue, oBool);
    } else {
        cerr << "Unknown boolean operator " << boolOp << "\n";
        return nullptr;
    }
}

Value* BoBoolOp::codegen() {
    return boolptr->codegen();
}

Value* Cond::codegen() {
    Value* conditionalValue = boolptr->codegen();
    bool hasElse = elseptr->hasElse;

    Function* fn = TheModule->getFunction("main");
    BasicBlock* thenBasicBlock = BasicBlock::Create(*TheContext, "then", fn);
    BasicBlock* ifEndBasicBlock = BasicBlock::Create(*TheContext, "ifEnd", fn);

    if (hasElse) {
        BasicBlock* elseBasicBlock = BasicBlock::Create(*TheContext, "else", fn);
        Builder->CreateCondBr(conditionalValue, thenBasicBlock, elseBasicBlock);

        Builder->SetInsertPoint(thenBasicBlock);
        CurrentEnv = CurrentEnv->generateChild();
        Value* thenValue = code->codegen();
        CurrentEnv = CurrentEnv->getParent();
        Builder->CreateBr(ifEndBasicBlock);

        Builder->SetInsertPoint(elseBasicBlock);
        CurrentEnv = CurrentEnv->generateChild();
        Value* elseValue = elseptr->codegen();
        CurrentEnv = CurrentEnv->getParent();
    } else {
        Builder->CreateCondBr(conditionalValue, thenBasicBlock, ifEndBasicBlock);

        Builder->SetInsertPoint(thenBasicBlock);
        CurrentEnv = CurrentEnv->generateChild();
        Value* thenValue = code->codegen();
        CurrentEnv = CurrentEnv->getParent();
    }

    Builder->CreateBr(ifEndBasicBlock);
    Builder->SetInsertPoint(ifEndBasicBlock);

    return nullptr;
}

Value* ElElse::codegen() {
    return code->codegen();
}

Value* Rep::codegen() {

    Function* fn = TheModule->getFunction("main");
    BasicBlock* conditionBasicBlock = BasicBlock::Create(*TheContext, "condition", fn);
    BasicBlock* whileBasicBlock = BasicBlock::Create(*TheContext, "while", fn);
    BasicBlock* endWhileBasicBlock = BasicBlock::Create(*TheContext, "endWhile", fn);
    
    Builder->CreateBr(conditionBasicBlock);
    Builder->SetInsertPoint(conditionBasicBlock);
    Value* conditionValue = boolptr->codegen();
    Builder->CreateCondBr(conditionValue, whileBasicBlock, endWhileBasicBlock);

    Builder->SetInsertPoint(whileBasicBlock);
    CurrentEnv = CurrentEnv->generateChild();
    Value* whileValue = code->codegen();
    CurrentEnv = CurrentEnv->getParent();
    Builder->CreateBr(conditionBasicBlock);

    Builder->SetInsertPoint(endWhileBasicBlock);

    return nullptr;
}

Value* Call::codegen() {
    FunctionCallee fnCall;
    Value* arg = param->codegen();
    if (id == "show") {
        vector<Value*> argsAr = {};
        if (arg) {
            static Value* pdStr = nullptr;
            if (pdStr == nullptr) {
                pdStr = Builder->CreateGlobalStringPtr("%d\n");
            }
            argsAr = {pdStr, move(arg)};
        } else {
            static Value* nStr = nullptr;
            if (nStr == nullptr) {
                nStr = Builder->CreateGlobalStringPtr("\n");
            }
            argsAr = {nStr, Builder->getInt32(0)};
        }
        fnCall = TheModule->getFunction("printf");
        return Builder->CreateCall(fnCall, argsAr);
    } else {
        cout << "SHIT! THE FUNCTION CALL IS WRONG!\n";
    }
    return Builder->CreateCall(fnCall, arg);
}

Value* ExprParam::codegen() {
    return expr->codegen();
}
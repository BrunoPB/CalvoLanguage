#include "ir.h"

void compileToIR(shared_ptr<S> AST) {
    setupPrintfFunction();
    Function* mainFn = declareMainFunction();
    setEntryBlock(mainFn);
    AST->codegen();
    endMain();
}

void setupPrintfFunction() {
    string pn = "printf";
    Type* retType = Builder->getVoidTy();
    vector<Type*> argTypes = {Builder->getInt8Ty()->getPointerTo(), Builder->getInt32Ty()};
    FunctionType* fnTypes = FunctionType::get(retType, argTypes, true);
    TheModule->getOrInsertFunction(pn, fnTypes);
}

Function* declareMainFunction() {
    string fnName = "main";
    FunctionType* fnType = move(FunctionType::get(Builder->getInt32Ty(), false));
    Function* fn = Function::Create(fnType, Function::ExternalLinkage, fnName, *TheModule);
    GlobalEnv->define(fnName, fn);
    return fn;
}

void setEntryBlock(Function* fn) {
    string bName = "entry";
    BasicBlock* entry = BasicBlock::Create(*TheContext, bName, fn);
    Builder->SetInsertPoint(entry);
}

void endMain() {
    ConstantInt* ret = Builder->getInt32(0);
    Builder->CreateRet(ret);
}

void saveModuleToFile(const std::string& fileName) {
    std::error_code errorCode;  // If error
    llvm::raw_fd_ostream outLL(fileName, errorCode);
    TheModule->print(outLL, nullptr);
}
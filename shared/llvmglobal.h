#ifndef LLVMGLOBAL_H
#define LLVMGLOBAL_H

#include <memory>

#include "../ir/env.h"
#include "llvmincludes.h"

static std::unique_ptr<llvm::LLVMContext> TheContext = std::make_unique<llvm::LLVMContext>();                 // LLVM global context. Owns and manages the core global data os LLVM
static std::unique_ptr<llvm::Module> TheModule = std::make_unique<llvm::Module>("CalvoModule", *TheContext);  // Type of object that can be built into the LLVM context
static std::unique_ptr<llvm::IRBuilder<>> Builder = std::make_unique<llvm::IRBuilder<>>(*TheContext);         // Builder used to build the LLVM context

static std::shared_ptr<Environment> GlobalEnv = move(make_shared<Environment>(Environment({}, nullptr)));  // Global Environment object
static std::shared_ptr<Environment> CurrentEnv = GlobalEnv;                                                // Object that represents the current environment

#endif
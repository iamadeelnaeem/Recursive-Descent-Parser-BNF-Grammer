// staticSemantics.h
#ifndef STATICSEMANTICS_H
#define STATICSEMANTICS_H

#include "symbolTable.h"
#include "parser.h"

void insertVariable(SymbolTable* st, const char* variable);
void verifyVariable(SymbolTable* st, const char* variable);
void staticSemantics(TreeNode* root);

#endif

// symbolTable.h
#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <stdbool.h>

// Define your symbol table structure
typedef struct SymbolTableNode {
    char variable[256];  // Adjust the size as needed
    struct SymbolTableNode* next;
} SymbolTableNode;

typedef struct {
    SymbolTableNode* head;
} SymbolTable;

// Function declarations
bool insert(SymbolTable* st, const char* variable);
bool verify(SymbolTable* st, const char* variable);

#endif

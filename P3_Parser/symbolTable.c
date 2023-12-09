// symbolTable.c
#include "symbolTable.h"
#include <stdlib.h>
#include <string.h>

bool insert(SymbolTable* st, const char* variable) {
    // Implement your insert logic here
    // Return true if successful, false if the variable already exists
    SymbolTableNode* node = malloc(sizeof(SymbolTableNode));
    if (!node) {
        // handle memory allocation failure
        return false;
    }
    strncpy(node->variable, variable, sizeof(node->variable) - 1);
    node->variable[sizeof(node->variable) - 1] = '\0';  // Ensure null-termination
    node->next = st->head;
    st->head = node;
    return true;
}


bool verify(SymbolTable* st, const char* variable) {
    // Implement your verify logic here
    // Return true if the variable exists, false otherwise
    SymbolTableNode* current = st->head;
    while (current) {
        if (strcmp(current->variable, variable) == 0) {
            return true;  // Variable found
        }
        current = current->next;
    }
    return false;  // Variable not found
}

// staticSemantics.c
#include "staticSemantics.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>  // Include this for strcmp

SymbolTable stv;  // Global Symbol Table for Variables

void insertVariable(SymbolTable* st, const char* variable) {
    // Insert the variable into the symbol table
    if (!insert(st, variable)) {
        fprintf(stderr, "ERROR: Variable %s already defined\n", variable);
        exit(1);
    }
}

void verifyVariable(SymbolTable* st, const char* variable) {
    // Verify if the variable is defined
    if (!verify(st, variable)) {
        fprintf(stderr, "ERROR: Variable %s used before definition\n", variable);
        exit(1);
    }
}

void collectDefinitions(TreeNode* node);
void verifyVariableUses(TreeNode* node);

void staticSemantics(TreeNode* root) {
    // Traverse the tree to collect definitions
    collectDefinitions(root);

    // Traverse again to verify variable uses
    verifyVariableUses(root);
}

void collectDefinitions(TreeNode* node) {
    if (node) {
        if (node->token.tokenID == KEYWORDStk && strcmp(node->token.instance, "let") == 0) {
            // Found a variable definition, insert into symbol table
            insertVariable(&stv, node->left->token.instance);
        }

        // Recursively traverse the left and right subtrees
        collectDefinitions(node->left);
        collectDefinitions(node->right);
    }
}

void verifyVariableUses(TreeNode* node) {
    if (node) {
        if (node->token.tokenID == IDENTIFIERtk) {
            // Found a variable use, verify in the symbol table
            verifyVariable(&stv, node->token.instance);
        }

        // Recursively traverse the left and right subtrees
        verifyVariableUses(node->left);
        verifyVariableUses(node->right);
    }
}

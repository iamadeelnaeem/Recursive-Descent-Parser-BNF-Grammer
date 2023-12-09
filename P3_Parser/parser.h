#ifndef PARSER_H
#define PARSER_H

#include "scanner.h"
#include "token.h"
#include "testTree.h"

typedef struct TreeNode
{
    Token token;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

extern TreeNode *root;

void insertNode(TreeNode **root, const char *key);
void getToken();
void parser();
void program();
void vars();
void varList();
void varListPrime();
void expStat();
void M();
void MPrime();
void N();
void NPrime();
void R();
void stats();
void mStat();
void stat();
void block();
void in();
void out();
void ifStat();
void loop();
void assign();
void RO();
void expStatPrime();

#endif
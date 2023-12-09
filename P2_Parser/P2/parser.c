#include "parser.h"
#include "testTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Functions
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

TreeNode *root = NULL;

// insert token to Node
void insertNode(TreeNode **root, const char *key)
{
    TreeNode *parent, *current, *new;

    current = *root;
    parent = NULL;

    while (current != NULL)
    {
        parent = current;
        if (strcmp(key, current->token.instance) < 0)
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }

    new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL)
    {
        printf("Memory allocation error\n");
        exit(1);
    }

    strcpy(new->token.instance, key);
    new->left = new->right = NULL;

    if (parent != NULL)
    {
        if (strcmp(key, parent->token.instance) < 0)
        {
            parent->left = new;
        }
        else
        {
            parent->right = new;
        }
    }
    else
    {
        *root = new;
    }
}

Token token;

void getToken()
{
    token = scanner();
    printf("Line: %d, Instance: %s\n", token.line, token.instance);

    if (token.tokenID == EOFtk)
    {
        printTree(root);
        exit(1);
    }
    if (strcmp(token.instance, "main") == 0 || strcmp(token.instance, "let") == 0)
    {
        program();
    }
    if (token.tokenID == COMMENTtk)
    {
        insertNode(&root, token.instance);
        getToken();
    }
    if (strcmp(token.instance, "") == 0)
    {
        getToken();
    }
}

void error()
{
    printf("Syntax Error\n");
    exit(1);
}

// initial auxiliary parser function
void parser()
{
    getToken();
}

// First(<program>) = {<vars>, main}
void program()
{
    if (strcmp(token.instance, "main") == 0)
    {
        insertNode(&root, token.instance);
        stats();
        getToken();
        if (strcmp(token.instance, "end") == 0)
        {
            insertNode(&root, token.instance);
            getToken();
        }
        else
        {
            error();
        }
    }
    else if (strcmp(token.instance, "let") == 0)
    {
        vars();
    }
    else
    {
        error();
    }
}

// First(<vars>) = {empty, let}
void vars()
{
    if (strcmp(token.instance, "let") == 0)
    {
        insertNode(&root, token.instance);
        varList();
        if (strcmp(token.instance, ".") == 0)
        {
            insertNode(&root, token.instance);
        }
        else
        {
            error();
        }
    }
    else if (strcmp(token.instance, "") == 0)
    {
    }
    else
    {
        error();
    }
}

/* Left factorization
<varList> -> id = integer <varListPrime>
<varListPrime> -> empty | <varList>*/

// First(<varList>) = {id}
void varList()
{
    getToken();

    if (token.tokenID == IDENTIFIERtk)
    {
        insertNode(&root, token.instance);
        getToken();

        if (strcmp(token.instance, "=") == 0)
        {
            insertNode(&root, token.instance);
            getToken();

            if (token.tokenID == INTEGERtk)
            {
                insertNode(&root, token.instance);
                varListPrime();
                getToken();
            }
            else
            {
                error();
            }
        }
        else
        {
            error();
        }
    }
    else
    {
        error();
    }
}

// First(<varListPrime>) = {empty, id}
void varListPrime()
{
    getToken();

    if (token.tokenID == IDENTIFIERtk)
    {
        insertNode(&root, token.instance);
        getToken();

        if (strcmp(token.instance, "=") == 0)
        {
            insertNode(&root, token.instance);
            getToken();

            if (token.tokenID == INTEGERtk)
            {
                insertNode(&root, token.instance);
                varListPrime();
            }
            else
            {
                error();
            }
        }
        else
        {
            error();
        }
    }
    else if (strcmp(token.instance, "") != 0)
    {
    }
    else
    {
        error();
    }
}

// First(<expStat>) = { [, id, integer, - }
void expStat()
{
    if ((strcmp(token.instance, "[") == 0) || token.tokenID == IDENTIFIERtk || token.tokenID == INTEGERtk || (strcmp(token.instance, "-") == 0))
    {
        M();
        if ((strcmp(token.instance, "+") == 0) || (strcmp(token.instance, "-") == 0))
        {
            getToken();
            insertNode(&root, token.instance);
            expStatPrime();
        }
    }
    else
    {
        error();
    }
}

void expStatPrime()
{
    expStat();
}

/* Left factorization
<M> -> <N> <MPrime>
<MPrime> -> * <M> | empty */

// First(<M>) = { [, id, integer, - }
void M()
{
    N();
    if (strcmp(token.instance, "*") == 0)
    {
        MPrime();
    }
}

// First(<MPrime>) = { *, empty }
void MPrime()
{
    if (strcmp(token.instance, "*") == 0)
    {
        insertNode(&root, token.instance);
        getToken();
        M();
    }
    else if (strcmp(token.instance, "") == 0)
    {
    }
    else
    {
        error();
    }
}

/* Left factorization
<N> -> <R> <NPrime> | - <N>
<NPrime> -> / <N> | empty */

// First(<N>) = { -, [, id, integer }
void N()
{
    if (strcmp(token.instance, "-") == 0)
    {
        insertNode(&root, token.instance);
        getToken();
        N();
    }
    else if ((strcmp(token.instance, "[") == 0) || token.tokenID == IDENTIFIERtk || token.tokenID == INTEGERtk)
    {
        R();
        NPrime();
    }
    else
    {
        error();
    }
}

// First(<NPrime>) = { /, empty }
void NPrime()
{
    getToken();
    if ((strcmp(token.instance, "/") == 0))
    {
        insertNode(&root, token.instance);
        getToken();
        N();
    }
}

// First(<R>) = { [, id, integer }
void R()
{
    if ((strcmp(token.instance, "[") == 0))
    {
        insertNode(&root, token.instance);
        expStat();
        getToken();
        if ((strcmp(token.instance, "]") == 0))
        {
            insertNode(&root, token.instance);
        }
        else
        {
            error();
        }
    }
    else if (token.tokenID == IDENTIFIERtk)
    {
        insertNode(&root, token.instance);
    }
    else if (token.tokenID == INTEGERtk)
    {
        insertNode(&root, token.instance);
    }
    else
    {
        error();
    }
}

// First(<stats>) = { scan, print, start, cond, loop, id }
void stats()
{
    getToken();
    if (strcmp(token.instance, "scan") == 0)
    {
        stat();
        mStat();
    }
    else if (strcmp(token.instance, "print") == 0)
    {
        stat();
        mStat();
    }
    else if (strcmp(token.instance, "start") == 0)
    {
        stat();
        mStat();
    }
    else if (strcmp(token.instance, "cond") == 0)
    {
        stat();
        mStat();
    }
    else if (strcmp(token.instance, "loop") == 0)
    {
        stat();
        mStat();
    }
    else if (strcmp(token.instance, "id") == 0)
    {
        stat();
        mStat();
    }
    else
    {
        error();
    }
}

// First(<mStat>) = { empty, scan, print, start, cond, loop, id }
void mStat()
{
    getToken();
    if (strcmp(token.instance, "scan") == 0)
    {
        in();
        mStat();
    }
    else if (strcmp(token.instance, "print") == 0)
    {
        out();
        mStat();
    }
    else if (strcmp(token.instance, "start") == 0)
    {
        block();
        mStat();
    }
    else if (strcmp(token.instance, "cond") == 0)
    {
        ifStat();
        mStat();
    }
    else if (strcmp(token.instance, "loop") == 0)
    {
        loop();
        mStat();
    }
    else if (strcmp(token.instance, "id") == 0)
    {
        assign();
        mStat();
    }
}

// First(<stat>) = { scan, print, start, cond, loop, id }
void stat()
{

    if (strcmp(token.instance, "scan") == 0)
    {
        in();
    }
    else if (strcmp(token.instance, "print") == 0)
    {
        out();
    }
    else if (strcmp(token.instance, "start") == 0)
    {
        block();
    }
    else if (strcmp(token.instance, "cond") == 0)
    {
        ifStat();
    }
    else if (strcmp(token.instance, "loop") == 0)
    {
        loop();
    }
    else if (strcmp(token.instance, "id") == 0)
    {
        assign();
    }
    else
    {
        error();
    }
}

// First(<block>) = { start }
void block()
{
    getToken();

    if (strcmp(token.instance, "start") == 0)
    {
        insertNode(&root, token.instance);
        vars();
        stats();
        getToken();
        if (strcmp(token.instance, "stop") == 0)
        {
            insertNode(&root, token.instance);
        }
        else
        {
            error();
        }
    }
    else
    {
        error();
    }
}

// First(<in>) = { scan }
void in()
{
    getToken();
    if (strcmp(token.instance, "scan") == 0)
    {
        insertNode(&root, token.instance);
        getToken();
        if (token.tokenID == IDENTIFIERtk)
        {
            insertNode(&root, token.instance);
            getToken();
            if (strcmp(token.instance, ".") == 0)
            {
                insertNode(&root, token.instance);
            }
            else
            {
                error();
            }
        }
        else
        {
            error();
        }
    }
}

// First(<out>) = { print }
void out()
{
    if (strcmp(token.instance, "print") == 0)
    {
        insertNode(&root, token.instance);
        getToken();
        expStat();
        if (strcmp(token.instance, ".") == 0)
        {
            insertNode(&root, token.instance);
        }
        else
        {
            error();
        }
    }
    else
    {
        error();
    }
}

// First(<if>) = { cond }
void ifStat()
{

    if (strcmp(token.instance, "cond") == 0)
    {
        insertNode(&root, token.instance);
        getToken();
        if (strcmp(token.instance, "(") == 0)
        {
            insertNode(&root, token.instance);
            getToken();
            expStat();
            RO();
            getToken();
            expStat();
            // getToken();
            if (strcmp(token.instance, ")") == 0)
            {
                insertNode(&root, token.instance);
                getToken();
                stat();
            }
            else
            {
                error();
            }
        }
        else
        {
            error();
        }
    }
    else
    {
        error();
    }
}

// First(<loop>) = { loop }
void loop()
{
    getToken();
    if (strcmp(token.instance, "loop") == 0)
    {
        insertNode(&root, token.instance);
        getToken();
        if (strcmp(token.instance, "(") == 0)
        {
            insertNode(&root, token.instance);
            expStat();
            RO();
            expStat();
            getToken();
            if (strcmp(token.instance, ")") == 0)
            {
                insertNode(&root, token.instance);
                stat();
            }
            else
            {
                error();
            }
        }
        else
        {
            error();
        }
    }
    else
    {
        error();
    }
}

// First(<assign>) = { id }
void assign()
{
    getToken();

    if (token.tokenID == IDENTIFIERtk)
    {
        insertNode(&root, token.instance);
        getToken();
        if (strcmp(token.instance, "~") == 0)
        {
            insertNode(&root, token.instance);
            expStat();
            getToken();
            if (strcmp(token.instance, ".") == 0)
            {
                insertNode(&root, token.instance);
            }
            else
            {
                error();
            }
        }
        else
        {
            error();
        }
    }
    else
    {
        error();
    }
}

// First(RO) = {<=, >=, <, >, =, ~}
void RO()
{
    if (token.tokenID == OPERATORStk)
    {
        if (strcmp(token.instance, "<=") == 0)
        {
            insertNode(&root, token.instance);
        }
        else if (strcmp(token.instance, ">=") == 0)
        {
            insertNode(&root, token.instance);
        }
        else if (strcmp(token.instance, "<") == 0)
        {
            insertNode(&root, token.instance);
        }
        else if (strcmp(token.instance, ">") == 0)
        {
            insertNode(&root, token.instance);
        }
        else if (strcmp(token.instance, "=") == 0)
        {
            insertNode(&root, token.instance);
        }
        else if (strcmp(token.instance, "~") == 0)
        {
            insertNode(&root, token.instance);
        }
        else
        {
            error();
        }
    }
    else
    {
        error();
    }
}

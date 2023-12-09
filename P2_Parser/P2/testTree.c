#include "testTree.h"
#include <stdio.h>
#include <stdlib.h>

void printTree(TreeNode *root)
{
    if (root)
    {
        printf("%s\n", root->token.instance);
        printTree(root->left);
        printTree(root->right);
    }
}
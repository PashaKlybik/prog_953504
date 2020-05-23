#include <stdlib.h>

#include "Tree.h"


Tree* CreateTree()
{
    Tree* tmp = (Tree*)malloc(sizeof(Tree));
    tmp->size = 0;
    tmp->pos = 0;
    tmp->root = NULL;

    return tmp;
}


void PushTreeNode(TreeNode* root, int key)
{
    while (true)
    {
        if (key > root->key)
        {
            if (root->right != NULL)
                root = root->right;

            else
            {
                TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
                newNode->left = NULL;
                newNode->right = NULL;
                newNode->key = key;

                root->right = newNode;

                break;
            }
        }

        else if (key < root->key)
        {
            if (root->left != NULL)
                root = root->left;

            else
            {
                TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
                newNode->left = NULL;
                newNode->right = NULL;
                newNode->key = key;

                root->left = newNode;

                break;
            }
        }
    }
}

void DeleteTree(TreeNode* leaf)
{
    if (leaf != nullptr)
    {
        DeleteTree(leaf->left);
        DeleteTree(leaf->right);
        free(leaf);
    }
}
#pragma once

#include <stdbool.h>
#include "TreeNode.h"

typedef struct {
	struct TreeNode* root;
} Tree;

Tree* initTree();
Tree* addTreeNode(Tree* tree, char word[32]);
Tree* addTreeNodeObject(Tree* tree, struct TreeNode* node);
struct TreeNode* findByWord(Tree* tree, struct TreeNode* curr, char word[32]);
void printRightRootLeft(struct TreeNode* curr);
Tree* deleteTreeNode(Tree* tree, struct TreeNode* deletable);
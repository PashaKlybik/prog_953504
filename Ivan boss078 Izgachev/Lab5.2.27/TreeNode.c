#include "TreeNode.h"

struct TreeNode* initTreeNode() {
	struct TreeNode* newTreeNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
	strcpy(newTreeNode->word, "");
	newTreeNode->parent = 0;
	newTreeNode->right = 0;
	newTreeNode->left = 0;
	newTreeNode->amount = 0;
	return newTreeNode;
}
#define _CRT_SECURE_NO_WARNINGS
#pragma once

#include <string.h>

struct TreeNode {
	char word[32];
	unsigned int amount;
	struct TreeNode* parent;
	struct TreeNode* left;
	struct TreeNode* right;
};

struct TreeNode* initTreeNode();
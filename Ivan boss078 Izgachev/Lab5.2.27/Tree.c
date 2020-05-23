#include "Tree.h"

Tree* initTree() {
	Tree* newTree = (Tree*)malloc(sizeof(Tree));
	newTree->root = 0;
	return newTree;
}

Tree* addTreeNode(Tree* tree, char word[32]) {
	if (tree->root == 0) {
		struct TreeNode* newNode = initTreeNode();
		strcpy(newNode->word, word);
		newNode->amount = 1;
		tree->root = newNode;
		return tree;
	}
	else {
		struct TreeNode* found = findByWord(tree, tree->root, word);
		if (found != 0) {
			struct TreeNode* updatedNode = initTreeNode();
			updatedNode->amount = ++found->amount;
			strcpy(updatedNode->word, found->word);
			tree = deleteTreeNode(tree, found);
			tree = addTreeNodeObject(tree, updatedNode);
			return tree;
		}
		struct TreeNode* newNode = initTreeNode();
		newNode->amount = 1;
		strcpy(newNode->word, word);
		tree = addTreeNodeObject(tree, newNode);
		return tree;
	}
}

Tree* deleteTreeNode(Tree* tree, struct TreeNode* deletable) {
	if (tree->root == deletable) {
		if (deletable->right == 0 && deletable->left == 0) {
			free(deletable);
			tree->root = 0;
			return tree;
		}
		if (deletable->right == 0) {
			tree->root = deletable->left;
			tree->root->parent = 0;
			free(deletable);
			return tree;
		}
		if (deletable->left == 0) {
			tree->root = deletable->right;
			tree->root->parent = 0;
			free(deletable);
			return tree;
		}
		struct TreeNode* curr = deletable->left;
		while (curr->right != 0)
		{
			curr = curr->right;
		}
		deletable->amount = curr->amount;
		strcpy(deletable->word, curr->word);
		tree = deleteTreeNode(tree, curr);
		return tree;
	}
	struct TreeNode* parent = deletable->parent;
	if (deletable->left == 0 && deletable->right == 0) {
		if (parent->left == deletable)
			parent->left = 0;
		else
			parent->right = 0;
		free(deletable);
		return tree;
	}
	if (deletable->left == 0) {
		if (parent->left == deletable) {;
			parent->left = deletable->right;
			deletable->right->parent = parent;
		}
		else {
			parent->right = deletable->right;
			deletable->right->parent = parent;
		}
		free(deletable);
		return tree;
	}
	if (deletable->right == 0) {
		if (parent->left == deletable) {
			parent->left = deletable->left;
			deletable->left->parent = parent;
		}
		else {
			parent->right = deletable->left;
			deletable->left->parent = parent;
		}
		free(deletable);
		return tree;
	}
	struct TreeNode* curr = deletable->left;
	while (curr->right != 0)
	{
		curr = curr->right;
	}
	deletable->amount = curr->amount;
	strcpy(deletable->word, curr->word);
	tree = deleteTreeNode(tree, curr);
	return tree;
}

struct TreeNode* findByWord(Tree* tree, struct TreeNode* curr, char word[32]) {
	if (curr == 0)
		return 0;
	if (!strcmp(curr->word, word))
		return curr;
	struct TreeNode* leftResult = findByWord(tree, curr->left, word);
	struct TreeNode* rightResult = findByWord(tree, curr->right, word);
	if (leftResult == 0 && rightResult == 0)
		return 0;
	if (leftResult != 0)
		return leftResult;
	else
		return rightResult;
}

Tree* addTreeNodeObject(Tree* tree, struct TreeNode* node) {
	struct TreeNode* curr = tree->root;
	if (curr == 0) {
		curr = node;
		return tree;
	}
	while (true) {
		if (node->amount < curr->amount) {
			if (curr->left == 0) {
				curr->left = node;
				node->parent = curr;
				return tree;
			}
			curr = curr->left;
		}
		else {
			if (curr->right == 0) {
				curr->right = node;
				node->parent = curr;
				return tree;
			}
			curr = curr->right;
		}
	}
}

void printRightRootLeft(struct TreeNode* curr) {
	if (curr == 0)
		return;
	printRightRootLeft(curr->right);
	printf("Word: '%s', amount: %d\n", curr->word, curr->amount);
	printRightRootLeft(curr->left);
}
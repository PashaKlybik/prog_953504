#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "Tree.h"

Tree* tree;

int main() {
	FILE* input = fopen("input.txt", "r");
	tree = initTree();
	if (input == NULL) {
		printf("File is not located!");
		return 0;
	}
	char buffer[8192];
	fgets(&buffer, sizeof(buffer), input);
	char curr[32];
	strcpy(curr, "");
	for (int i = 0; i < sizeof(buffer); i++) {
		char ch = buffer[i];
		if (ch == '\0') {
			if (strcmp(curr, "")) {
				addTreeNode(tree, curr);
			}
			break;
		}
		if (ch == ' ' || ch == ',' || ch == '.' || ch == '\n') {
			if (strcmp(curr, "")) {
				addTreeNode(tree, curr);
			}
			strcpy(curr, "");
			continue;
		}
		strncat(curr, &ch, 1);
	}
	printRightRootLeft(tree->root);
	return 0;
}
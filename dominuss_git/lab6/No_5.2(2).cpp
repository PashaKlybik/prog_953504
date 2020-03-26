#include <stdio.h>
#include <iostream>

struct Steck {
	int treeNumber;
	int value;

	Steck *p_prev;
	Steck *p_next;
};

struct Tree {
	int value;

	Tree *p_left;
	Tree *p_right;
};

bool At(Steck *top, int number, int treeNumber) {
	Steck *s_run = top;

	while(s_run) {
		if(s_run->value == number && s_run->treeNumber == treeNumber) {
			return false;
		}
		s_run = s_run->p_next;
	}
	return true;
}

void push_back(Steck **top, int treeNumber, int number) {
	bool mode = At(*top, number, treeNumber);

	if(mode) {
		Steck *newSteck;
		newSteck = new Steck();
		Steck *back;
		back = &**top;

		if(*top == NULL) {
			newSteck->p_prev = NULL;
			newSteck->p_next = NULL;
			newSteck->value = number;
			newSteck->treeNumber = treeNumber;
			*top = newSteck;
		} else {
			back->p_prev = newSteck;
			newSteck->p_next = *top;
			newSteck->p_prev = NULL;
			newSteck->value = number;
			newSteck->treeNumber = treeNumber;
			*top = newSteck;
		}
	}
}

void push_back(Tree **tree, int value) {

	Tree *branch;
	branch = new Tree();

	if(*tree == NULL) {
		branch->value = value;
		branch->p_left = NULL;
		branch->p_right = NULL;
		*tree = branch;
	} else {
		Tree *root;
		root = &**tree;
		while (root->p_left != NULL && root->p_right != NULL) {
			if (root->value < value) {
				root = root->p_right;
			} else {
				root = root->p_left;
            }
		}

		if(root->value < value) {
			branch->value = value;
			root->p_right = branch;
			branch->p_left = NULL;
			branch->p_right = NULL;
		} else {
            branch->value = value;
			root->p_left = branch;
			branch->p_left = NULL;
			branch->p_right = NULL;
        }
    }
}

void SteckInTree(Tree **tree, Steck *top, int treeNumber) {
	while (top) {
		if (top->treeNumber == treeNumber) {
			push_back(&*tree, top->value);
		}
		top = top->p_next;
	}
}

void S_Print(Steck *top) {
	Steck *p_run = top;
	while(p_run) {
		printf("Tree number : %d ; Value : %d\n", p_run->treeNumber, p_run->value);
		p_run = p_run->p_next;
    }
}

void T_Print_Bigger(Tree *tree) {
	Tree *p_run = tree;
	while(p_run->p_right != NULL) {
		p_run = p_run->p_right;
	}
	printf("The biggest value : %d\n", p_run->value);
}

int _tmain(int argc, _TCHAR* argv[])
{
	Steck *top = NULL;
	Tree *tree = NULL;
	int treeNumber;

	do {	
		while(true) {
			printf("%s", "Write number of tree and value. If you want to stop enter 0");
			int value;

			scanf("%d", &treeNumber);
			scanf("%d", &value);

			if(treeNumber == 0 || value == 0) {
				break;
			} else {
				push_back(&top, treeNumber, value);
			}
		
			system("cls");
		}

		while (true) {
			S_Print(top);
			printf("%s", "What Steck do you want imagine to tree?");
			scanf("%d", &treeNumber);			
			if(treeNumber == 0) {
				break;
			}
		
			SteckInTree(&tree, top, treeNumber);
			T_Print_Bigger(tree);

			system("pause");
			system("cls");
		}        
		printf("%s", "Exit?");
		scanf("%d", &treeNumber);
		if(!treeNumber) {
			break;
        }
	}while(true);

	system("pause");
	return 0;
}

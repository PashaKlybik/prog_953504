#include <stdio.h>
#include <stdbool.h>
typedef struct List
{
	int data;
	struct List* next;
	struct List* prev;
} List;
typedef struct TreeNode
{
	struct TreeNode* left;
	struct TreeNode* right;
	struct TreeNode* parent;
	int data;
} TreeNode;
List* InitializeElement(int data)
{
	List* list;
	list = (List*)malloc(sizeof(List));
	list->data = data;
	list->next = NULL;
	list->prev = NULL;
	return list;
}
List* AddElement(List* element, int data)
{
	if (!element)
	{
		element = InitializeElement(data);
		return element;
	}
	List* temp;
	temp = (List*)malloc(sizeof(List));
	element->next = temp;
	temp->data = data;
	temp->next = NULL;
	temp->prev = element;
	return(temp);
}
void PrintList(List* element)
{
	List* print;
	print = element;
	while (print)
	{
		printf("%d ", print->data);
		print = print->next;
	}
}
TreeNode* AddToTree(TreeNode* node, int data, TreeNode* parent)
{
	if (!node)
	{
		node = (TreeNode*)malloc(sizeof(TreeNode));
		node->data = data;
		node->left = NULL;
		node->right = NULL;
		node->parent = parent;
	}
	else if (data >= node->data)
	{
		node->right = AddToTree(node->right, data, node);
	}
	else
	{
		node->left = AddToTree(node->left, data, node);
	}
	return node;
}
void DeleteTree(TreeNode* node)
{
	if (node)
	{
		DeleteTree(node->left);
		DeleteTree(node->right);
		free(node);
	}
}
void PrintTree(TreeNode* node)
{
	if (node)
	{
		PrintTree(node->left);
		/*for (int i = 0; i < p; i++)
		{
			printf(" ");
		}*/
		printf("%d\n", node->data);
		PrintTree(node->right);
	}
}
TreeNode* GetMaxNode(TreeNode* node) 
{
	while (node->right)
	{
		node = node->right;
	}
	return node;
}
TreeNode* DeleteNode(TreeNode* node)
{
	TreeNode* temp;
	if (node->left && node->right)
	{
		temp = NULL;
		TreeNode* localMax = GetMaxNode(node->left);
		node->data = localMax->data;
		DeleteNode(localMax);
	}
	else if (!node->parent)
	{
		temp = node->right;
	}
	else if (node->left)
	{
		if (node == node->parent->left)
		{
			node->parent->left = node->left;
			temp = node->parent->left;
			temp->parent = node->parent;
		}
		else
		{
			node->parent->right = node->left;
			temp = node->parent->right;
			temp->parent = node->parent;
		}
	}
	else if (node->right)
	{
		if (node == node->parent->right)
		{
			node->parent->right = node->right;
			temp = node->parent->right;
			temp->parent = node->parent;
		}
		else
		{
			node->parent->left = node->right;
			temp = node->parent->left;
			temp->parent = node->parent;
		}
	}
	else
	{
		if (node == node->parent->left)
		{
			node->parent->left = NULL;
			temp = node->parent;
		}
		else
		{
			node->parent->right = NULL;
			temp = node->parent;
		}
	}
	free(node);
	return temp;
}
TreeNode* FindNode(TreeNode* node, int amount)
{
	static int count = 0;
	if (node)
	{
		FindNode(node->left, amount);
		FindNode(node->right, amount);
		if (node->data < 0)
		{
			node = DeleteNode(node);
		}
		count++;
	}
	if (amount == count)
	{
		return node;
	}
}
List* DeleteHead(List* root)
{
	struct List* temp;
	temp = root->next;
	temp->prev = NULL;
	free(root);
	return(temp);
}
int main()
{
	srand(time(0));
	int amount;
	TreeNode* tree = NULL;
	List* list = NULL;
	printf("Enter the amount of list elements: ");
	scanf_s("%d", &amount);
	for (int i = 0; i < amount; i++)
	{
		list = AddElement(list, rand() % 201 - 100);
	}
	while (list->prev)
	{
		list = list->prev;
	}
	printf("\nList:\n");
	PrintList(list);
	while (list->prev)
	{
		list = list->prev;
	}
	for (int i = 0; i < amount; i++)
	{
		tree = AddToTree(tree, list->data, NULL);
		if (list->next)
		{
			list = DeleteHead(list);
		}
	}
	free(list);
	list = NULL;
	printf("\nTree:\n");
	PrintTree(tree);
	tree = FindNode(tree, amount);
	printf("\nChanged Tree:\n");
	PrintTree(tree);
	DeleteTree(tree);
}
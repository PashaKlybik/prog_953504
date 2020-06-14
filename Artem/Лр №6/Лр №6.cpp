//5.2 (4). В текстовом файле записаны целые числа.Построить бинарное
//дерево поиска, в узлах которого хранятся числа из файла.
//Разработать функцию, определяющую число узлов дерева на
//каждом уровне.

//10
//20
//7
//6
//23
//21
//8
//25
//                 10
//			  7	        20
//		  6    	  8          23
//					      21     25
//1
//2
//3
//2

#include <iostream>
#include<cstdio>
using namespace std;

//ищем количество чисел
int WordAmount(char* str, int wordCount)
{
	for (int i = 0; str[i] != '\0'; i++)
	{
		if (str[i] == ' ')
			wordCount++;
	}
	return wordCount;
}

//заполняем двумерный массив словами из одномерного массива str а потом в интовый массив
int* ArrayFilling(char* str, int n, char** words, int position, int* intData)
{
	for (int i = 0; i < (n + 1); i++)
		words[i] = (char*)malloc(128 * sizeof(char));
	int j = 0, strSize = 0;
	for (int i = 0; str[i] != '\0'; i++)
	{
		if (str[i] != ' ' || '\0')
		{
			words[position][j] = str[i];
			words[position][j + 1] = '\0';
			sscanf_s(words[position], "%d", &intData[strSize]);
		}
		j++;
		if (str[i] == ' ')
		{
			position++;
			strSize++;
			j = 0;
		}

	}
	return intData;
}
struct Node
{
	int info;
	Node* left;
	Node* right;
} *tree;

void Add(int a, Node** tree)
{
	if ((*tree) == NULL) {
		(*tree) = new Node;
		(*tree)->info = a;
		(*tree)->left = (*tree)->right = NULL;
		return;
	}
	if (a > (*tree)->info) {
		Add(a, &(*tree)->right);
	}
	else {
		Add(a, &(*tree)->left);
	}
}

void Print(Node* tree)
{
	if (tree == NULL)
	{
		return;
	}
	cout << " " << tree->info << endl;
	Print(tree->left);
	Print(tree->right);
}

void Count(Node* tree, int* nodesNumber, int& level, int& size)
{
	nodesNumber[level]++;
	if (tree->left)
	{
		level++;
		Count(tree->left, nodesNumber, level, size);
	}
	if (tree->right)
	{
		level++;
		Count(tree->right, nodesNumber, level, size);
	}
	if (size < level)
		size = level;
	level--;
}

void DeleteTree(Node* tree)
{
	if (tree == NULL)
		return;
	DeleteTree(tree->left);
	DeleteTree(tree->right);

	free(tree);
}

void DeleteArr(char** words, int* intData, int* nodesNumber,  int n)
{
	for (int i = 0; i < n; i++)
	{
		free(words[i]);
	}
	free(words);
	free(intData);
	free(nodesNumber);
}

int main()
{
	int info;
	int n = 100;
	int* intData = (int*)malloc(100 * sizeof(int));
	char str[500];

	FILE* file;
	char** words = (char**)malloc((n) * sizeof(char*));

	fopen_s(&file, "text.txt", "r");
	if (!file)
	{
		cout << " Error: file not found!";
		exit(0);
	}
	fgets(str, sizeof(str), file);

	int wordCount = WordAmount(str, 1);
	ArrayFilling(str, n, words, 0, intData);

	for (int i = 0; i < wordCount; i++)
	{
		Add(intData[i], &tree);
	}

	cout << " Numbers for tree:\n";

	Print(tree);

	int level = 0;
	int size = -1;
	int* nodesNumber = (int*)calloc(50, sizeof(int)); //массив для хранения числа узлов заполняется нулями

	Count(tree, nodesNumber, level, size);

	cout << " Number of nodes at each level:\n";
	for (int i = 0; i < size + 1; i++)
		cout << " On " << i + 1 << " level: " << nodesNumber[i] << "\n";

	DeleteTree(tree);
	DeleteArr(words, intData, nodesNumber, n);
	return 0;
}
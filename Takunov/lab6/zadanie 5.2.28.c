//Designed by Pavel Takunov
#include <stdio.h>
#include <string.h>
#include <Windows.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996).

typedef struct Node
{
	struct Node* left;
	struct Node* right;
	char key;
	long count;

} Node;
void Add(Node** list, char x)
{
	if (*list == NULL)
	{
		*list = (Node*)malloc(sizeof(Node));
		(*list)->key = x;
		(*list)->count = 1;
		(*list)->left = (*list)->right = NULL;
	}
	else
	{
		if ((*list)->key == x)
			((*list)->count)++;
		else if ((*list)->key > x)
			Add(&((*list)->left), x);
		else
			Add(&((*list)->right), x);
	}
}
void ShowInfoTree(Node* list)
{
	if (list != NULL)
	{
		ShowInfoTree(list->left);
		printf("%c = %ld\n", list->key, list->count);
		ShowInfoTree(list->right);
	}
}
int LetterDefenition(char c)
{
	int CharTypeA = 0;
	if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y' ||
		c=='A'|| c == 'E' || c == 'Y' || c == 'U' || c == 'I' || c == 'O' ||
		c == 'у' || c == 'е' || c == 'ы' || c == 'а' || c == 'о' || c == 'э' || c == 'ю' || c == 'и' || c == 'я'||
		c == 'У' || c == 'Е' || c == 'Ы' || c == 'А' || c == 'О' || c == 'Э' || c == 'Ю' || c == 'И' || c == 'Я')
		CharTypeA = 1;
	else
		CharTypeA = 0;
	return CharTypeA;
}
int Amount(Node* list)
{
	int count = 0;
	if (list != NULL)
	{
		count += Amount(list->left);
		if (LetterDefenition(list->key))
			count += list->count;
		count += Amount(list->right);
	}
	return count;
}
int main()
{
	system("color 0A");
	for (;;)
	{
		//int resolution = 0;
		//
		//printf("do you want to continue&\n Yes:0 |  No:1\n");
		//scanf("%d", resolution);
		//if (resolution==1)
		//{
		//	break;
		//}
		SetConsoleCP(1251);
		SetConsoleOutputCP(1251);
		Node* base = NULL;
		char string[256];
		char* tts;
		int vowels, consonants;
		printf("Hi my dear teacher this is a tree that you cannot break, try to do it!\nEnter the string: \n");
		gets(string);
		for (tts = string; *tts; ++tts)
			Add(&base, *tts);
		printf("Tree item information\n");
		ShowInfoTree(base);
		vowels = Amount(base);
		consonants = (int)strlen(string) - Amount(base);
		printf("Number of vowels: %d\n", vowels);
		printf("Number of consonants: %d\n", consonants);
		if (vowels > consonants)
			printf("more vowels on %d\n", vowels - consonants);
		else if (vowels == consonants)
			puts("Letters equally");
		else
			printf("more consonants on %d\n", consonants - vowels);
	}
	return 666;
}



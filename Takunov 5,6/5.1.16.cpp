#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)

char* buffer = (char*)malloc(20 * sizeof(char));
int Count = 0;
int lengthOfWords = 0;

typedef struct Node
{
	char  string[20] = "";
	struct Node* Next = nullptr;
	struct Node* Prev = nullptr;
}Node;

typedef struct DoubleList
{
	int size;
	Node* Head = nullptr;
	Node* Tail = nullptr;
}DoubleList;

typedef struct StackNode
{
	DoubleList* list = nullptr;
	char string[20] = "";
	struct StackNode* Next = nullptr;
}StackNode;

typedef struct Stack
{
	StackNode* Head = nullptr;
}Stack;

DoubleList* MakeList()
{
	DoubleList* temp = (DoubleList*)malloc(sizeof(DoubleList));
	temp->size = 0;
	temp->Head = nullptr;
	temp->Tail = nullptr;
	return temp;
}

Stack* StackInIt(DoubleList* LinkedList)
{
	Stack* list = (Stack*)malloc(sizeof(Stack));
	StackNode* Node = (StackNode*)malloc(sizeof(StackNode));
	Node->list = LinkedList;
	Node->Next = nullptr;
	list->Head = Node;
	return list;
}

void LinkList(Stack* list, DoubleList* LinkedList)
{
	StackNode* temp = (StackNode*)malloc(sizeof(StackNode));
	temp->list = LinkedList;
	temp->Next = list->Head;
	list->Head = temp;
}

void AddWordToStack(Stack* list, char* value)
{
	StackNode* temp = (StackNode*)malloc(sizeof(StackNode));
	temp->Next = list->Head;
	strcpy(temp->string, value);
	list->Head = temp;
}

void ShowWords(StackNode* list)
{
	StackNode* Current = list;
	if (Current->Next != nullptr)
	{
		ShowWords(list->Next);
		printf("%d)\t%s\n", Count + 1, list->string);
		Count++;
	}
}

void ReturnLine(char* string)
{
	if (*string != '\0')
	{
		ReturnLine(string + 1);
		buffer[Count] = *string;
		Count++;
	}
}

void DoubleListInIt(DoubleList* list)
{
	Node* temp = (Node*)malloc(sizeof(Node));
	if (temp == nullptr)
		return;
	char tempstr[20];
	scanf("%s", tempstr);
	strcpy(temp->string, "");
	strcpy(temp->string, tempstr);
	temp->Next = list->Head;
	temp->Prev = nullptr;
	if (list->Head)
		list->Head->Prev = temp;
	if (list->Tail == nullptr)
		list->Tail = temp;
	list->Head = temp;
	list->size++;
}

void Sort(char** str, int length)
{
	char temp[20] = "";
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < length - i; j++)
		{
			if (str[j][0] > str[j + 1][0])
			{
				strcpy(temp, str[j]);
				strcpy(str[j], str[j + 1]);
				strcpy(str[j + 1], temp);
			}
		}
	}
}

void ShowDoubleList(DoubleList* list, char** words)
{
	Node* temp = list->Head;
	int counter = 1;
	while (temp)
	{
		printf("%d)\t", counter);
		ReturnLine(temp->string);
		for (int i = strlen(temp->string); i < 20; i++)
		{
			buffer[i] = '\0';
		}
		printf("%s", buffer);
		strcpy(words[lengthOfWords], buffer);
		strcpy(buffer, "");
		lengthOfWords++;
		printf("\n");
		Count = 0;
		temp = temp->Next;
		counter++;
	}
}

void Show(Stack* list, char** words)
{
	StackNode* Current = list->Head;
	while (Current != nullptr) {
		ShowDoubleList(Current->list, words);
		Current = Current->Next;
	}
}

int main()
{
	int length = 0;
	while (length < 1)
	{
		puts("Enter length");
		scanf("%d", &length);
	}
	char** words = (char**)malloc(length * sizeof(char*));
	for (int i = 0; i < length; i++)
		words[i] = (char*)malloc(sizeof(char) * 20);
	DoubleList** lists = (DoubleList**)malloc(sizeof(DoubleList*) * (length));
	for (int i = 0; i < length; i++) {
		lists[i] = MakeList();
		DoubleListInIt(lists[i]);
	}
	Stack* stack = StackInIt(lists[0]);
	Stack* copyofstack = StackInIt(lists[0]);
	for (int i = 1; i < length; i++)
		LinkList(stack, lists[i]);
	printf("Output info\n___________________\n");
	Show(stack, words);
	printf("All words\n");
	for (int i = 0; i < length; i++)
		printf("%d)\t%s\n", i + 1, words[i]);
	Sort(words, length);
	for (int i = 0; i < length; i++)
		AddWordToStack(copyofstack, words[i]);
	printf("Sorted words\n");
	ShowWords(copyofstack->Head);
	for (int i = 0; i < length; i++)
	{
		free(lists[i]);
	}
	free(lists);
	return 0;
}
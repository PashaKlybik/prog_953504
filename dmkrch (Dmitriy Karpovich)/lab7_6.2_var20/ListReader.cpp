#define MAX 40

#include "ListReader.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "CharFunctions.h"


void AddNewReader(ListReader* listReader)
{
	system("cls");

	while (getchar() != '\n');

	char name[MAX];
	char surname[MAX];
	int group;
	char telephone[MAX];
	char email[MAX];
	char note[MAX];

	printf("Enter name: ");
	getline(name, MAX);

	printf("Enter surname: ");
	getline(surname, MAX);

	printf("Enter group: ");
	scanf_s("%d", &group);

	while (getchar() != '\n');

	printf("Enter telephone number: ");
	getline(telephone, MAX);

	printf("Enter email: ");
	getline(email, MAX);

	printf("Enter note: ");
	getline(note, MAX);


	Reader* reader = CreateReader(surname, name, group, telephone, email, note);
	AddReader(listReader, reader);
}

ListReader* CreateListReader()
{
	ListReader* temp = (ListReader*)malloc(sizeof(ListReader));

	temp->size = 0;
	temp->head = NULL;

	return temp;
}

void AddReader(ListReader* listReader, Reader* reader)
{
	if (listReader->head == NULL)
	{
		NodeReader* nodeReader = (NodeReader*)malloc(sizeof(NodeReader));

		nodeReader->reader = reader;
		nodeReader->next = NULL;

		listReader->head = nodeReader;
		listReader->size++;
	}
	else
	{
		NodeReader* currNodeReader = listReader->head;

		while (currNodeReader->next != NULL)
		{
			currNodeReader = currNodeReader->next;
		}

		NodeReader* nodeReader = (NodeReader*)malloc(sizeof(NodeReader));

		nodeReader->reader = reader;
		nodeReader->next = NULL;

		currNodeReader->next = nodeReader;
		listReader->size++;
	}
}

Reader* FindReader(ListReader* listReader, char* surname, int group)
{
	NodeReader* node = listReader->head;

	for (int i = 0; i < listReader->size; ++i)
	{
		if ((strcmp(surname, node->reader->surname) == 0) && (node->reader->group == group))
			return node->reader;

		node = node->next;
	}

	return NULL;
}
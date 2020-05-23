#include "Reader.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Reader* CreateReader(char* surname, char* name, int group, char* number, char* email, char* note)
{
	Reader* reader = (Reader*)malloc(sizeof(Reader));

	ListDeal* listDeal = (ListDeal*)malloc(sizeof(ListDeal));
	listDeal->head = NULL;
	listDeal->size = 0;

	reader->surname = _strdup(surname);
	reader->name = _strdup(name);
	reader->group = group;
	reader->telephoneNumber = _strdup(number);
	reader->email = _strdup(email);
	reader->note = _strdup(note);
	reader->penalty = 0;
	reader->dealList = listDeal;

	return reader;
}
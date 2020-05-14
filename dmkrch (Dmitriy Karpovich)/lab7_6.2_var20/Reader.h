#pragma once


#include "ListDeal.h"


/* Структура, описывающая читателя */
struct Reader
{
	char* surname;
	char* name;
	int group;
	char* telephoneNumber;
	char* email;
	char* note;
	ListDeal* dealList;
	int penalty;
};



/* Создает объект класса Reader на той информации, что передается в параметрах */
Reader* CreateReader(char* surname, char* name, int group, char* number, char* email, char* note);
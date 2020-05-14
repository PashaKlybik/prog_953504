#pragma once

#include "Reader.h"


/* Структура, описывающая узел списка, хранящий книги */
struct NodeReader
{
	NodeReader* next;

	Reader* reader;
};

/* Структура, описывающая список, хранящий читателей */
struct ListReader
{
	NodeReader* head;

	int size;
};



/* Создает нового читателя в библиотеке на той информации, что введет пользователь */
void AddNewReader(ListReader* listReader);

/* Создает объект класса ListReader*/
ListReader* CreateListReader();

/* Добавляет объект класса Reader в объект класса ListReader */
void AddReader(ListReader* listReader, Reader* reader);

/* Ищет читателя по фамилии и номеру группу и возвращает такой объект класса Reader */
Reader* FindReader(ListReader* listReader, char* surname, int group);
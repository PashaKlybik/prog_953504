#pragma once

#include "Book.h"


/* Структура, описывающая узел списка, хранящий читателей */
struct NodeBook
{
	NodeBook* next;

	Book* book;
	int quantity;
};


/* Структура, описывающая список, хранящий читателей */
struct ListBook
{
	NodeBook* head;

	int size;
};



/* Создает объект класса ListBook */
ListBook* CreateListBook();

/* Добавляет объект класса Book в объект класса ListBook */
void AddBook(ListBook* listBook, Book* book, int quantity);

/* Ищет книгу по названию и возвращает такой объект класса Book */
Book* FindBook(ListBook* listBook, char* title);

/* Удаляет книгу Book из ListBook */
void RemoveBook(Book* book, ListBook* listBook);
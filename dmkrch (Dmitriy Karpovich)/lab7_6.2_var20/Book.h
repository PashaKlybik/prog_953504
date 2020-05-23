#pragma once


/* Структура, описывающая книгу */
struct Book
{
	char* author;
	char* title;
	char* note;
	int price;
};



/* Создает объект класса Book */
Book* CreateBook(char* author, char* title, int price, char* note);
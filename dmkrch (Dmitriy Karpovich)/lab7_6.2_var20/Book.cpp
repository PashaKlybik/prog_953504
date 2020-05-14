#include "Book.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>


Book* CreateBook(char* author, char* title, int price, char* note)
{
	Book* book = (Book*)malloc(sizeof(Book));

	book->author = _strdup(author);
	book->title = _strdup(title);
	book->price = price;
	book->note = _strdup(note);

	return book;
}
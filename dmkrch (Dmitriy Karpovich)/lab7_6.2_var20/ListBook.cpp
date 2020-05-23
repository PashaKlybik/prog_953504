#include "ListBook.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>


ListBook* CreateListBook()
{
	ListBook* temp = (ListBook*)malloc(sizeof(ListBook));

	temp->size = 0;
	temp->head = NULL;

	return temp;
}

void AddBook(ListBook* listBook, Book* book, int quantity)
{
	if (listBook->head == NULL)
	{
		NodeBook* nodeBook = (NodeBook*)malloc(sizeof(NodeBook));

		nodeBook->book = book;
		nodeBook->next = NULL;
		nodeBook->quantity = quantity;

		listBook->head = nodeBook;
		listBook->size++;
	}
	else
	{
		NodeBook* currNodeBook = listBook->head;

		while (currNodeBook->next != NULL)
		{
			currNodeBook = currNodeBook->next;
		}

		NodeBook* nodeBook = (NodeBook*)malloc(sizeof(NodeBook));

		nodeBook->book = book;
		nodeBook->next = NULL;
		nodeBook->quantity = quantity;

		currNodeBook->next = nodeBook;
		listBook->size++;
	}
}

Book* FindBook(ListBook* listBook, char* title)
{
	NodeBook* node = listBook->head;

	for (int i = 0; i < listBook->size; ++i)
	{
		if (strcmp(title, node->book->title) == 0)
			return node->book;

		node = node->next;
	}

	return NULL;
}

void RemoveBook(Book* book, ListBook* listBook)
{
	NodeBook* currNode = listBook->head;

	while (true)
	{
		if (currNode->book == book) // Если мы нашли совпадение передаваемой книги book с книгой, которая в списке listBook
		{
			if (currNode->quantity == 1)
			{
				if (currNode == listBook->head) // Если совпадение в голове списка
				{
					NodeBook* temp = listBook->head;
					listBook->head = listBook->head->next;

					free(temp);

					listBook->size--;
					break;
				}

				else // совпадение не в голове списка
				{
					NodeBook* previous = listBook->head;

					for (int i = 0; i < listBook->size; ++i)
					{
						if (previous->next->book == book)
							break;

						previous = previous->next;
					}

					NodeBook* toDelete = previous->next;

					previous->next = toDelete->next;

					free(toDelete);
					listBook->size--;
					break;
				}
			}

			else
			{
				currNode->quantity--;
				break;
			}
		}



		currNode = currNode->next;
	}
}
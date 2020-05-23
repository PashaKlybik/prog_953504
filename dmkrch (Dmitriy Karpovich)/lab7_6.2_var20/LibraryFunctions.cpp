#define MAX 40

#include "LibraryFunctions.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <string>

#include "CharFunctions.h"


void InitFromFile(CathLibrary* cathLibrary)
{
	// инициализируем читателей в библиотеке
	FILE* file;

	fopen_s(&file, "readersInput.txt", "r");
	ListReader* listReader = CreateListReader();

	while (!feof(file))
	{
		char singleLine[MAX];
		char name[MAX];
		char surname[MAX];
		int group;
		char telephone[MAX];
		char email[MAX];
		char note[MAX];

		fgets(singleLine, MAX, file);
		strcpy_s(surname, singleLine);

		fgets(singleLine, MAX, file);
		strcpy_s(name, singleLine);

		fgets(singleLine, MAX, file);
		group = atoi(singleLine);

		fgets(singleLine, MAX, file);
		strcpy_s(telephone, singleLine);

		fgets(singleLine, MAX, file);
		strcpy_s(email, singleLine);

		fgets(singleLine, MAX, file);
		strcpy_s(note, singleLine);

		fgets(singleLine, MAX, file);

		Reader* reader = CreateReader(surname, name, group, telephone, email, note);

		AddReader(listReader, reader);
	}

	fclose(file);

	cathLibrary->readerList = listReader;


	// теперь инициализируем книжки в библиотеку

	fopen_s(&file, "booksInput.txt", "r");
	ListBook* bookList = CreateListBook();

	while (!feof(file))
	{
		char singleLine[MAX];
		char author[MAX];
		char title[MAX];
		char note[MAX];
		int price;
		int quantity;

		fgets(singleLine, MAX, file);
		strcpy_s(author, singleLine);

		fgets(singleLine, MAX, file);
		strcpy_s(title, singleLine);

		fgets(singleLine, MAX, file);
		price = atoi(singleLine);

		fgets(singleLine, MAX, file);
		strcpy_s(note, singleLine);

		fgets(singleLine, MAX, file);
		quantity = atoi(singleLine);

		fgets(singleLine, MAX, file);

		Book* book = CreateBook(author, title, price, note);

		AddBook(bookList, book, quantity);
	}

	fclose(file);

	cathLibrary->bookList = bookList;
}

void ShowReaderInfo(Reader* reader)
{
	int k = 0;

	while (true)
	{
		if (reader->name[k] != '\n')
			printf("%c", reader->name[k]);
		else
			break;
		++k;
	}

	printf(" %s", reader->surname);
	printf("group: %d", reader->group);

	printf("\ncontact: ");
	k = 0;

	while (true)
	{
		if (reader->telephoneNumber[k] != '\n')
			printf("%c", reader->telephoneNumber[k]);
		else
			break;

		++k;
	}
	printf(", %s", reader->email);
	printf("books: ");

	ShowReaderBooks(reader->dealList);
	printf("\npenalties: ");
	if (reader->penalty < 1)
	{
		printf("no penalties");
	}
	else if (reader->penalty == 1)
	{
		printf("yellow card");
	}
	else
	{
		printf("red card :(");
	}
	printf("\nnote: %s", reader->note);
	printf("\n\n");
}

void ShowReaders(ListReader* readerList)
{
	NodeReader* node = readerList->head;

	for (int i = 0; i < readerList->size; ++i)
	{
		ShowReaderInfo(node->reader);

		node = node->next;
	}
}

void ShowBookInfo(NodeBook* node)
{
	int k = 0;

	while (true)
	{
		if (node->book->title[k] != '\n')
			printf("%c", node->book->title[k]);
		else
			break;

		++k;
	}

	printf(" by %s", node->book->author);
	printf("\tamount: %d  price: %d$", node->quantity, node->book->price);
	printf("\n\tnote: %s", node->book->note);
	printf("\n");
}

void ShowBooks(ListBook* bookList)
{
	NodeBook* node = bookList->head;

	for (int i = 0; i < bookList->size; ++i)
	{
		ShowBookInfo(node);

		node = node->next;
	}
}

void ShowReaderBooks(ListDeal* dealList)
{
	NodeDeal* node = dealList->head;

	for (int i = 0; i < dealList->size; ++i)
	{
		int k = 0;

		while (true)
		{
			if (node->deal->book->title[k] != '\n')
				printf("%c", node->deal->book->title[k]);
			else
				break;

			++k;
		}

		if (k != 0)
			printf(", ");

		node = node->next;
	}
}

void BorrowBook(char* surname, int group, char* title, CathLibrary* lib, DealDate* dealDate)
{
	Reader* reader = FindReader(lib->readerList, surname, group); // Ищем читателя на основе имени, фамилии
	Book* book = FindBook(lib->bookList, title); // Ищем книгу на основе названия 
	Deal* deal = CreateDeal(book, dealDate); // Создаем сделку, состоящую из книги + даты

	AddDeal(reader->dealList, deal); // Вносим сделку в список сделок найденного читателя
	RemoveBook(book, lib->bookList); // Удаляем книгу из библиотеки
}

void ReturnBook(char* surname, int group, char* title, CathLibrary* lib)
{
	Reader* reader = FindReader(lib->readerList, surname, group); // ищем читателя по фамилии, номеру группы
	Deal* deal = FindDeal(reader->dealList, title); // ищем сделку в списке сделок по названию книги

	AddBook(lib->bookList, deal->book, 1); // Добавляем обратну книжку в библиотеку
	RemoveDeal(deal, reader->dealList); // Удаляем сделку у читателя
}

bool ReaderExists(char* surname, int group, ListReader* listReader)
{
	Reader* reader = FindReader(listReader, surname, group);

	if (reader != NULL)
		return true;
	else
		return false;
}

bool BookExists(char* title, ListBook* listBook)
{
	Book* book = FindBook(listBook, title);

	if (book != NULL)
		return true;
	else
		return false;
}


void LibReport(CathLibrary* lib)
{
	int libBooks = 0;
	int readBooks = 0;
	int sumBooks = 0;

	NodeBook* nodeBook = lib->bookList->head;

	for (int i = 0; i < lib->bookList->size; ++i)
	{
		libBooks += nodeBook->quantity;

		sumBooks += nodeBook->book->price * nodeBook->quantity;

		nodeBook = nodeBook->next;
	}

	NodeReader* nodeReader = lib->readerList->head;

	for (int i = 0; i < lib->readerList->size; ++i)
	{
		readBooks += nodeReader->reader->dealList->size;

		NodeDeal* nodeDeal = nodeReader->reader->dealList->head;

		for (int k = 0; k < nodeReader->reader->dealList->size; ++k)
		{
			sumBooks += nodeDeal->deal->book->price;

			nodeDeal = nodeDeal->next;
		}

		nodeReader = nodeReader->next;
	}

	printf("\nAmount of books in library: %d", libBooks);
	printf("\nAmount of readers books: %d", readBooks);
	printf("\nAmount of readers: %d", lib->readerList->size);
	printf("\nTotal sum of books: %d $\n\n", sumBooks);
}

void DeleteLibrary(CathLibrary* lib)
{
	NodeBook* temp = lib->bookList->head;

	for (int i = 0; i < lib->bookList->size; ++i)
	{
		free(temp);

		temp = temp->next;
	}

	NodeReader* tempR = lib->readerList->head;

	for (int i = 0; i < lib->readerList->size; ++i)
	{
		free(tempR);

		tempR = tempR->next;
	}
}
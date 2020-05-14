#define MAX 40

#include <iostream>

#include "Library.h"
#include "CharFunctions.h"
#include <string.h>
#include "LibraryFunctions.h"
#include "Interface.h"


int main()
{
	CathLibrary* cathLibrary = CreateCathLibrary();

	InitFromFile(cathLibrary);

	while (true)
	{
		system("cls");
		PrintMenu(0);

		int choice = 0;
		int choice1 = 0;
		char surname[MAX];
		char title[MAX];
		int group = 0;
		int year;
		int month;
		int day;

		scanf_s("%d", &choice);

		switch (choice)
		{
		case 1:
			system("cls");

			PrintMenu(1);

			scanf_s("%d", &choice1);

			if (choice1 == 1)
			{
				system("cls");

				while (getchar() != '\n');

				printf("Enter surname of reader ");
				getline(surname, MAX);

				system("cls");

				printf("Enter group ", surname);
				scanf_s("%d", &group);

				system("cls");

				if (ReaderExists(surname, group, cathLibrary->readerList))
					ShowReaderInfo(FindReader(cathLibrary->readerList, surname, group));
				else
					printf("This reader is not registered in library\n\n");
			}

			else if (choice1 == 2)
			{
				system("cls");

				ShowReaders(cathLibrary->readerList);
			}

			while (getchar() != '\n');

			printf("Press enter to continue...");
			getchar();

			break;


		case 2:
			system("cls");
			
			ShowBooks(cathLibrary->bookList);

			while (getchar() != '\n');

			printf("Press enter to continue...");
			getchar();

			break;


		case 3:
			system("cls");

			while (getchar() != '\n');

			printf("Enter surname of reader ");
			getline(surname, MAX);

			printf("Enter group ", surname);
			scanf_s("%d", &group);

			while (getchar() != '\n');

			system("cls");

			if (ReaderExists(surname, group, cathLibrary->readerList))
			{
				if (FindReader(cathLibrary->readerList, surname, group)->penalty < 2)
				{
					printf("Enter title of book you want to borrow ");
					getline(title, MAX);

					system("cls");

					if (BookExists(title, cathLibrary->bookList))
					{
						printf("Enter year of returning the book ");
						scanf_s("%d", &year);
						printf("Enter month of returning the book ");
						scanf_s("%d", &month);
						printf("Enter day of returning the book ");
						scanf_s("%d", &day);

						DealDate* dealDate = CreateDealDate(year, month, day);

						BorrowBook(surname, group, title, cathLibrary, dealDate);

						system("cls");

						printf("You successfully borrowed the book from library!\n");
						printf("Dont forget to bring it back on %d.%d.%d\n\n", dealDate->year, dealDate->month, dealDate->day);

						while (getchar() != '\n');

						printf("Press enter to continue...");
						getchar();
					}
					else
					{
						printf("This book doesnt exist in library\n\n");

						printf("Press enter to continue...");
						getchar();
					}
				}
				else
				{
					system("cls");


					printf("Unfortunately, this reader cant borrow books due to too many penalties\n\n");

					printf("Press enter to continue...");
					getchar();
				}
			}
			
			else
			{
				printf("This reader is not registered in library");

				printf("\n\nPress enter to continue...");
				getchar();
			}

			break;


		case 4:
			system("cls");

			while (getchar() != '\n');

			printf("Enter surname of reader ");
			getline(surname, MAX);

			printf("Enter group ", surname);
			scanf_s("%d", &group);

			while (getchar() != '\n');

			system("cls");

			if (ReaderExists(surname, group, cathLibrary->readerList)) // Если существует читатель на учете
			{
				Reader* reader = FindReader(cathLibrary->readerList, surname, group); // Достаем читателя

				printf("Enter title of book you want to return back ");
				getline(title, MAX);

				system("cls");

				if (FindDeal(reader->dealList, title)) // Если нашлась книга у читателя
				{
					Deal* deal = FindDeal(reader->dealList, title); // Достаем сделку читателя

					printf("Enter current year ");
					scanf_s("%d", &year);

					while (getchar() != '\n');

					if (year <= deal->dealDate->year)
					{
						printf("Enter current month ");
						scanf_s("%d", &month);

						while (getchar() != '\n');

						if (month <= deal->dealDate->month)
						{
							printf("Enter current day ");
							scanf_s("%d", &day);

							while (getchar() != '\n');

							if (day <= deal->dealDate->day);
							else
							{
								printf("\nYou had to return book on %d.%d.%d\n", deal->dealDate->year, deal->dealDate->month, deal->dealDate->day);
								printf("Next time return book in time! I give you +1 penalty");
								reader->penalty++;
							}
						}
						else
						{
							printf("\nYou had to return book on %d.%d.%d\n", deal->dealDate->year, deal->dealDate->month, deal->dealDate->day);
							printf("Next time return book in time! I give you +1 penalty");
							reader->penalty++;
						}
					}
					else
					{
						printf("\nYou had to return book on %d.%d.%d\n", deal->dealDate->year, deal->dealDate->month, deal->dealDate->day);
						printf("Next time return book in time! I give you +1 penalty");
						reader->penalty++;
					}

					ReturnBook(surname, group, title, cathLibrary);
					printf("\nThe book was successfully returned!\n\n");

					printf("Press enter to continue...");
					getchar();
				}
				else
				{
					printf("This reader doesnt have such book\n\n");

					printf("Press enter to continue...");
					getchar();
				}
			}

			else
			{
				printf("This reader is not registered in library");

				printf("\n\nPress enter to continue...");
				getchar();
			}

			break;


		case 5:
			AddNewReader(cathLibrary->readerList);
			break;


		case 6:
			system("cls");

			LibReport(cathLibrary);

			while (getchar() != '\n');
			printf("Press enter to continue...");
			getchar();
			break;


		case 7:
			exit(0);
			break;
		}
	}

	getchar();
}
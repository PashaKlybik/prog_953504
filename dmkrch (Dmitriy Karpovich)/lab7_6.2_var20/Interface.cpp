#include "Interface.h"

#include <stdio.h>
#include <windows.h>


void PrintMenu(int key)
{
	printf("\t\tLibrary menu");
	printf("\n\n 1. Show readers");
	if (key == 1)
	{
		printf("\n\t1.1 Show by surname & group");
		printf("\n\t1.2 Show all");
	}
	printf("\n 2. Show books");
	if (key == 2)
	{
		printf("\n\t2.1 Show by title");
		printf("\n\t2.2 Show all");
	}
	printf("\n 3. Borrow book");
	printf("\n 4. Return book");
	printf("\n 5. Add new reader");
	printf("\n 6. Report");
	printf("\n 7. Exit");
	printf("\n\n ");
}
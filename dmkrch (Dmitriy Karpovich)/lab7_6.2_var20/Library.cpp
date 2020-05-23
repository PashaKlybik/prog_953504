#define MAX 40

#include "Library.h"

#include <stdlib.h>


CathLibrary* CreateCathLibrary()
{
	CathLibrary* cathLibrary = (CathLibrary*)malloc(sizeof(CathLibrary));

	cathLibrary->bookList = NULL;
	cathLibrary->readerList = NULL;

	return cathLibrary;
}

#pragma once

#include "ListBook.h"
#include "ListReader.h"

/* Структура, описывающая библиотеку */
struct CathLibrary
{
	ListBook* bookList;
	ListReader* readerList;
};



CathLibrary* CreateCathLibrary();
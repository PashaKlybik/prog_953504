#pragma once
#include "Book.h"


/* Структура, описывающая дату сделки */
struct DealDate
{
	int year;
	int month;
	int day;
};

/* Структура, описывающая сделку */
struct Deal
{
	Book* book;
	DealDate* dealDate;
};



/* Создает объект класса Deal */
Deal* CreateDeal(Book* book, DealDate* dealDate);

/* Создает объект класса DealDate */
DealDate* CreateDealDate(int year, int month, int day);
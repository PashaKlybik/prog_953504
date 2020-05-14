#include "Deal.h"

#include <stdlib.h>
#include <string>

Deal* CreateDeal(Book* book, DealDate* dealDate)
{
	Deal* deal = (Deal*)malloc(sizeof(Deal));

	deal->book = book;
	deal->dealDate = dealDate;

	return deal;
}

DealDate* CreateDealDate(int year, int month, int day)
{
	DealDate* dealDate = (DealDate*)malloc(sizeof(DealDate));

	dealDate->year = year;
	dealDate->month = month;
	dealDate->day = day;


	return dealDate;
}
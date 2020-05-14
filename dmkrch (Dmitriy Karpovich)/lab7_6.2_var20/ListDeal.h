#pragma once

#include "Deal.h"


/* Структура, описывающая узел сделки  */
struct NodeDeal
{
	NodeDeal* next;

	Deal* deal;
};

/* Структура, описывающая список, хранящий сделки */
struct ListDeal
{
	NodeDeal* head;

	int size;
};



/* Добавляет объект класса Deal в объект класса ListDeal*/
void AddDeal(ListDeal* dealList, Deal* deal);

/* Ищет объект Deal по навзанию книги в сделке и возвращает этот объект */
Deal* FindDeal(ListDeal* listDeal, char* title);

/* Удаляет сделку deal из listDeal */
void RemoveDeal(Deal* deal, ListDeal* listDeal);
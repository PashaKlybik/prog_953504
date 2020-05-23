#include "ListDeal.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>


void AddDeal(ListDeal* dealList, Deal* deal)
{
	if (dealList->head == NULL)
	{
		NodeDeal* nodeDeal = (NodeDeal*)malloc(sizeof(NodeDeal));

		nodeDeal->deal = deal;
		nodeDeal->next = NULL;

		dealList->head = nodeDeal;
		dealList->size++;
	}
	else
	{
		NodeDeal* currNodeDeal = dealList->head;

		while (currNodeDeal->next != NULL)
		{
			currNodeDeal = currNodeDeal->next;
		}

		NodeDeal* nodeDeal = (NodeDeal*)malloc(sizeof(NodeDeal));

		nodeDeal->deal = deal;
		nodeDeal->next = NULL;

		currNodeDeal->next = nodeDeal;
		dealList->size++;
	}
}

Deal* FindDeal(ListDeal* listDeal, char* title)
{
	NodeDeal* node = listDeal->head;

	for (int i = 0; i < listDeal->size; ++i)
	{
		if (strcmp(title, node->deal->book->title) == 0)
			return node->deal;

		node = node->next;
	}

	return NULL;
}

void RemoveDeal(Deal* deal, ListDeal* listDeal)
{
	NodeDeal* currNode = listDeal->head;

	while (true)
	{
		if (currNode->deal == deal) // Если мы нашли совпадение передаваемой книги как параметр и книги которая в списке 
		{
			if (currNode == listDeal->head) // Если совпадение в голове списка
			{
				NodeDeal* temp = listDeal->head;
				listDeal->head = listDeal->head->next;

				free(temp);

				listDeal->size--;
				break;
			}

			else // совпадение не в голове списка
			{
				NodeDeal* previous = listDeal->head;

				for (int i = 0; i < listDeal->size; ++i)
				{
					if (previous->next->deal == deal)
						break;

					previous = previous->next;
				}

				NodeDeal* toDelete = previous->next;

				previous->next = toDelete->next;

				free(toDelete);
				listDeal->size--;
				break;
			}
		}

		currNode = currNode->next;
	}
}
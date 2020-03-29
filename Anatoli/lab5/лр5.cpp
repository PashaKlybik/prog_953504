#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <conio.h>

typedef struct node {
	int val;
	struct node* next;
} node_t;

void Print_list(node_t* head);
void Push(node_t* head, int val);
void Sort(node_t* first, node_t* second, node_t* result);

int main() {
	/*First list*/
	node_t* first = NULL;
	first = (node_t*)(malloc(sizeof(node_t)));

	if (first == NULL) {
		return 1;
	}
	/*Second list*/
	node_t* second = NULL;
	second = (node_t*)(malloc(sizeof(node_t)));

	if (second == NULL) {
		return 1;
	}
	second->val = 12;
	second->next = NULL;

	first->val = 1;
	first->next = NULL;
	//Fill second list
	for (int i = 13; i < 15; i++)
	{
		Push(second, i);
	}
	//Fill first list
	for (int i = 2; i < 10; i++)
	{
		Push(first, i);
	}
	printf("First list : ");
	Print_list(first);
	printf("\nSecond list : ");
	Print_list(second);

	node_t* result = NULL;
	result = (node_t*)(malloc(sizeof(node_t)));
	if (result == NULL) {
		return 1;
	}
	result->val = 0;
	result->next = NULL;
	Sort(first, second, result);
	printf("\nFinal : ");
	Print_list(result);
	_getch();
	return 0;
}
void Print_list(node_t* head)
{
	node_t* current = head;

	while (current != NULL) {
		printf("%d  ", current->val);
		current = current->next;
	}
}
void Push(node_t* head, int val) {

	node_t* current = head;

	while (current->next != NULL) {
		current = current->next;
	}

	/* now we can add a new variable */
	current->next = (node_t*)malloc(sizeof(node_t));
	current->next->val = val;
	current->next->next = NULL;
}
void Sort(node_t* first, node_t* second, node_t* result)
{
	//include last element of the ending list
	bool check = 1;
	while ((first->next != NULL) || (second->next != NULL))
	{
		node_t* current = result;

		while (current->next != NULL) {
			current = current->next;
		}
		current->next = (node_t*)malloc(sizeof(node_t));

		if ((first->val > second->val) && (second->next != NULL))
		{
			int i = second->val;
			current->val = i;
			current->next->next = NULL;
			second = second->next;
		}
		else if ((first->val > second->val) && (second->next == NULL))  //If first list ended
		{
			int i = first->val;
			current->val = i;
			current->next->next = NULL;
			if (first->next != NULL)
			{
				first = first->next;
			}
		}
		else if ((first->val < second->val) && (first->next != NULL))
		{
			int i = first->val;
			current->val = i;
			current->next->next = NULL;
			if (first->next != NULL)
			{
				first = first->next;
			}
		}
		else if ((first->val < second->val) && (first->next == NULL))  //If first list ended
		{	
			if ((check == 1))
			{
				int i = first->val;
				current->val = i;
				current->next->next = NULL;
				check = 0;
			}
			else
			{
				int i = second->val;
				current->val = i;
				current->next->next = NULL;
				if (second->next != NULL)
				{
					second = second->next;
				}
			}
		}
		else if (first->val == second->val)
		{
			int i = first->val;
			current->val = i;
			current->next->next = NULL;
			if (first->next != NULL)
			{
				first = first->next;
			}
			if (second->next != NULL)
			{
				second = second->next;
			}
		}
		if ((first->next == NULL) && (second->next == NULL))
		{
			if (first->val < second->val)
			{
				current->next->next = (node_t*)malloc(sizeof(node_t));
				int i = second->val;
				current->next->val = i;
				current->next->next = NULL;
			}
			else if ((first->val > second->val))
			{
				current->next->next = (node_t*)malloc(sizeof(node_t));
				int i = first->val;
				current->next->val = i;
				current->next->next = NULL;
			}
		}
	}
}

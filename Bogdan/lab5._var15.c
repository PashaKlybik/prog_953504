#include <cstring>
#include <stdio.h>
#include <stdlib.h>

/*
 * Итак, принцип работы:
 * https://vk.cc/at1dtR
 * Нужно просто каждый раз, находя число, на которое длинное делится без остатка,
 * заносить его в лист с делителями и делить изначальный лсит на это число
 * Лист с делителями нужен, чтобы вести счёт делителей каждого числа
 * Например вот такой лист ( 0 2 1 0 1 ) значит, что у нас 2 двойки, одна тройка и пятёрка, т.е. число - 60
 * Кол-во же делителей для числа 60 будет равно (2+1)*(1+1)*(1+1) = 12
 * Ниже идёт реализация двунаправленного линейного списка
 */

typedef struct _Node {
	int value;
	struct _Node* next;
	struct _Node* prev;
} Node;

typedef struct _DblLinkedList {
	size_t size;
	Node* head;
	Node* tail;
} DblLinkedList;


DblLinkedList* createDblLinkedList()
{
	DblLinkedList* tmp = (DblLinkedList*)malloc(sizeof(DblLinkedList));
	tmp->size = 0;
	tmp->head = tmp->tail = NULL;

	return tmp;
}

void deleteDblLinkedList(DblLinkedList** list)
{
	Node* tmp = (*list)->head;
	Node* next = NULL;
	while(tmp)
	{
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
	free(*list);
	(*list) = NULL;
}

void pushFront(DblLinkedList* list, int data)
{
	Node* tmp = (Node*)malloc(sizeof(Node));
	if (tmp == NULL)
		exit(1);
	
	tmp->value = data;
	tmp->next = list->head;
	tmp->prev = NULL;

	if (list->head)
		list->head->prev = tmp;
	 list->head = tmp;
	
	if (list->tail == NULL)
		list->tail = tmp;

	list->size++;
}

void popFront(DblLinkedList* list)
{
	Node* tmp = (Node*)malloc(sizeof(Node));
	if (tmp == NULL)
		exit(1);
	tmp = list->head;
	
	if (list->size == 0)
		exit(2);
	
	list->head = list->head->next;

	if (list->head)
		list->head->prev = NULL;

	if (tmp == list->tail)
		list->tail = NULL;

	list->size--;
}

void pushBack(DblLinkedList* list, int value) {
	Node* tmp = (Node*)malloc(sizeof(Node));
	if (tmp == NULL) {
		exit(3);
	}
	tmp->value = value;
	tmp->next = NULL;
	tmp->prev = list->tail;
	if (list->tail) {
		list->tail->next = tmp;
	}
	list->tail = tmp;

	if (list->head == NULL) {
		list->head = tmp;
	}
	list->size++;
}

void popBack(DblLinkedList* list)
{
	Node *tmp = (Node*)malloc(sizeof(Node));
	if (tmp == NULL)
		exit(1);
	tmp = list->tail;

	if (list->size == 0)
		exit(2);;

	list->tail = list->tail->prev;

	if (list->tail)
		list->tail->next = NULL;

	if (tmp == list->head)
		list->head = NULL;

	list->size--;
}

Node* getNth(DblLinkedList* list, size_t index) {
	Node* tmp = list->head;
	size_t i = 0;

	while (tmp && i < index) {
		tmp = tmp->next;
		i++;
	}

	return tmp;
}

int Mod(DblLinkedList *list, int number) // Ф-ция для нахождения остатка
{
	Node* tmp = list->tail;
	

	int ostatok = 0;
	
	while (tmp) {
		ostatok *= 10;
		ostatok = (tmp->value + ostatok) % number;
		tmp = tmp->prev;
	}
	return ostatok;						//Возвращает этот самый остаток
}

void Multiply(DblLinkedList* list, int number)	// Ф-ция для умножения списка на number, ничего не возвращает, Здесь не используется, но пусть будет(по приколу чисто)
{
	int carry = 0;
	for (size_t i = 0; i < list->size || carry; ++i)
	{
		if (i == list->size)
			pushBack(list, 0);
		long long cur = carry + getNth(list, i)->value * 1ll * number;
		getNth(list, i)->value = int(cur % 10);
		carry = int(cur / 10);
	}
	while (list->size > 1 && list->tail->value == 0)
		popBack(list);
}

void Division(DblLinkedList* list, int number)	// Ф-ция для деления списка на number, ничего не возвращает
{
	int carry = 0;
	for (int i = (int)list->size - 1; i >= 0; --i) {
		long long cur = getNth(list, i)->value + carry * 1ll * 10;
		getNth(list, i)->value = int(cur / number);
		carry = int(cur % number);
	}
	while (list->size > 1 && list->tail->value == 0)
		popBack(list);
}

int main()
{
	char str[80];
	printf("Enter the number: ");
	gets_s(str, 80);

	DblLinkedList *List = createDblLinkedList();			//Создание списка для многоразрядного числа
	DblLinkedList* DividersList = createDblLinkedList();	//Создание списка для делителей
		
	for(int i=strlen(str) - 1; i>=0; i--)					//Заполняем список для числа входного
	{
		printf("|%c|\n", str[i]);
		pushBack(List, str[i]-48);
	}

	long long int i = 2;
	while(true)												//Пока список не будет состоять из одного числа(единицы) будет вайл крутиться
	{
		if (Mod(List, i) == 0)
		{
			Division(List, i);
			printf("|%d|", i);

			int temp = DividersList->size;		//Переменная, нужная для того, чтобы знать, надо зафиливать нулями лист или нет
			if (i > DividersList->size)
				for (int j = 0; j < i - temp; j++)
					pushBack(DividersList, 0);
			getNth(DividersList, i - 1)->value++;
			
			i = 1;
		}
		i++;
		if (List->size == 1 && getNth(List, 0)->value == 1)
			break;
	}

	printf("\n");
	int answer = 1;
	for (int i = 0; i < DividersList->size; i++)
	{
		answer *= getNth(DividersList, i)->value + 1;
		printf(" %d ", getNth(DividersList, i)->value);
	}

	printf("\nAnswer - %d", answer);
	
	getchar();
	return 0;
}
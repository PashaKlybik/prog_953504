#include <stdio.h>
#include <cstdlib>
#include <string.h>

/* Структура, описывающая элемент двунаправленного списка */
typedef struct item
{
	int digit;
	struct item* next;
	struct item* prev;
} Item;

/* Структура, описывающая многоразрядное число */
typedef struct mnumber
{
	Item* head;
	Item* tail;
	int n;
} MNumber;

void DeleteNumber(MNumber* numb);
MNumber CreateMNumber(const char* initStr);
void AddDigit(MNumber* number, int digit);
void PrintMNumber(MNumber number);
void PowerMNumber(MNumber &n1, int pow);


void main(void)
{
	MNumber a = CreateMNumber("3");
	int power = 0;

	printf("3^");
	scanf_s("%d", &power);



	PowerMNumber(a, power);
	PrintMNumber(a);

	DeleteNumber(&a);
}

/* Deletes number */
void DeleteNumber(MNumber* numb)
{
	Item* item = numb->head;
	Item* next;

	while (item != numb->tail)
	{
		next = item->next;

		free(item);

		item = next;
	}

	free(item);
}

/* Создает многоразрядное число из цифр строки */
MNumber CreateMNumber(const char initStr[])
{
	MNumber number = { NULL, NULL, 0 };
	int n;
	for (n = strlen(initStr) - 1; n >= 0; --n)
		AddDigit(&number, initStr[n] - '0');

	return number;
}


/* Добавляет цифру в многоразрядное число */
void AddDigit(MNumber* number, int digit)
{
	Item* p = (Item*)malloc(sizeof(Item));
	p->digit = digit;
	p->next = p->prev = NULL;

	if (number->head == NULL)
		number->head = number->tail = p;
	else
	{
		number->head->prev = p;
		p->next = number->head;
		number->head = p;
	}

	number->n++;
}

void PowerMNumber(MNumber& n1, int pow)
{
	MNumber multiply = CreateMNumber("");

	while (pow > 1)
	{
		Item* p1 = n1.tail;

		int digit;
		int pos = 0;
		int s1;

		while (p1 != NULL)
		{
			s1 = p1->digit;
			p1 = p1->prev;

			digit = (s1 * 3 + pos) % 10;
			pos = (s1 * 3 + pos) / 10;
			AddDigit(&multiply, digit);
		}

		if (pos != 0)
			AddDigit(&multiply, pos);


		n1 = multiply;
		multiply.tail = NULL;
		multiply.head = NULL;

		--pow;
	}
}


/* Выводит многоразрядное число на экран */
void PrintMNumber(MNumber number)
{
	Item* p = number.head;
	printf("\nNumber: ");
	while (p) 
	{
		printf("%d", p->digit);
		p = p->next;
	}
}
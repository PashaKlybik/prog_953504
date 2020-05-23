#include <stdio.h>
#include <cstdlib>
#include <string.h>

/* Struct that describes node of 2-linked list */
typedef struct item
{
	int digit;
	struct item* next;
	struct item* prev;
} Item;

/* Struct that decsribes big number */
typedef struct mnumber
{
	Item* head;
	Item* tail;
	int n;
} MNumber;


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
}

/* Creates big number string */
MNumber CreateMNumber(const char initStr[])
{
	MNumber number = { NULL, NULL, 0 };
	int n;
	for (n = strlen(initStr) - 1; n >= 0; --n)
		AddDigit(&number, initStr[n] - '0');

	return number;
}


/* Adds digit to number */
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


/* Printfs big number on the console */
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
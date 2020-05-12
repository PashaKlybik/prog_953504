//Задан двунаправленный список, указывающий порядок обработки одной из n очередей. 
//Элементы списка содержат номер обрабатываемой очереди i (i <= n );
//признак выполняемого действия: ‘А’ – элемент из списка добавляется в i-ю очередь, 
//‘D’ – из i-й очереди удаляется элемент; данные ( символ). 
//Разработать функцию обработки очередей в соответствии с « программой» двунаправленного списка. 
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996).

struct dvusp
{
public:
	char x;
	char com;
	int z;
	dvusp* next, * prev;
};

	void pri(dvusp** head)
	{
		dvusp* curr = *head;
		while (curr)
		{
			printf("%c %c %d", curr->x, curr->com, curr->z);
			curr = curr->next;
		}
	}

	void pri(dvusp* head)
	{
		if (head)
		{
			dvusp* curr = head;
			while (curr)
			{
				printf("%c   ",curr->x);
				curr = curr->next;
			}
		}
		printf("\n");
	}


	void makeQ(dvusp** head, char ch, char c, int r)
	{
		dvusp* ne = (dvusp*)malloc(sizeof(dvusp));
		ne->x = ch;
		ne->com = c;
		ne->z = r;
		ne->next = NULL;
		ne->prev = NULL;
		if (!*head)
			*head = ne;
		else
		{
			dvusp* curr = *head;
			while (curr->next) curr = curr->next;
			curr->next = ne;
			ne->prev = curr;
		}
	}

	void makeQ(dvusp** head, char ch)
	{
		dvusp* ne = (dvusp*)malloc(sizeof(dvusp));
		ne->x = ch;
		ne->next = NULL;
		ne->prev = NULL;
		if (!*head)
			*head = ne;
		else
		{
			dvusp* curr = *head;
			while (curr->next) curr = curr->next;
			curr->next = ne;
			ne->prev = curr;
		}
	}

	void vzyat(dvusp** head)
	{
		if (*head)
		{
			char t = 0;
			if (head)
			{
				dvusp* old_head = *head;
				t = (*head)->x;
				*head = (*head)->next;
				delete old_head;
			}
		}
		return;
	}



int main()
{
	dvusp* head = (dvusp*)malloc(sizeof(dvusp*));
	head = NULL;
	int n = 0, u = 0;
	printf ("How many queues should I create?\n");
	scanf_s ("%d",&u);
	printf("How many list items should I create?\n");
	scanf_s("%d", &n);

	for (int i = 0; i < n; i++) //создание списка с командами
	{
		int x; 
		char y=0, z=0;
		printf("\n#%d\n", i + 1);
		while (true)
		{
			printf("Command(A/D): ");
			rewind(stdin);
			scanf("%c", &y);
			if (y == 'A' || y == 'D') break;
			else printf("Try again!\n");
		}
		if (y == 'A')
		{
			printf("Data: ");
			rewind(stdin);
			scanf("%c", &z);
		}
		else z = 0;
		while (true)
		{
			printf("Number of queue: ");
			rewind(stdin);
			scanf_s("%d", &x);
			if (x > u) printf("Try again!\n");
			else break;
		}
		makeQ(&head, z, y, x);
	}

	dvusp** que = (dvusp**)calloc(u, sizeof(dvusp*)); //создание массива очередей

	dvusp* curr = head;
	while (curr)
	{
		int i = curr->z;
		if (curr->com == 'A') makeQ(&que[i - 1], curr->x);
		else vzyat(&que[i - 1]);
		curr = curr->next;
	}

	printf("\n");

	for (int i = 0; i < u; i++)
	{
		printf("#%d ", i + 1);
		pri(que[i]);
	}

	return 0;
}

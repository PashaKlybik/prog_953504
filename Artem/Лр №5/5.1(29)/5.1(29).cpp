//5.1 (29).Определить, являются ли два многоразрядных числа взаимно
//простыми.Для хранения многоразрядного числа использовать
//динамический двунаправленный список.
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
struct list
{
	int field; // поле данных
	struct list* next; // указатель на следующий элемент
	struct list* prev; // указатель на предыдущий элемент
};
struct list* Init(int a) // а- значение первого узла
{
	struct list* lst; // выделение памяти под корень списка
	lst = (struct list*)malloc(sizeof(struct list));
	lst->field = a;
	lst->next = NULL; // указатель на следующий узел
	lst->prev = NULL; // указатель на предыдущий узел
	return(lst);
}
struct list* Addelem(list* lst, int number)
{
	struct list* temp, * p;
	temp = (struct list*)malloc(sizeof(list));
	p = lst->next; // сохранение указателя на следующий узел
	lst->next = temp; // предыдущий узел указывает на создаваемый
	temp->field = number; // сохранение поля данных добавляемого узла
	temp->next = p; // созданный узел указывает на следующий узел
	temp->prev = lst; // созданный узел указывает на предыдущий узел
	if (p != NULL)
		p->prev = temp;
	return(temp);
}

int Check(int num1, int num2)
{
	return num2 ? Check(num2, num1 % num2) : num1;
}

void Delete(list* head)
{
	list* prev = head;
	while (prev->next)
	{
		list* temp;
		temp = prev;
		prev = prev->next;
		free(temp);
	}
	prev = prev->next;
	free(prev);
}

int main() 
{
	list* head, * cur;
	int num1, num2;
	// Создаем список из 2 элементов
	printf(" Enter the first number: ");
	scanf("%d", &num1);

	head = Init(num1);
	cur = head;

	printf(" Enter the second number: ");
	scanf("%d", &num2);
	cur = Addelem(cur, num2);

	printf("\n");
	if (Check(num1, num2) == 1)
		printf(" Numbers are mutually simple!\n");
	else printf(" Numbers aren't mutually simple!\n");

	Delete(head);
	getchar();
	return 0;
}
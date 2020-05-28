// ---------------------------------------------------------------------------

#pragma hdrstop
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include "ListOfTowns.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)

/* заполнение списка информацией из файла */
void ReadFromFile(ListOfTowns *towns) {
	FILE *file;
	file = fopen("G:\\Ira\\Progr\\LR7\\Town.txt", "r");

	if (!file) {
		printf("Error. Technical difficulites.");
		getch();
		exit(1);
	}
	float longti, lati;
	char *name = (char*)malloc(sizeof(char));
	while (fscanf(file, "%s %f %f", name, &longti, &lati) != EOF) {
		AddNewTown(towns, name, longti, lati);
	}
	fclose(file);
}

/* ƒобавл€ет новый узел в конец списка */
void AddNewTown(ListOfTowns *towns, char name[20], float longti, float lati) {
	Town *tmp = (Town*) malloc(sizeof(Town));
	if (tmp == NULL) {
		printf("Error. Tehnical dificulties.");
		getch();
		exit(3);
	}
	for (int i = 0; i < 20; i++) {
		tmp->TownName[i] = name[i];
	}
	tmp->longtitude = longti;
	tmp->latitude = lati;
	tmp->next = NULL;
	tmp->prev = towns->tail;
	if (towns->tail) {
		towns->tail->next = tmp;
	}
	towns->tail = tmp;

	if (towns->head == NULL) {
		towns->head = tmp;
	}
}

/* создание списка */
ListOfTowns* CreateListOfTowns() {
	ListOfTowns *tmp = (ListOfTowns*) malloc(sizeof(ListOfTowns));
	tmp->head = tmp->tail = NULL;

	return tmp;
}

/* удаление списка*/
void DeleteListOfTowns(ListOfTowns **list) {
	Town *tmp = (*list)->head;
	Town *next = NULL;
	while (tmp) {
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
	free(*list);
	(*list) = NULL;
}

/* вывод списка в консоль */
void PrintTowns(ListOfTowns towns) {
	struct Town *p = (Town*)malloc(sizeof(Town));
	p = towns.head;
	while (p != NULL) // условие окончани€ обхода
	{
		printf("%s %.2f %.2f\n ", p->TownName, p->longtitude, p->latitude);
		// вывод значени€ элемента p
		p = p->next; // переход к следующему узлу
	}
}


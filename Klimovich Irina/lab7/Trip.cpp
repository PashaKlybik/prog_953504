// ---------------------------------------------------------------------------

#pragma hdrstop

#include "Trip.h"
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <ctime>
// ---------------------------------------------------------------------------
#pragma package(smart_init)

/* Добавляет новый узел в конец списка */
void AddPost(Trip *trip, char name[20], float longti, float lati) {
	if (trip->head != NULL) {
		float longt2, lat2;
		longt2 = trip->tail->longtitude;
		lat2 = trip->tail->latitude;
		trip->price += fabs(longti - longt2) + fabs(lati - lat2);
	}
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
	tmp->prev = trip->tail;
	if (trip->tail) {
		trip->tail->next = tmp;
	}
	trip->tail = tmp;

	if (trip->head == NULL) {
		trip->head = tmp;
	}
}

/* создание списка */
Trip* CreateTrip() {
	Trip *tmp = (Trip*) malloc(sizeof(Trip));
	tmp->head = tmp->tail = NULL;
	tmp->next = tmp->prev = NULL;
	tmp->price = 0;

	return tmp;
}

/* удаление списка */
void DeleteTrip(Trip **list) {
	Town *tmp = (*list)->head;
	Town *next = NULL;
	while (tmp) {
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
	free(*list);
	(*list)->prev = NULL;
	(*list)->next = NULL;
	(*list)->price = 0;
}

/* вывод списка в консоль */
void PrintTrip(Trip trip) {
	// printf("\nPrice: %.2f\n", trip.price);
	struct Town *p;
	p = trip.head;
	while (p != NULL) // условие окончания обхода
	{
		printf("%s \t", p->TownName); // вывод значения элемента p
		p = p->next; // переход к следующему узлу
	}
	printf("\n");
}

/* добавление новых узлов выбранных пользователем в список */
void AddTrip(Trip *trip, ListOfTowns towns) {
	printf("Press 1-to add town, 2-not to add, 3-to stop adding.\n");
	Town *temp = (Town*)malloc(sizeof(Town));
	temp = towns.head;
	int answer = 0;
	while (temp != NULL) {
		printf("%s\n", temp->TownName);
		scanf("%d", &answer);
		if (answer == 1) {
			AddPost(trip, temp->TownName, temp->longtitude, temp->latitude);
		}
		else if (answer == 3) {
			break;
		}
		else if (answer != 2) { /* если был произведен неправильный ввод */
			printf("Encorrect input.\n"); /* будет требовать повторить */
			printf("Press 1-to add town, 2-not to add, 3-to stop adding.\n");
			temp = temp->prev;
		}
		temp = temp->next;
	}
}

/* создание стандартного маршрута путем добавления случайных узлов */
void StandartTrip(Trip *trip, ListOfTowns towns) {
	Town *temp = (Town*)malloc(sizeof(Town));
	temp = towns.head;
	int t = 0;
	int x, y; /* случайный числа отвечающиие за диапазон */
	x = rand() % 100;
	y = rand() % 100;
	if (x > y) {
		int t = y;
		y = x;
		x = t;
	}
	while (temp != NULL) {
		t = rand() % 100;
		if (t >= x && t <= y) { /* если в диапазоне, то узел будет добавлен */
			AddPost(trip, temp->TownName, temp->longtitude, temp->latitude);
		}
		temp = temp->next;
	}
	/* если ни один узел не попал в список добавить начало и конец списка */
	if (trip->head == NULL) {
		AddPost(trip, towns.head->TownName, towns.head->longtitude,
			towns.head->latitude);
		AddPost(trip, towns.tail->TownName, towns.tail->longtitude,
			towns.tail->latitude);
	}
	if (trip->head == trip->tail) { /* добавлен только один город */
		if (trip->head != towns.head) {  /*ород не является первым в списке городов*/
			AddPost(trip, towns.head->TownName, towns.head->longtitude,
				towns.head->latitude);
		}
		else /*добавленный город является первым в списке городов*/
			AddPost(trip, towns.head->next->TownName,
			towns.head->next->longtitude, towns.head->next->latitude);
		if (trip->head != towns.head) {/*город не является последним в списке*/
			AddPost(trip, towns.tail->TownName, towns.tail->longtitude,
				towns.tail->latitude); /*добавленый город последний в списке городов*/
		}
		else
			AddPost(trip, towns.tail->prev->TownName,
			towns.tail->prev->longtitude, towns.tail->prev->latitude);
	}
}
void CopyTrip(Trip *route, Trip tr) {/*копирование маршрута*/
	Town *temp = (Town*)malloc(sizeof(Town));
	temp = tr.head;
	while(temp) {
		AddPost(route, temp->TownName, temp->longtitude, temp->latitude);
		temp = temp->next;
	}
}

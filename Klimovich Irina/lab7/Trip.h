// ---------------------------------------------------------------------------

#ifndef TripH
#define TripH
#include "Town.h"
#include "ListOfTowns.h"

// ---------------------------------------------------------------------------
/* маршрут = двусвязный список */
struct Trip {
	float price; // цена пути
	Town *head; // первый город
	Town *tail; // последний город
	struct Trip *next; // следующий маршрут
	struct Trip *prev; // предыдущий маршрут
};

void AddPost(Trip *trip, char name[20], float longti, float lati);
// добавление новoго узла
Trip* CreateTrip(); // создание списка
void DeleteTrip(Trip **list); // удаляет список
void PrintTrip(Trip trip); /* вывод маршрута */
void AddTrip(Trip *trip, ListOfTowns towns); /* добавление маршрута */
void StandartTrip(Trip *trip, ListOfTowns towns);
/* добавление маршрута из случайных городов */
void CopyTrip(Trip *route, Trip tr);/*копирование маршрута*/
#endif

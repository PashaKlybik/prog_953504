// ---------------------------------------------------------------------------

#ifndef ListOfTripsH
#define ListOfTripsH
#include "Trip.h"

// ---------------------------------------------------------------------------
/* маршрут = двусвязный список */
struct ListOfTrips {
	Trip *head; // первый маршрут
	Trip *tail; // последний маршрут
	int amount;
};

void AddRoute(ListOfTrips *trips, Trip *tmp, ListOfTowns towns);
// добавление нового узла
void AddStandartTrip(ListOfTrips *trips, ListOfTowns towns);
/* добавление маршрута из случайных городов */
ListOfTrips* CreateListOfTrips(); // создание списка
void PrintListOfTrips(ListOfTrips trips);/*вывод списка маршрутов*/
void DeleteListOfTrips(ListOfTrips **trips);/*удаление*/
Trip* SearchTrip(ListOfTrips tripps, int number); /*поиск маршрута по номеру*/

#endif

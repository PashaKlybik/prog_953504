// ---------------------------------------------------------------------------

#ifndef TProgramH
#define TProgramH
#include "ListOfTrips.h"

// ---------------------------------------------------------------------------
struct Date { // дата поездки

	unsigned short int day;
	unsigned short int month;
	unsigned short int year;
};

struct Service { // услуга

	bool chose; // выбрана или нет
	float price; // стоимость
	char name[40]; // нащвание
};

typedef struct TouristProgram {
	struct Trip *route; // маршрут
	Date date; // дата
	int places; // количество записанных на нее туристов
	float price; // стоимость
	Service service[9]; // услуги
} TProgram;

TProgram* CreateProgram(); /* создание программы */
void AddPersonalProgram(TProgram*, ListOfTowns, ListOfTrips*);
/* добавление новой рограммы маршрут которой полностью выбирает пользователь */
void ChooseTrip(TProgram *prog, ListOfTrips trips, int number);
/* выбор маршрута для программы*/
void PrintProgram(TProgram prog);/*вывод программы*/
void DeleteTProgram(TProgram *prog);/*удаление*/
void Services(TProgram *prog); /*выбор услуг*/
void CopyInf(TProgram* pr1, TProgram* pr2);/*копирование информации из pr1 в pr2*/

#endif

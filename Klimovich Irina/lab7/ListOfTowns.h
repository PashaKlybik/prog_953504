// ---------------------------------------------------------------------------

#ifndef ListOfTownsH
#define ListOfTownsH
#include "Town.h"

// ---------------------------------------------------------------------------
/* список всех городов */
struct ListOfTowns {
	Town *head;
	Town *tail;
};

void ReadFromFile(ListOfTowns *towns); // чтение из файла
void AddNewTown(ListOfTowns *towns, char name[20], float longti, float lati);
// добавление новго узла
ListOfTowns* CreateListOfTowns(); // создание списка
void DeleteListOfTowns(ListOfTowns **list); // удаляет список
void PrintTowns(ListOfTowns towns);  /*вывод городов*/
#endif

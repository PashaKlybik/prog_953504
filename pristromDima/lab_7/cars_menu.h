#ifndef CARS_MENU_H
#define CARS_MENU_H

#include <stdio.h>
#include <conio.h>
#include <windows.h>

#include "cars.h"
#include "service.h"

#define UP_ARROW    72
#define DOWN_ARROW  80
#define ENTER       13
#define ESCAPE      27
#define F1          59
#define P_KEY       112
#define Y_KEY       121

void showCarsMenu(CarList **car_list);

void cars_scrollUp(COORD *marker);
void cars_scrollDown(COORD *marker);
void cars_mark(int line);
void cars_demark(int line);

void cars_showDatabase(CarList *car_list);
void cars_loadFromFile(CarList *car_list);
void cars_dumpToFile(CarList *car_list);
void cars_search(CarList *car_list);
CarUnit scanCarInfo(void);

void getHelp(void);

#endif // CARS_MENU_H

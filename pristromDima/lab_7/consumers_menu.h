#ifndef CONSUMERS_MENU_H
#define CONSUMERS_MENU_H

#include <stdio.h>
#include <conio.h>
#include <windows.h>

#include "cars_menu.h"
#include "consumers.h"
#include "service.h"

#define UP_ARROW    72
#define DOWN_ARROW  80
#define ENTER       13
#define ESCAPE      27

void showConsumersMenu(CarList **car_list, ConsumerList **consumer_list);

void cons_scrollUp(COORD *marker);
void cons_scrollDown(COORD *marker);
void cons_mark(int line);
void cons_demark(int line);

void cons_showDatabase(ConsumerList *consumer_list);
void cons_loadFromFile(ConsumerList *consumer_list);
void cons_dumpToFile(ConsumerList *consumer_list);
int cons_select(CarList *cars, ConsumerList *consumer_list);
void cons_search(ConsumerList *consumer_list);
Consumer scanConsumerInfo(void);

#endif // CONSUMERS_MENU_H

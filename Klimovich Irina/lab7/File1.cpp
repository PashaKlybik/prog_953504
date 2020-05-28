// ---------------------------------------------------------------------------

#pragma hdrstop

#include <tchar.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include "ListOfTowns.h"
#include "ListOfTrips.h"
#include"TProgram.h"
#include <ctime>
#include <time.h>
#include <iostream>
#define MaxPlace 30 //максимальное количество туристов в программах
// ---------------------------------------------------------------------------
#pragma argsused

/*6.2 (24). Santaren. Программный модуль управления туристическими
программами. В каждую программу входит следующая
информация: маршрут, дата, количество мест, общая стоимость
тура. Программа состоит из набора обязательных и необязательных
туристических услуг. Пользователь может самостоятельно
сформировать свою программу либо выбрать полную программу.
Возможно создание новых туристических программ и добавление
услуг в существующие. Запись туристов на каждую программу,
оформление туристических поездок по мере комплектования групп.
Расчет доходов компании.*/

void InputDate(Date *date);/* контроль ввода даты*/
void Input(int &number, int max); /* котнтроль ввода целого числа number(не больше max)*/
void Menu();/*вывод меню*/
void SubMenu1();/*подменю */
void SubMenu2();
void SubMenu3();

// ---------------------------------------------------------------------------
int main() {
	srand(time(NULL));
	ListOfTowns *towns = CreateListOfTowns();/* города, которые можно посетить*/
	ReadFromFile(towns);/* информация из файла*/
	ListOfTrips *trips = CreateListOfTrips(); /* список маршрутов*/
	for (int i = 0; i < 5; i++) {
		AddStandartTrip(trips, *towns);/*случайные маршруты*/
	}
	TProgram *prog = (TProgram*)malloc(20 * sizeof(TProgram));
	/* туристические программы*/
	int work = 1; /* выбранный пользователем пункт меню*/
	int subwork = 0; /* выбранный пользователем пункт подменю*/
	int k = 0; /*количество существуюших туристических программ*/
	int number = 0;/* для различного пользовательского ввода*/
	while (work) {
		number = 0;
		Menu();/* вывод пунктов меню*/
		Input(work, 4); /*ввод пункта меню*/
		switch (work) {
		case 1:
			printf("End");
			work = 0; /*завершение работы*/
			break;
		case 2:
			SubMenu1(); /*подменю*/
			Input(subwork, 4);
			switch (subwork) {
			case 1:
				break;
			case 2: /* create new program */
				if (k < 20) {
					prog[k] = *CreateProgram();
					printf("1.Choose existing route.\n");
					printf("2.Create your own route.\n");
					printf("Enter number of function.\n");
					Input(number, 2);
					if (number == 1) { /*выбрать существующий маршрут*/
						PrintListOfTrips(*trips);
						printf("Enter number of trip\t");
						Input(number, trips->amount + 1);
						ChooseTrip(&prog[k], *trips, number);
					}
					else if (number == 2) { /*создать свой маршрут*/
						AddPersonalProgram(&prog[k], *towns, trips);
					}
					printf("Number of tourists: ");
					Input(prog[k].places, MaxPlace);/* количество туристов*/
					InputDate(&prog[k].date);/*ввод даты*/
					Services(&prog[k]);  /* выбор различных услуг*/
					printf("Price: %.3f\n", prog[k].price); /*вывод получившейся цены*/
					++k;
				}
				break;
			case 3: // existing program
				if (k != 0) {
					for (int i = 0; i < k; i++) {
						printf("%d.\n", i + 1);
						PrintProgram(prog[i]);
					}
					int index = 0;
					printf("Enter number of program");
					Input(index, k); /*выбор программы*/
					--index;
					printf("Number of tourists: "); /*добавление количества туристов*/
					Input(number, MaxPlace - prog[index].places);
					prog[index].places += number;
				}
				else
					printf("No existing programs");
				break;
			case 4: /* add service */
				if (k != 0) {
					for (int i = 0; i < k; i++) {
						printf("%d.\n", i + 1);
						PrintProgram(prog[i]);
					}
					printf("Enter number of program\t");
					prog[k] = *CreateProgram();
					Input(number, k);
					--number;
					CopyInf(&prog[k], &prog[number]); /*копирование существующей программы*/
					Services(&prog[k]);  /*добавление услуг*/
					printf("Number of tourists: ");
					Input(prog[k].places, MaxPlace);/* количество человек*/
					++k;
				}
				else
					printf("No existing programs");
				break;
			default:
				printf("Error. Enter one more time.\n");
				break;
			}
			break;
		case 3:
			SubMenu2();
			Input(subwork, 3);
			switch (subwork) {
			case 1:
				break;
			case 2: {
				printf("\n");
				int t = 1;   /*вывод программ, у которых набралась целая группа*/
				for (int i = 0; i < k; i++) {
					if (prog[i].places == 30) {
						printf("%d\n", t);
						PrintProgram(prog[i]);
						++t;
					}
				}
				} break;
			case 3:
				printf("\n");/*вывод всех существующих программ*/
				for (int i = 0; i < k; i++) {
					PrintProgram(prog[i]);
				}
				break;
			default:
				printf("Error. Enter one more time.\n");
				break;
			}
			break;
		case 4:
			SubMenu3();
			Input(subwork, 2);
			switch (subwork) {
			case 1:
				break;
			case 2: {  /*доходы компании*/
					float income = 0.0;
					for (int i = 0; i < k; i++) {
						income += (prog[i].places*prog[i].price);
					}
					printf("Company income is about %.3f\n", income);
				} break;
			default:
				printf("Error. Enter one more time.\n");
				break;
			}
			break;
		default:
			printf("Error. Enter one more time..\n");
			break;
		}
	}
	/*очищение памяти*/
	for (int i = 0; i < k; i++) {
		DeleteTProgram(&prog[i]);
	}
	free(prog);
	DeleteListOfTrips(&trips);
	DeleteListOfTowns(&towns);
	return 0;
}

// ---------------------------------------------------------------------------
void Menu() {
	printf("\n1.Exit.\n");
	printf("2.Record on a tourist program.\n");
	printf("3.Tourist trips\n");
	printf("4.Company income\n");
	printf("Enter number of service\n");
}

void SubMenu1() {
	printf("Record on a tourist program.\n");
	printf("\t1.To menu.\n");
	printf("\t2.Create new program.\n");
	printf("\t3.Choose existing program.\n");
	printf("\t4.Add service for an existing program.\n");
	printf("Enter number of service\n");
}

void SubMenu2() {
	printf("Tourist trips.\n");
	printf("\t1.To menu.\n");
	printf("\t2.Print tourist trips.\n");
	printf("\t3.Print tourist programs.\n");
	printf("Enter number of service\n");
}

void SubMenu3() {
	printf("Company income.\n");
	printf("\t1.To menu.\n");
	printf("\t2.Print company income.\n");
	printf("Enter number of service\n");
}

void InputDate(Date *date) {
	time_t now = time(0);
	struct tm *time;
	time = localtime(&now);
	bool error = false;
	do {
		error = false;
		printf("Date: ");
		scanf("%d.%d.%d", &date->day, &date->month, &date->year);
		fflush(stdin);
		if (date->year < time->tm_year + 1900)
		{ /* если введен год иеньше чем сейчас */
			error = true;
		}
		/* если введен месяц этого года, который уже был */
		else if (date->year == time->tm_year + 1900 && date->month <
			time->tm_mon + 1) {
			error = true;
		}
		/* если введен день этого месяца этогго года, который уже был */
		else if (date->month == time->tm_mon + 1 && date->day < time->tm_mday) {
			if (date->year == time->tm_year + 1900) {
				error = true;
			}
		}
		/* если введен отрицательное число или ноль */
		else if (date->day < 1 || date->month < 1) {
			error = true;
		}
		/* проверка на количество дней для первых семи месяцев кроме февраля */
		else if (date->month < 8 && date->month != 2) {
			if (date->month % 2 != 0 && date->day > 31) {
				error = true;
			}
			else if (date->day > 30) {
				error = true;
			}
		}
		/* проверка на количество дней для других месяцев */
		else if (date->month > 7) {
			if (date->month > 12) { /* если введен номер месяца больше 12 */
				error = true;
			}
			if (date->month % 2 == 0 && date->day > 31) {
				error = true;
			}
			else if (date->day > 30) {
				error = true;
			}
		}
		else if (date->month == 2) { /* проверка февраля */
			if (date->year % 4 != 0 ||
				date->year % 100 == 0 && date->year % 400 != 0) {
				if (date->day > 28) { /* обычный год */
					error = true;
				}
			}
			else if (date->day > 29) { /* високосный год */
				error = true;
			}
		}
		if (error) {
			printf("Error.Enter one more time.\n");
			date->day = date->month = date->year = 0;
		}
	}
	while (error);
}

void Input(int &number, int max) { /*проверка ввода*/
	bool error = false;
	do {
		error = false;
		int res = scanf("%d", &number);
		fflush(stdin); /*очищение буфера*/
		if (res != 1)
			error = true;
		if (number < 1 || number > max) {
			error = true;
		}
		if (error)
			printf("Invalid input. Try again.\n");
	}
	while (error);
}

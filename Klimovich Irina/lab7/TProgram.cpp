// ---------------------------------------------------------------------------

#pragma hdrstop
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include "TProgram.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)

TProgram* CreateProgram() { /* создание программы*/
	TProgram *prog = (TProgram*)malloc(sizeof(TProgram));
	prog->route = CreateTrip();
	prog->date.day = prog->date.month = prog->date.year = 0;
	prog->places = 0;
	prog->price = 0.0;
	FILE *file;
	file = fopen("G:\\Ira\\Progr\\LR7\\Service.txt", "r");
	if (!file) { //чтение услуг из файла*/
		printf("Error. Technical difficulites.");
		getch();
		exit(1);
	}
	int t = 0;
	int i = 0;
	while (fscanf(file, "%s %f %d", prog->service[i].name,
		&prog->service[i].price, &t) != EOF) {
		if (t == 1) {
			prog->service[i].chose = true;
		}
		else {
			prog->service[i].chose = false;
		}	
		++i;
	}
	fclose(file);

	return prog;
}
/*добавление программы маршрут которой полностью выбирает пользователь*/
void AddPersonalProgram(TProgram *prog, ListOfTowns towns, ListOfTrips *trips) {
	AddRoute(trips, prog->route, towns);
}
/*выбор маршрута из уже существующих*/
void ChooseTrip(TProgram *prog, ListOfTrips trips, int number) {
	prog->route = SearchTrip(trips, number);
}
/*вывод прграммы*/
void PrintProgram(TProgram prog) {
	printf("Price for one person: %.3f\nNumber of people: %d\n", prog.price,
		prog.places);
	printf("Date: %d.%d.%d\n", prog.date.day, prog.date.month,
		prog.date.year);
	printf("Services:\n");
	for (int i = 0; i < 9; i++) {
		if (prog.service[i].chose) {
			printf("%s %.2f\n", prog.service[i].name, prog.service[i].price);
		}
	}
	printf("Route:\n");
	PrintTrip(*prog.route);
	printf("\n\n");
}
/*удаление программы*/
void DeleteTProgram(TProgram * prog) {
	DeleteTrip(&prog->route);
	prog->date.day = prog->date.month = prog->date.year;
	prog->places = prog->price = 0;
}
/*услуги*/
void Services(TProgram * prog) {
	int number = 0;
	int i = 0;
	int index;
	printf("Mandatory Services: \n");  /* обязательные услуги*/
	while (i!=4) {
		if (prog->service[i].price<=1) {
			prog->service[i].price = prog->route->price;
		}
		printf("%s %.2f\n", prog->service[i].name, prog->service[i].price);
		++i;
	}
	index = i - 1;
	printf("Optional Services\n");/*необязательные услуги*/
	while (i!=9) {
	    printf("%d. ", i-index);
		printf("%s %.2f\n", prog->service[i].name, prog->service[i].price);
		++i;
	}
	printf("Enter numbers of optional services without spaces or 0 for none.");
	scanf("%d", &number);
	while (number != 0) {
		prog->service[index + (number % 10)].chose = true;
		number /= 10;
	}
	for (int j = 0; j < 9; j++) {
		if (prog->service[j].chose) {
			prog->price += prog->service[j].price;
		}
	}
}
/*копирование информации*/
void CopyInf(TProgram *pr1, TProgram *pr2) {
	pr1->route = *&pr2->route;
	pr1->date = *&pr2->date;
	for (int i = 0; i < 9; i++) {
		pr1->service[i].chose = *&pr2->service[i].chose;
		pr1->service[i].price = *&pr2->service[i].price;
	}
}

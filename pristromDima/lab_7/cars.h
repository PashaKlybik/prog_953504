#ifndef AUTOS_H
#define AUTOS_H

#define CURRENT_YEAR 2019

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum States { NEW, USED };
typedef int State;

enum Fields { MODEL, STATE, YEAR, ENGINE_CAPACITY, MILEAGE, POWER, PRICE,
              NAME, CONTACTS, FINANCES };
typedef int Field;

typedef struct
{
    char model[20];
    State state;
    int year;
    int engine_capacity;
    int mileage;
    int power;
    float price;
} CarUnit;

struct CarListNode
{
    CarUnit value;
    struct CarListNode *prev;
    struct CarListNode *next;
};

typedef struct
{
    struct CarListNode *first;
    struct CarListNode *last;
    int size;
    int sold;
    int obtained;
    float income;
} CarList;

int loadCarBase(CarList *cars, char *path);
int dumpCarBase(CarList *cars, char *path);
void addCar(CarList *cars, CarUnit car);
int removeCar(CarList *cars, struct CarListNode *node, CarUnit car);
void sortByField(CarList *cars, Field field);
CarList* searchCars(CarList *cars, Field field, char *value);
void deallocCarList(CarList *cars);

void sellCar(CarList *cars, CarUnit car);
void obtainCar(CarList *car, CarUnit order);

#endif // AUTOS_H

#ifndef CONSUMERS_H
#define CONSUMERS_H

#include "cars.h"

typedef struct
{
    char name[100];
    int contacts;
    CarUnit *request;
    float finances;
} Consumer;

struct ConsumerListNode
{
    Consumer value;
    struct ConsumerListNode *prev;
    struct ConsumerListNode *next;
};

typedef struct
{
    struct ConsumerListNode *first;
    struct ConsumerListNode *last;
    int size;
} ConsumerList;

int loadConsumerBase(ConsumerList *consumers, char *path);
int dumpConsumerBase(ConsumerList *consumers, char *path);
void addConsumer(ConsumerList *consumers, Consumer consumer);
int addOrder(ConsumerList *consumers, Consumer consumer, CarUnit *order);
int removeConsumer(ConsumerList *consumers, struct ConsumerListNode *node, Consumer order);
int removeOrder(ConsumerList *consumers, Consumer consumer);
Consumer* getConsumer(ConsumerList *consumers, struct ConsumerListNode *node, Consumer consumer);
ConsumerList* searchConsumers(ConsumerList *cars, Field field, char *value);
void deallocConsumerList(ConsumerList *consumers);

CarUnit* selectCar(CarList *cars, CarUnit order);
int buyCar(ConsumerList *consumers, CarList *cars, CarUnit *car, Consumer *consumer);

#endif // CONSUMERS_H

#include <stdio.h>
#include <time.h>
#include <malloc.h>
#include <stdlib.h>

typedef struct service
{
    int serviceTime;
    int number;
    struct service* next;
    struct service* prev;
} Service;

void AddService(Service* serv, int number)
{
    Service* p = (Service*)malloc(sizeof(Service));
    p->serviceTime = rand() % 100;
    p->prev = serv;
    p->next = NULL;
    p->number = number;
    serv->next = p;
}

void BubbleSort(Service* serv)
{
    Service* temp = serv;
    Service* tempNext = temp->next;
    int tr = 1;
    while (tr)
    {
        tr = 0;

        while (serv->next)
        {

            if (serv->serviceTime > tempNext->serviceTime)
            {
                tr = 1;
                int tempST = serv->serviceTime;
                int tempNumber = serv->number;
                serv->serviceTime = tempNext->serviceTime;
                serv->number = tempNext->number;
                tempNext->serviceTime = tempST;
                tempNext->number = tempNumber;
            }

            serv = serv->next;
            tempNext = serv->next;
        }

        while (serv->prev)
        {
            serv = serv->prev;
        }
        tempNext = serv->next;
    }
}

int main()
{
    srand(time(NULL));
    int numberOfStructures = 0;
    int maxSum;
    Service* serv = (Service*)malloc(sizeof(Service));;
    serv->serviceTime = rand() % 100;
    serv->next = NULL;
    serv->prev = NULL;
    serv->number = 0;
    Service* first = serv;

    printf("Number of services n= ");
    scanf_s("%d", &numberOfStructures);
    printf("max. time in each service= ");
    scanf_s("%d", &maxSum);
    for (int i = 1; i < numberOfStructures; i++)
    {
        AddService(serv, i);
        serv = serv->next;
    }
    serv = first;

    while (serv)
    {
        printf("%d:%d  ", serv->number, serv->serviceTime);
        serv = serv->next;
    }
    serv = first;
    printf("\n\n");

    BubbleSort(serv);
    serv = first;

    while (serv)
    {
        printf("%d:%d  ", serv->number, serv->serviceTime);
        serv = serv->next;
    }

    serv = first;
    int servSum = 0;
    printf("\n");
    while (serv)
    {
        servSum += serv->serviceTime;
        if (servSum < maxSum)
        {
            printf("Number: %d\n", serv->number);
        }
        else
        {
            break;
        }
        serv = serv->next;
    }

    free(serv);
    return 0;
}
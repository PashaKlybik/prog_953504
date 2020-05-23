#include <stdlib.h>

#include "List.h"


DoubleLinkedList* CreateDblLinkedList()
{
    DoubleLinkedList* tmp = (DoubleLinkedList*)malloc(sizeof(DoubleLinkedList));
    tmp->size = 0;

    tmp->head = tmp->tail = NULL;

    return tmp;
}

void PushNode(DoubleLinkedList* list, int* arr, int arrSize, int treeNumber)
{
    Node* tmp = (Node*)malloc(sizeof(Node));
    if (tmp == NULL)
    {
        exit(3);
    }
    tmp->arr = arr;
    tmp->treeNumber = treeNumber;
    tmp->next = NULL;
    tmp->arrSize = arrSize;

    tmp->prev = list->tail;
    if (list->tail)
    {
        list->tail->next = tmp;
    }
    list->tail = tmp;

    if (list->head == NULL)
    {
        list->head = tmp;
    }
    list->size++;
}

void DeleteList(DoubleLinkedList* list)
{
    Node* item = list->head;
    Node* next;

    while (item != list->tail)
    {
        next = item->next;

        free(item);

        item = next;
    }

    free(item);
}
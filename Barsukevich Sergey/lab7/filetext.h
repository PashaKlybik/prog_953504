#ifndef FILETEXT_H_INCLUDED
#define FILETEXT_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>


typedef struct listnode
{
    struct listnode* next;
    char* data;
} ListNode;

typedef struct list
{
    ListNode* head;
    ListNode* tail;
    int size;
} List;

List* CreateList()
{
    List* list1 = /*(List*)*/malloc(sizeof(List));
    list1->head = list1->tail = NULL;
    list1->size = 0;
    return list1;
}

void ListPop(List* list1)
{
    if(list1->size == 0) return;
    ListNode* temp = list1->head;
    list1->size--;
    list1->head = temp->next;
    free(temp);
    if(list1->size == 0)
    {
        list1->head = list1->tail = NULL;
    }
}

void DeleteList(List* list1)
{
    while(list1->head != NULL)
    {
        ListPop(list1);
    }
}

char* ListGet(List* list1)
{
    return list1->head->data;
}

void ListPushBack(List* list1, char* data)
{
    ListNode* temp = malloc(sizeof(ListNode));
    temp->data = data;
    if(list1->tail != NULL)
    {
        list1->tail->next = temp;
    }
    else
    {
        list1->head = temp;
    }
    list1->tail = temp;
    list1->tail->next = NULL;
    list1->size++;
}

ListNode* ListGetNode(List* list1, int num)
{
    ListNode* temp;
    int i = 0;
    temp = list1->head;
    while (temp != NULL && i < num)
    {
        temp = temp->next;
        i++;
    }
    return temp;
}

void ListPrint(List* list1)
{
    ListNode* temp = list1->head;
    while(temp != NULL)
    {
        puts(temp->data);
        temp = temp->next;
    }
}

void ListPrintVers2(List* list1)
{
    ListNode* temp = list1->head;
    int i = 1;
    while(temp != NULL)
    {
        printf("%d) ", i); puts(temp->data);
        i++;
        temp = temp->next;
    }
}

#endif // FILETEXT_H_INCLUDED

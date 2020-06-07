#ifndef PAGELIST_H_INCLUDED
#define PAGELIST_H_INCLUDED

#include "Page.h"
#include "filetext.h"

typedef struct /*dlistnode*/onepage
{
    struct onepage* next;
   // struct onepage* prev;
    Page* data;
} onePage;

typedef struct pagelist
{
    onePage* head;
    onePage* tail;
    int size;
} PageList;


PageList* CreatePList()
{
    PageList* temp = (PageList*)malloc(sizeof(PageList));
    temp->head = temp->tail = NULL;
    temp->size = 0;
    return temp;
}

void PListPushBack(PageList* list1, Page* a)
{
    onePage* temp = (onePage*)malloc(sizeof(onePage));
    temp->data = a;
    temp->next = NULL;
    //temp->prev = list1->tail;
    if (list1->tail != NULL)
    {
        list1->tail->next = temp;
    }
    list1->tail = temp;
    if (list1->head == NULL)
    {
        list1->head = temp;
    }
    list1->size++;
}

void PListPop(PageList* list1)
{
    onePage* del = list1->head;
    list1->head = list1->head->next;
    /*if (list1->head != NULL)
    {
        list1->head->prev = NULL;
    }*/
    if (del == list1->tail)
    {
        list1->head = list1->tail = NULL;
    }
    DeleteArticle(del->data->article);
    DeleteComList(del->data->comments);
    DeleteCodeList(del->data->sourceCodes);
    free(del);
    list1->size--;
}

void DeletePList(PageList* list1)
{
    while(list1->head != NULL)
    {
        PListPop(list1);
    }
}

onePage* PListGet(PageList* list1, int num)
{
    onePage* temp;
    int i;
   /* if (num < list1->size/2)
    {
        i = 0;
        temp = list1->head;
        while (temp != NULL && i < num)
        {
            temp = temp->next;
            i++;
        }
    }
    else if(num < list1->size)
    {
        i = list1->size - 1;
        temp = list1->tail;
        while (temp != NULL && i > num)
        {
            temp = temp->prev;
            i--;
        }
    }*/
  i = 0;
    temp = list1->head;
        while (temp != NULL && i < num)
        {
            temp = temp->next;
            i++;
        }
    return temp;
}

void PListPrintPage(onePage* temp)
{
    printf("\t"); puts(temp->data->article->title);
    printf("Theme:\t\t"); puts(temp->data->article->theme);
    printf("Dated:\t\t"); puts(temp->data->article->date);
    printf("Languages: \t"); puts(temp->data->article->languages);

    puts("");
    ListPrint(temp->data->article->text);
    puts("\nSource:\n");

    CodeListPrint(temp->data->sourceCodes);
    printf("\nComments(%d):\n\n", temp->data->comments->size);
    ComListPrint(temp->data->comments);
}

void PListPrintPageWithoutComs(onePage* temp)
{
    printf("\t"); puts(temp->data->article->title);
    printf("Theme:\t\t"); puts(temp->data->article->theme);
    printf("Dated:\t\t"); puts(temp->data->article->date);
    printf("Languages: \t"); puts(temp->data->article->languages);

    puts("");
    ListPrint(temp->data->article->text);
    puts("\nSource:\n");

    CodeListPrint(temp->data->sourceCodes);
}

#endif // PAGELIST_H_INCLUDED

#ifndef SOURCECODELIST_H_INCLUDED
#define SOURCECODELIST_H_INCLUDED

#include "filetext.h"
typedef struct articlecode
{
    char* title;
    char* language;
    List* code;
} SourceCode;

SourceCode* CreateArticleCode()
{
    SourceCode* temp = (SourceCode*)malloc(sizeof(SourceCode));
    temp->code = CreateList();
    return temp;
}

void DeleteArticleCode(SourceCode* temp)
{
    DeleteList(temp->code);
    free(temp->title);
    free(temp->language);
    free(temp);
}

typedef struct codelistobj
{
    struct codelistobj* next;
    SourceCode* data;
} CodeListNode;

typedef struct codelist
{
    CodeListNode* head;
    CodeListNode* tail;
    int size;
} CodeList;

CodeList* CreateCodeList()
{
    CodeList* list1 = malloc(sizeof(CodeList));
    list1->head = list1->tail = NULL;
    list1->size = 0;
    return list1;
}

void CodeListPop(CodeList* list1)
{
    if(list1->size == 0) return;
    CodeListNode* temp = list1->head;
    list1->size--;
    list1->head = temp->next;
    DeleteArticleCode(temp->data);
    free(temp);
    if(list1->size == 0)
    {
        list1->head = list1->tail = NULL;
    }
}

void DeleteCodeList(CodeList* list1)
{
    while(list1->head != NULL)
    {
        CodeListPop(list1);
    }
}

void CodeListPushBack(CodeList* list1, SourceCode* data)
{
    CodeListNode* temp = malloc(sizeof(CodeListNode));
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

void CodeListPrint(CodeList* list1)
{
    CodeListNode* temp = list1->head;
    while(temp != NULL)
    {
        fputs(temp->data->language, stdout); puts(":");
        ListPrint(temp->data->code);
        temp = temp->next;
    }
}

#endif // SOURCECODELIST_H_INCLUDED

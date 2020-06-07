#ifndef COMMENTSLIST_H_INCLUDED
#define COMMENTSLIST_H_INCLUDED

#include "comment.h"

typedef struct commentlistone
{
    Comment* data;
    struct commentlistone* next;

} CommentListNode;

typedef struct commentlist
{
    CommentListNode* head;
    CommentListNode* tail;
    int size;
} CommentList;

CommentList* CreateComList()
{
    CommentList* list1 = malloc(sizeof(CommentList));
    list1->head = list1->tail = NULL;
    list1->size = 0;
    return list1;
}

void ComListPop(CommentList* list1)
{
    if(list1->size == 0) return;
    CommentListNode* temp = list1->head;
    list1->size--;
    list1->head = temp->next;
    DeleteCom(temp->data);
    free(temp);
    if(list1->size == 0)
    {
        list1->head = list1->tail = NULL;
    }
}

void DeleteComList(CommentList* list1)
{
    while(list1->head != NULL)
    {
        ComListPop(list1);
    }
}

void ComListPushBack(CommentList* list1, Comment* data)
{
    CommentListNode* temp = malloc(sizeof(CommentListNode));
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

CommentListNode* ComListGetNode(CommentList* list1, int num)
{
    CommentListNode* temp;
    int i = 0;
    temp = list1->head;
    while (temp != NULL && i < num)
    {
        temp = temp->next;
        i++;
    }
    return temp;
}

void ComListPrint(CommentList* list1)
{
    CommentListNode* temp = list1->head;
    int i=0;
    while(temp != NULL)
    {
        printf("#%d ", i++); fputs(temp->data->userNick, stdout); puts(" wrote:\n");
        ListPrint(temp->data->content);
        puts("\n");
        temp = temp->next;
    }
}

#endif // COMMENTSLIST_H_INCLUDED

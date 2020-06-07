#ifndef COMMENT_H_INCLUDED
#define COMMENT_H_INCLUDED

#include "filetext.h"

typedef struct comment
{
    char* title;
    char* userNick;
    List* content;
} Comment;

void DeleteCom(Comment* temp)
{
    DeleteList(temp->content);
    free(temp->userNick);
    free(temp->title);
    free(temp);
}

Comment* CreateCom()
{
    Comment* temp = (Comment*)malloc(sizeof(Comment));
    temp->content = CreateList();
    return temp;
}

#endif // COMMENT_H_INCLUDED

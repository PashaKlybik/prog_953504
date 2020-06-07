#ifndef PROGARTICLE_H_INCLUDED
#define PROGARTICLE_H_INCLUDED

#include "filetext.h"

typedef struct article
{
    char* title;
    char* theme;
    char* date;
    char* languages;
    List* text;
} Article;

Article* CreateArticle()
{
    Article* temp = (Article*)malloc(sizeof(Article));
    temp->text = CreateList();
    return temp;
}

void DeleteArticle(Article* temp)
{
    DeleteList(temp->text);
    free(temp->title);
    free(temp->theme);
    free(temp->date);
    free(temp->languages);
}

#endif // PROGARTICLE_H_INCLUDED

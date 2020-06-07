#ifndef PAGE_H_INCLUDED
#define PAGE_H_INCLUDED

#include "progarticle.h"
#include "sourcecodelist.h"
#include "commentslist.h"

typedef struct page
{
    Article* article;
    CodeList* sourceCodes;
    CommentList* comments;
} Page;

Page* CreatePage()
{
    Page* temp = (Page*)malloc(sizeof(Page));
    temp->article = (Article*)malloc(sizeof(Article));
    temp->sourceCodes = CreateCodeList();
    temp->comments = CreateComList();
    return temp;
}

#endif // PAGE_H_INCLUDED

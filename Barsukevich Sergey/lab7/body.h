#ifndef BODY_H_INCLUDED
#define BODY_H_INCLUDED

#include "filetext.h"
#include "progarticle.h"
#include "Page.h"
#include "pagelist.h"
#include "sourcecodelist.h"
#include "comment.h"
#include "commentslist.h"

void LoadArticles(PageList* pagelists)
{
    int stringSize = 50;
    char* str = (char*)malloc(stringSize*sizeof(char));
    FILE* fp = fopen("articles.txt", "r");
    int i = 0;
    Page* thispage;
    List* temp = CreateList();

    while (!feof(fp))
    {
        fscanf(fp,"%c",&str[i]);
        if(str[i] == '\n' || feof(fp))
        {
            str[i] = '\0';
            if((strlen(str) == 2 && str[0] == '$' && str[1] == '$') || feof(fp))
            {
                if(feof(fp))
                {
                    ListPushBack(temp, str);
                }
                thispage = CreatePage();
                thispage->article->title = strdup(ListGet(temp));
                ListPop(temp);
                thispage->article->theme = strdup(ListGet(temp));
                ListPop(temp);
                thispage->article->date = strdup(ListGet(temp));
                ListPop(temp);
                thispage->article->languages = strdup(ListGet(temp));
                ListPop(temp);
                thispage->article->text = temp;
                PListPushBack(pagelists, thispage);
                temp = CreateList();
                str = (char*)malloc(stringSize*sizeof(char));
                i = 0;
                continue;
            }
            str = (char*)realloc(str, (i+1)*sizeof(char));
            ListPushBack(temp, str);
            str = (char*)malloc(stringSize*sizeof(char));
            i = 0;
            continue;
        }
        i++;
        if(i>=stringSize)
        {
            stringSize*=2;
            str = (char*)realloc(str, stringSize*sizeof(char));
        }
    }
    fclose(fp);
    free(str);
}

void LoadSourceCodes(PageList* pagelists)
{
    int stringSize = 50;
    char* str = (char*)malloc(stringSize*sizeof(char));
    FILE* fp = fopen("source.txt", "r");
    int i = 0;
    SourceCode* codepage;
    List* temp = CreateList();
    while (!feof(fp))
    {
        fscanf(fp,"%c",&str[i]);
        if(str[i] == '\n' || feof(fp))
        {
            str[i] = '\0';
            if((strlen(str) == 2 && str[0] == '$' && str[1] == '$') || feof(fp))
            {
                if(feof(fp))
                {
                    ListPushBack(temp, str);
                }
                onePage* pos = pagelists->head;
                while(pos != NULL)
                {
                    if(strcmp(pos->data->article->title,ListGet(temp)) == 0) break;
                    pos = pos->next;
                }
                if(pos != NULL)
                {
                    codepage = CreateArticleCode();
                    codepage->title = strdup(ListGet(temp));
                    ListGet(temp);
                    codepage->language = strdup(ListGet(temp));
                    ListGet(temp);
                    codepage->code = temp;
                    CodeListPushBack(pos->data->sourceCodes, codepage);
                }
                temp = CreateList();
                str = (char*)malloc(stringSize*sizeof(char));
                i = 0;
                continue;
            }
            str = (char*)realloc(str, (i+1)*sizeof(char));
            ListPushBack(temp, str);
            str = (char*)malloc(stringSize*sizeof(char));
            i = 0;
            continue;
        }
        i++;
        if(i>=stringSize)
        {
            stringSize*=2;
            str = (char*)realloc(str, stringSize*sizeof(char));
        }
    }
    fclose(fp);
    free(str);
}

void LoadComments(PageList* comlist)
{
    int strSize = 50;
    char* str = (char*)malloc(strSize*sizeof(char));
    FILE* fp = fopen("comma.txt", "r");
    int i = 0;
    Comment* thiscomment;
    List* temp = CreateList();
    while (!feof(fp))
    {
        fscanf(fp,"%c",&str[i]);
        if(str[i] == '\n' || feof(fp))
        {
            str[i] = '\0';
            if((strlen(str) == 2 && str[0] == '$' && str[1] == '$') || feof(fp))
            {
                if(feof(fp))
                {
                    ListPushBack(temp, str);
                }
                onePage* pos = comlist->head;
                while(pos != NULL)
                {
                    if(strcmp(pos->data->article->title,ListGet(temp)) == 0) break;
                    pos = pos->next;
                }
                if(pos != NULL)
                {
                    thiscomment = CreateCom();
                    thiscomment->title = strdup(ListGet(temp));
                    ListPop(temp);
                    thiscomment->userNick = strdup(ListGet(temp));
                    ListPop(temp);
                    thiscomment->content = temp;
                    ComListPushBack(pos->data->comments, thiscomment);
                }
                temp = CreateList();
                str = (char*)malloc(strSize*sizeof(char));
                i = 0;
                continue;
            }
            str = (char*)realloc(str, (i+1)*sizeof(char));
            ListPushBack(temp, str);
            str = (char*)malloc(strSize*sizeof(char));
            i = 0;
            continue;
        }
        i++;
        if(i>=strSize)
        {
            strSize*=2;
            str = (char*)realloc(str, strSize*sizeof(char));
        }
    }
    fclose(fp);
    free(str);
}

#endif // BODY_H_INCLUDED

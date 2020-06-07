#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include "body.h"
#include <stdbool.h>
bool IsNumber(char* str);
/*{
    int i;
    if(strlen(str) == 0) return false;
    for(i=0; i<strlen(str); i++)
    {
        if(!isdigit(str[i])) return false;
    }
    return true;
}*/

int main()
{
    system("chcp 1251");
    system("cls");
    PageList* collection = CreatePList();
    LoadArticles(collection);
    LoadSourceCodes(collection);
    LoadComments(collection);
    char choice;
    char* t;
    while(true)
    {
        printf("1. Выбор статьи с комментариями.\n");
        printf("2. Поиск статьи по тематике. \n");
        printf("3. Выход.\n");
        choice = getchar();
        system("cls");
        if(choice == '1' || choice == 97)
        {
            puts("Выберите статью:");
            onePage* temp = collection->head;
            int i = 1;
            while(temp != NULL)
            {
                printf("%d) ", i); puts(temp->data->article->title);
                i++;
                temp = temp->next;
            }
            int num = -1;
            printf("Введите номер  статьи: ");
            char* tt = (char*)malloc(10);
                fgets(tt,5,stdin);
                free(tt);
            while(num<1 || num>(collection->size))
            {
                t = (char*)malloc(10);
                fgets(t,5,stdin);
                t[strlen(t)-1] = '\0';

                if(IsNumber(t))
                {
                    num = atoi(t);
                    if(num>=1 && num<= collection->size)
                    {
                        free(t);
                        break;
                    }
                    else;
                }
              else   printf("\nОшибка при вводе. Повторите снова: ");
            }
            free(t);
            system("cls");
            PListPrintPage(PListGet(collection, num-1));
            puts("1. Добавить комментарий");
            puts("2. Изменить комментарий");
            char r = getch();
            if(r == '1' || r == 97)
            {
                Comment* cm = CreateCom();
                printf("Добавление нового комментария...\n");
                cm->title = strdup(PListGet(collection, num-1)->data->article->title);
                char* string = (char*)malloc(100);
                printf("Введите имя пользователя: ");
                fgets(string,100,stdin);
                string[strlen(string)-1] = '\0';
                cm->userNick = strdup(string);
                printf("Введите комментарий: ");
                fgets(string,100,stdin);
                ListPushBack(cm->content, string);
                ComListPushBack(PListGet(collection,num-1)->data->comments, cm);
            }
            else if(r == '2' || r == 98)
            {
                int k=-1, curr=0;
                printf("Введите номер комментария: ");
                scanf("%d",&k);
                CommentListNode* edit = PListGet(collection, num-1)->data->comments->head;
                while(edit != NULL && curr != k)
                {
                    edit = edit->next;
                    curr++;
                }

                puts("1. Изменить ник комментатора");
                puts("2. Изменить комментарий");
                char w = getch();
                char y;
                if(w == '1' || w == 97)
                {
                    scanf("%c", &y);
                    char* string = (char*)malloc(100);
                    printf("Enter user: ");
                    fgets(string,100,stdin);

                    string[strlen(string)-1] = '\0';
                    puts(string);
                    edit->data->userNick = strdup(string);
                }
                else if(w == '2' || w == 98)
                {
                    char* string = (char*)malloc(100);
                    char litter = scanf("%c", &litter);
                    printf("Enter message: ");
                    fgets(string,100,stdin);
                    string[strlen(string)-1] = '\0';
                    while(edit->data->content->head != NULL)
                    {
                        ListPop(edit->data->content);
                    }
                    ListPushBack(edit->data->content, string);
                }
                else
                {
                    continue;
                }
            }
            getch();
        }
        else if(choice == '2' || choice == 98)
        {
            List* temp = CreateList();
            onePage* tempu = collection->head;
            char* tt = (char*)malloc(10);
                fgets(tt,5,stdin);
                free(tt);
            while(tempu != NULL)
            {
                if(temp->size == 0) ListPushBack(temp,strdup(tempu->data->article->theme));
                int counter = 0;
                ListNode* start = temp->head;
                while(start != NULL)
                {
                    if(strcmp(tempu->data->article->theme, start->data) == 0) counter++;
                    start = start->next;
                }
                if(counter == 0) ListPushBack(temp,strdup(tempu->data->article->theme));
                tempu = tempu->next;
            }
            puts("Список тем по статьям:");
            ListPrintVers2(temp);
            printf("\nВыберите одну из них: ");
            int themenum = 0;
            while(themenum<1 || themenum>(temp->size))
            {
                t = (char*)malloc(10);
                fgets(t,5,stdin);
                t[strlen(t)-1] = '\0';
                if(IsNumber(t))
                {
                    themenum = atoi(t);
                    if(themenum>=1 && themenum<= (temp->size))
                    {
                        free(t);
                        break;
                    }
                }
                printf("\nОшибка ввода. Повторите снова: ");
            }
            free(t);
            tempu = collection->head;
            List* themeTop = CreateList();
            while(tempu != NULL)
            {
                if(strcmp(tempu->data->article->theme, ListGetNode(temp,themenum-1)->data) == 0)
                {
                    ListPushBack(themeTop, tempu->data->article->title);
                }
                tempu = tempu->next;
            }
            puts("\nСписок статей по  теме:");
            ListPrintVers2(themeTop);
            printf("\nВыберите статью: ");
            int k1 = 0;
            while(k1<1 || k1>(themeTop->size))
            {
                t = (char*)malloc(10);
                fgets(t,5,stdin);
                t[strlen(t)-1] = '\0';
                if(IsNumber(t))
                {
                    k1 = atoi(t);
                    if(k1>=1 && k1<= (themeTop->size))
                    {
                        free(t);
                        break;
                    }
                }
                printf("\nОшибка ввода. Повторите снова: ");
            }
            tempu = collection->head;
            while(tempu != NULL)
            {
                if(strcmp(tempu->data->article->title,ListGetNode(themeTop,k1-1)->data) == 0) break;
                tempu = tempu->next;
            }
            system("cls");
            //PListPrintPage(tempu);
            PListPrintPageWithoutComs(tempu);
            getch();
        }
        else if(choice == '3' || choice == 99)
        {
            FILE* fp = fopen("comma.txt", "w");
            onePage* tempu = collection->head;
            while(tempu != NULL)
            {
                CommentListNode* k = tempu->data->comments->head;
                while(k != NULL)
                {
                    fputs(k->data->title,fp); fputs("\n",fp);
                    fputs(k->data->userNick,fp);  fputs("\n",fp);
                    ListNode* w = k->data->content->head;
                    while(w != NULL)
                    {
                        fputs(w->data,fp); fputs("\n", fp);
                        w = w->next;
                    }
                    fputs("$$\n",fp);
                    k = k->next;
                }
                tempu= tempu->next;
            }
            DeletePList(collection);
            break;
        }
        system("cls");
    }
    return 0;
}
bool IsNumber(char* str)
{
    int i;
    if(strlen(str) == 0) return false;
    for(i=0; i<strlen(str); i++)
    {
        if(!isdigit(str[i])) return false;
    }
    return true;
}

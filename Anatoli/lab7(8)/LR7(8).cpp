//#include "stdafx.h"
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <malloc.h>
#include <conio.h>
using namespace std;
//==============================================
struct list
{
    int num;
    char code[10];
    char name[35];
    double price; // поле данных
    struct list* next; // указатель на следующий элемент
    struct list* prev; // указатель на предыдущий элемент
};
struct DiscountList
{
    char number[10];
    int discount;
    struct DiscountList* next;
    struct DiscountList* prev;
};
int tmp = 0, tmp2 = 0;
struct list* init(list* lst, char price[], char code[], char name[]);
struct DiscountList* init(DiscountList* lst, char number[], char disc[]);
struct list* addelem(list* lst, char price[], char code[], char name[]);
struct DiscountList* addelem(DiscountList* lst, char number[], char disc[]);
void listprint(list* lst);
void listprint(DiscountList* lst);
double searchItme(list* lst, char code[]);
char* searchItmeName(list* lst, char code[]);
int main()
{
    //                       OPEN ITEMS BASE
    FILE* f = fopen("C:\\143\\GoodsBase.txt", "a+");
    if (f == NULL)
    {
        cout << "Error";
        _getch();
        return 0;
    }
    int k = 0;
    struct list* items;
    items = (struct list*)malloc(sizeof(struct list));

    while (!feof(f))
    {
        char fprice[10], fcode[20], fname[25], tmp2[100];
        fgets(tmp2, 30, f);
        if (NULL != fgets(fname, 30, f)) {}
        if (NULL != fgets(fcode, 20, f)) {}
        if (NULL != fgets(fprice, 20, f)) {}
        if (k == 0)
        {
            items = init(items, fprice, fcode, fname);
            k++;
        }
        else
        {
            items = addelem(items, fprice, fcode, fname);
        }
    }
    fclose(f);
    double purchaseSum = 0;
    char purchaseList[10][100];
    ::tmp = 0;
    while (1)
    {
        cout << "Enter item's code:" << '\n';
        char code[10];
        cin >> code;

        if (strcmp(code, "0") == 0) break;
        else if (searchItme(items, code) != 0)
        {
            double tmp = searchItme(items, code);
            int amount = 0;
            cout << "Amount: ";
            char stringAmount[3];
            cin >> stringAmount;
            if (strcmp(stringAmount, "0") == 0)
                break;
            else if (stringAmount[0] == '\n' || strcmp(stringAmount, "\n") == 0)
            {
                amount = 1;
            }
            else if (atoi(stringAmount) != 0 && atoi(stringAmount) >= 1)
            {
                amount = atoi(stringAmount);
            }
            else
            {
                cout << "Incorrect value" << "\n";
                continue;
            }
            purchaseSum += tmp * amount;
            char infoItem[70];
            char get[35];
            strcpy(get, searchItmeName(items, code));
            strcpy(infoItem, get);
            strncat(infoItem, "________________", 18);
            char string[50];
            sprintf(string, "%f", tmp);
            strncat(infoItem, string, 5);
            strcat(infoItem, " x ");
            strncat(infoItem, stringAmount, 5);
            strcpy(purchaseList[::tmp++], infoItem);
        }
        else cout << "No such item" << "\n";
    }
    cout << "Sum of your purchase is  " << purchaseSum << '\n';
    cout << "Do you have dicount card? Yes - 1, No - 2" << '\n';
    int answer = 0;
    cin >> answer;
    if (answer == 1)
    {
        //                       OPEN DISCOUNT BASE
        while (1)
        {
            FILE* fin = fopen("C:\\143\\DiscountCards.txt", "a+");
            if (fin == NULL)
            {
                cout << "Error";
                _getch();
                return 0;
            }
            cout << "Your card code: ";
            char cardCode[10];
            cin >> cardCode;
            if (strcmp(cardCode, "0") == 0)
            {
                break;
            }
            struct DiscountList* cards;
            cards = (struct DiscountList*)malloc(sizeof(DiscountList));
            int flag = 0;
            while (!feof(fin))
            {
                char fnumber[10], fdiscount[5], tmp2[100];
                fgets(tmp2, 30, fin);
                if (NULL != fgets(fnumber, 30, fin)) {}
                if (NULL != fgets(fdiscount, 30, fin)) {}
                fnumber[strlen(fnumber) - 1] = '\0';
                if (strcmp(cardCode, fnumber) == 0)
                {
                    int a = atoi(fdiscount);
                    double b = (100 - (double)a) / 100;
                    purchaseSum *= b;
                    cout << "Sum of your purchase is  " << purchaseSum;
                    flag = 1;
                    break;
                }
                if (feof(fin))
                {
                    cout << "Incorrect input" << '\n';
                }
            }
            if (flag == 1)
                break;
            fclose(fin);
        }
        // listprint(cards);
    }
    else if (answer == 2) 
    {
        cout << "Sum of your purchase is  " << purchaseSum;
    }
    FILE* fn = fopen("C:\\143\\HistoryOfPurchases.txt", "a");
    if (fn == NULL)
    {
        cout << "Error";
        _getch();
        return 0;
    }
    {
        for (int i = 0; i < tmp; i++)
        {
            fprintf(fn, "\n%s", purchaseList[i]);
        }
        fprintf(fn, "\nSum of the purchase: %f", purchaseSum);
        fprintf(fn, "\n                     Good Luck!");
        fprintf(fn, "\n==================================================================");
    }
    fclose(fn);
    return 0;
}
double searchItme(list* lst, char code[])
{
    struct list* p;
    p = lst;
    do
    {
        char tmp[10];
        strcpy(tmp, p->code);
        tmp[strlen(p->code) - 1] = '\0';
        if (strcmp(tmp, code) == 0)
            return p->price;
        p = p->prev; // переход к следующему узлу
    } while (p != NULL); // условие окончания обхода
    return 0;
}
char* searchItmeName(list* lst, char code[])
{
    struct list* p;
    p = lst;
    do
    {
        char tmp[10];
        strcpy(tmp, p->code);
        tmp[strlen(p->code) - 1] = '\0';
        if (strcmp(tmp, code) == 0)
        {
            p->name[strlen(p->name) - 1] = '\0';
            return p->name;
        }
        p = p->prev; // переход к следующему узлу
    } while (p != NULL); // условие окончания обхода
    return 0;
}
struct list* init(list* lst, char price[], char code[], char name[])
{
    lst->num = tmp++;
    strcpy(lst->code, code);
    strcpy(lst->name, name);
    double price1 = strtod(price, NULL);
    lst->price = price1;
    lst->next = NULL; // указатель на следующий узел
    lst->prev = NULL; // указатель на предыдущий узел
    return(lst);
}
struct DiscountList* init(DiscountList* lst, char number[], char disc[])
{
    strcpy(lst->number, number);
    int disc2 = atoi(disc);
    lst->discount = disc2;
    lst->next = NULL; // указатель на следующий узел
    lst->prev = NULL; // указатель на предыдущий узел
    return(lst);
}
struct list* addelem(list* lst, char price[], char code[], char name[])
{
    struct list* temp, * p;
    temp = (struct list*)malloc(sizeof(list));
    p = lst->next; // сохранение указателя на следующий узел
    lst->next = temp; // предыдущий узел указывает на создаваемый
    temp->num = tmp++;
    strcpy(temp->code, code);
    strcpy(temp->name, name);
    double price1 = strtod(price, NULL);
    temp->price = price1; // сохранение поля данных добавляемого узла
    temp->next = p; // созданный узел указывает на следующий узел
    temp->prev = lst; // созданный узел указывает на предыдущий узел
    if (p != NULL)
        p->prev = temp;
    return(temp);
}
struct DiscountList* addelem(DiscountList* lst, char number[], char disc[])
{
    struct DiscountList* temp, * p;
    temp = (struct DiscountList*)malloc(sizeof(DiscountList));
    p = lst->next; // сохранение указателя на следующий узел
    lst->next = temp; // предыдущий узел указывает на создаваемый
    int disc2 = atoi(disc);
    temp->discount = disc2;
    strcpy(temp->number, number);
    temp->next = p; // созданный узел указывает на следующий узел
    temp->prev = lst; // созданный узел указывает на предыдущий узел
    if (p != NULL)
        p->prev = temp;
    return(temp);
}
void listprint(list* lst)
{
    struct list* p;
    p = lst;
    do
    {
        cout << p->name << "Price: " << p->price << "$" << '\n' << "Code: " << p->code << "===============================================" << '\n';
        p = p->prev; // переход к следующему узлу
    } while (p != NULL); // условие окончания обхода
}
void listprint(DiscountList* lst)
{
    struct DiscountList* p;
    p = lst;
    do
    {
        cout << p->number<< "===============================================" << '\n';
        p = p->prev; // переход к следующему узлу
    } while (p != NULL); // условие окончания обхода
}

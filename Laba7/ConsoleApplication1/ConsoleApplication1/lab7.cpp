#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include "book.h"
#include "menu.h"

int main()
{
    ListBook* lst = read_books(1);
    while (true)
    {
        Menu();
        int choice = check_borders(0, 14);
        switch (choice)
        {
        case 1:
            make_order(lst);
            system("pause");
            system("cls");
            break;
        case 2:
            add_to_book_list(lst, add_book());
            lst->size++;
            system("cls");
            break;
        case 3:
            print_info(lst);
            system("pause");
            system("cls");
            break;
        case 0:
            delete_book_list(lst);
            return 0;
        }
    }
}


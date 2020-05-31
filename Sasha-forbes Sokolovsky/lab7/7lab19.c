#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include "7lab19.h"



int main(void)
{        
    struct contact *cont = NULL;
    
    while (1)
    {                        
        struct date dt;        
        system("cls");
        get_current_date(&dt);
        show_date(dt);
        printf("1.contacts\n");
        printf("2.notifications\n");    
        printf("3.exit\n");
        
        fflush(stdin);
        char c;
        scanf("%c", &c);

        switch (c)
        {
            case '1':
                contact_menu(&cont);
                break;
            case '2':
                notifications(cont);
                break;
            case '3':
                free_contact(cont);                            
                return 0;           
            default:
                printf("\nplease input number from 1 to 3\npress any key to continue");
                getch();
        }
    }    
}
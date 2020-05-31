#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>

#define uint64_t unsigned long long int

struct date
{
    int day;
    int mon;
    int year;
};
/* compare date */
int compare_date(const struct date fir, const struct date sec)
{
    if (fir.year == sec.year)
    {
        if (fir.mon == sec.mon)
        {
            return fir.day - sec.day;
        }
        else
        {
            return fir.mon - sec.mon;
        }
    }
    else
    {
        return fir.year - sec.year;
    }
}
/* struct date get current year, mo, day */
void get_current_date(struct date *dt)
{
    time_t timer = time(NULL);
    struct tm *current_date = localtime(&timer);        
    dt->year = current_date->tm_year + 1900;
    dt->mon = current_date->tm_mon + 1;
    dt->day = current_date->tm_mday;        
}
/* safe uint64_t input in diaposone[min,max] */
uint64_t input(const uint64_t min, const uint64_t max)
{
	int temp = 0;
	uint64_t res;
	do
	{	
		temp = scanf("%d", &res);
		
        if (temp != 1)
		{
			temp = 0;
			printf("input error\n");
			while (getchar() != '\n');
		}
        else
        {
            if (res >= min && res <= max)
            {
                break;
            }
            else
            {
                printf("input error\n");
                temp = 0;                
            }            
        }
	}
	while (temp != 1);
    
	return res;
}
/* print date */
void show_date(const struct date t)
{
    printf("date: %d.%d.%d\n", t.day, t.mon, t.year);
}

struct event
{        
    char title[30];
    uint64_t duration_min;
    char place[30];
    struct date dt;    
    char note[100];
    struct event *next;
};

struct event *get_event_node(struct event *ev, int index)
{
    if (!ev)
    {        
        return NULL;
    }
    struct event *temp = ev;
    
    int i;    
    for (i  = 0; i < index; i++)
    {
        temp = temp->next;
    }
    return temp;
}

void change_event_information(struct event **ev)
{
    while (1)
    {
        struct date dt;
        system("cls");        
        printf("title: %s\n", (*ev)->title);
        printf("select what to change\n");
        printf("1.duration\n");
        printf("2.place\n");
        printf("3.data\n");        
        printf("4.note\n");
        printf("5.title\n");
        printf("6.go back\n");
        
        fflush(stdin);
        char c;
        scanf("%c", &c);        

        switch (c)
        {
            case '1':
                system("cls");
                printf("duration(min): ");
                (*ev)->duration_min = input(0, 10000000000);
                break;
            case '2':
                system("cls");
                fflush(stdin);
                printf("place: ");
                fgets((*ev)->place, 30, stdin);
                break;
            case '3':
                system("cls");
                printf("use only number\n");
                printf("day: ");
                (*ev)->dt.day = input(1, 31);
                printf("month: ");
                (*ev)->dt.mon = input(1, 12);                
                printf("year: ");
                (*ev)->dt.year = input(2020, 3020);                                       
                break;            
            case '4':
                system("cls");
                fflush(stdin);
                printf("note: ");
                fgets((*ev)->note, 100, stdin);
                break;
            case '5':
                system("cls");
                fflush(stdin);
                printf("new title: ");
                fgets((*ev)->title, 30, stdin);
                break;
            case '6':                                                                
                get_current_date(&dt);                
                if (compare_date(dt, (*ev)->dt) > 0)
                {
                    printf("date assignment is onle possible for the future or present\n");
                    printf("press any key to continue with current time\n");
                    get_current_date(&((*ev))->dt);            
                }                
                return;                         
        }                
    }
}

void sort_event(struct event *ev)
{        
    struct event *first = ev;
    struct event *second = ev->next;     
    
    while (first->next)
    {      
        while (second)
        {   
            if (compare_date(first->dt, second->dt) > 0)
            {       
                struct event *temp = first;             
                first = second;
                second = temp;
            }
            second = second->next;                
        }
        first = first->next;
        second = first->next;                        
    }
}

void print_events(struct event **ev)
{   
    if (!(*ev))
    {    
        printf("is empty\n");
        return;    
    }
    sort_event(*ev);

    while (1)
    {
        system("cls");
        printf("select event:\n");
        int leng = 1;        
        struct event *temp = (*ev);                        
        
        while (temp)
        {
            printf("%d.%s", leng++, temp->title);
            temp = temp->next;            
        }
        printf("%d.go back\n", leng);        
        int id = input(1, leng);
        
        if (id == leng)
        {
            return;
        }
        if (id > 0 && id < leng)
        {
            system("cls");
            id--;
            struct event *p = get_event_node((*ev), id);
            printf("title: %s", p->title);
            printf("duration(min): %d\n", p->duration_min);
            printf("place: %s\n", p->place);                
            show_date(p->dt);
            printf("note: %s", p->note);        
            printf("\nchange?(y- yes, n - no)\n");
        
            while (1)
            {                
                fflush(stdin);
                char c;
                scanf("%c", &c);
        
                switch (c)
                {
                    case 'y':
                        change_event_information(&p);
                        break;
                    case 'n':                    
                        break;
                    default:
                        printf("no such varient\n");
                        continue;
                }
                break;
            }
        }    
        else
        {
            printf("no such variant");
        }       
    }
}

void add_event(struct event **ev)
{        
    struct event *temp = NULL;      
   
    if (!(temp = (struct event*)malloc(sizeof(struct event))))
    {
        printf("not enought memory. goodbye");
        exit(1);
    }
    fflush(stdin);
    printf("title: ");    
    fgets(temp->title, 30, stdin);   
    get_current_date(&temp->dt);
    temp->place[0] = '\0';        
    temp->note[0] = '\0';                
    temp->next = NULL;
    change_event_information(&temp);     
    
    if (!(*ev))
    {
        (*ev) = temp;        
    }
    else
    {        
        temp->next = (*ev);  
        (*ev) = temp;
    }    
}

void delete_event(struct event **ev)
{
    if (!(*ev))
    {    
        printf("is empty\n");
        return;    
    }
    while (1)
    {
        system("cls");
        printf("select event:\n");        
        int leng = 1;        
        struct event *temp = (*ev);                
        
        while (temp)
        {
            printf("%d.%s", leng++, temp->title);
            temp = temp->next;            
        }
        printf("%d.go back\n", leng);        
        int id = input(1, leng);        
        
        if (id == leng)
        {
            return;
        }
        if (id > 0 && id < leng)
        {            
            printf("are you sure?(y - yes, n - no)\n");
        
            while (1)
            {
                struct event *p = NULL;
        
                fflush(stdin);
                char c;
                scanf("%c", &c);
        
                switch (c)
                {
                    case 'y':         
                        if (id == 1)                                       
                        {
                            p = *ev;
                            *ev = (*ev)->next;
                            free(p);
                        }
                        else
                        {
                            p = get_event_node(*ev, id - 2);                   
                            struct event *pn = p->next;
                            p->next = p->next->next;       
                            free(pn);                     
                        }                        
                        break;
                    case 'n':                    
                        break;;
                    default:
                        printf("no such varient");
                        continue;
                }             
                break;   
            }
        }
    }
}

void event_menu(struct event **ev)
{    
    while (1)
    {
        system("cls");        
        printf("1.show events\n");
        printf("2.add event\n");    
        printf("3.delete event\n");
        printf("4.go back\n");        
        
        fflush(stdin);
        char c;
        scanf("%c", &c);
     
        switch (c)
        {
            case '1':
                print_events(ev);
                break;
            case '2':
                add_event(ev);
                break;
            case '3':
                delete_event(ev);
                break;
            case '4':
                return;                
            default:
                printf("please input number from 1 to 4\npree any key to continue");
        }
    }
}

struct contact 
{        
    char second_name[20];
    char first_name[20];    
    char work_place[30];
    uint64_t telephone_number;
    struct date birthday;    
    struct event (*ev);
    struct contact *next;
};

struct contact *get_contact_node(struct contact *cont, int index)
{
    if (!cont)
    {        
        return NULL;
    }
    struct contact *temp = cont;
    
    int i;    
    for (i  = 0; i < index; i++)
    {
        temp = temp->next;
    }
    return temp;
}

void change_contact_information(struct contact **cont)
{    
    while (1)
    {        
        system("cls");
        printf("%s%s\n", (*cont)->second_name, (*cont)->first_name);
        printf("select what to change\n");
        printf("1.second and first name\n");
        printf("2.telephone number\n");
        printf("3.work place\n");
        printf("4.birthday\n");        
        printf("5.events\n");
        printf("6.go back\n");
        
        fflush(stdin);
        char c;
        scanf("%c", &c);
      
        switch (c)
        {
            case '1':
                system("cls");
                fflush(stdin);
                printf("second name: ");
                fgets((*cont)->second_name, 20, stdin);
                fflush(stdin);
                printf("\nfirst name: ");
                fgets((*cont)->first_name, 20, stdin);
                break;
            case '2':
                system("cls");                
                printf("telephone number: +");
                (*cont)->telephone_number = input(0, 100000000000000);
                break;
            case '3':
                system("cls");
                fflush(stdin);
                printf("work place: ");
                fgets((*cont)->work_place, 30, stdin);                     
                break;
            case '4':
                system("cls");
                printf("use only number\n");
                printf("day: ");
                (*cont)->birthday.day = input(1, 31);
                printf("month: ");
                (*cont)->birthday.mon = input(1, 12);                
                printf("year: ");
                (*cont)->birthday.year = input(0, 3020);                                
                break;            
            case '5':
                event_menu(&(*cont)->ev);
                break;
            case '6':                
                return;                 
            default:
                system("cls");
                printf("no such varient\npress any key to conitue");
                break;        
        }                
    }
}

void print_contacts(struct contact **cont)
{
    if (!(*cont))
    {    
        printf("is empty\n");
        return;    
    }    

    while (1)
    {
        system("cls");
        printf("select event:\n");
        int leng = 1;        
        struct contact *temp = (*cont);                        
        
        while (temp)
        {
            printf("%d.%s  %s", leng++, temp->second_name, temp->first_name);
            temp = temp->next;            
        }
        printf("%d.go back\n", leng);        
        int id = input(1, leng);
        
        if (id == leng)
        {
            return;
        }
        else if (id > 0 && id < leng)
        {
            system("cls");
            id--;
            struct contact *p = get_contact_node((*cont), id);
            printf("second name: %s", p->second_name);
            printf("first name: %s", p->first_name);            
            printf("work place: %s\n", p->work_place);                
            show_date(p->birthday);      
            printf("telephone number: %llu\n", p->telephone_number);        
            printf("events:\n");
            
            struct event *temp = (*cont)->ev;
        
            while(temp)
            {
                printf("%s", temp->title);
            }
            printf("\n\nchange?(y- yes, n - no)\n");
        
            while (1)
            {                
                fflush(stdin);
                char c;
                scanf("%c", &c);
        
                switch (c)
                {
                    case 'y':
                        change_contact_information(&p);
                        break;
                    case 'n':                    
                        break;
                    default:
                        printf("no such varient\n");
                        continue;
                }
                break;
            }
        }    
        else
        {
            printf("no such varient");
        }       
    }
}

void add_contact(struct contact **cont)
{
    struct contact *temp = NULL;      
    
    if (!(temp = (struct contact*)malloc(sizeof(struct contact))))
    {
        printf("not enought memory. goodbye");
        exit(1);
    }

    fflush(stdin);
    printf("second name: ");    
    fgets(temp->second_name, 30, stdin);   
    printf("first name: ");    
    fgets(temp->first_name, 30, stdin);   
    get_current_date(&temp->birthday);
    temp->work_place[0] = '\0';        
    temp->telephone_number = 0;     
    temp->ev = NULL;               
    temp->next = NULL;
    change_contact_information(&temp);     
    
    if (!(*cont))
    {
        (*cont) = temp;        
    }
    else
    {        
        temp->next = (*cont);  
        (*cont) = temp;
    }        
}

void delete_contact(struct contact **cont)
{
    if (!(*cont))
    {    
        printf("is empty\n");
        return;    
    }
    while (1)
    {
        system("cls");
        printf("select event:\n");        
        int leng = 1;        
        struct contact *temp = *cont;                
        
        while (temp)
        {
            printf("%d.%s  %s", leng++, temp->second_name, temp->first_name);
            temp = temp->next;            
        }
        printf("%d.go back\n", leng);        
        int id = input(1, leng);        
        
        if (id == leng)
        {
            return;
        }
        else
        {            
            printf("are you sure?(y - yes, n - no)\n");
        
            while (1)
            {
                struct contact *p = NULL;
        
                fflush(stdin);
                char c;
                scanf("%c", &c);
        
                switch (c)
                {
                    case 'y':         
                        if (id == 1)                                       
                        {
                            p = *cont;
                            *cont = (*cont)->next;                            
                            free(p);
                        }
                        else
                        {
                            p = get_contact_node(*cont, id - 2);                   
                            struct contact *pn = p->next;
                            p->next = p->next->next;       
                            free(pn);                     
                        }                                                
                        break;
                    case 'n':                    
                        break;;
                    default:
                        printf("no such varient");
                        continue;
                }             
                break;   
            }
        }
    }
}

void contact_menu(struct contact **cont)
{    
    while (1)
    {
        system("cls");        
        printf("1.show contacts\n");
        printf("2.add contact\n");    
        printf("3.delete contact\n");        
        printf("4.go back\n");
        
        fflush(stdin);
        char c;
        scanf("%c", &c);
        
        switch (c)
        {
            case '1':
                print_contacts(cont);
                break;
            case '2':
                add_contact(cont);
                break;
            case '3':
                delete_contact(cont);
                break;            
            case '4':
                return;                
            default:
                printf("please input number from 1 to 4\n");
        }
    }
}

void free_event(struct event *ev)
{
    while (ev)
    {
        struct event *temp = ev;
        ev = ev->next;
        free(temp);
    }
}

void free_contact(struct contact *cont)
{
    while (cont)
    {
        free_event(cont->ev);
        struct contact *temp = cont;        
        cont = cont->next;
        free(temp);
    }
}

void notifications(struct contact *cont)
{
    struct date dt;
    get_current_date(&dt);
    struct contact *temp = cont;
    printf("coming soon:\n");

    while (temp)
    {        
        struct event *p = temp->ev;

        while (p)
        {
            if (p->dt.year == dt.year &&
                p->dt.mon == dt.mon &&
                p->dt.day - dt.day < 2 &&
                p->dt.day - dt.day > 0)
            {
                printf("%s", p->title); 
                show_date(p->dt);               
            }
            p = p->next;
        }
        temp = temp->next;
    }
    printf("birthday:\n");
    temp = cont;

    while (temp)
    {
        if (temp->birthday.mon == dt.mon &&
            temp->birthday.day - dt.day < 2 &&
            temp->birthday.day - dt.day > 0)
        {
            printf("%s%s", temp->second_name, temp->first_name);
            show_date(temp->birthday);
        }
    }
}